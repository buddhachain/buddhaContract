#include <inttypes.h>
#include "xchain/xchain.h"
#include "xchain/account.h"
#include "xchain/contract.pb.h"
#include "xchain/syscall.h"
#include "buddha.pb.h"
#include "buddha.h"
#include "meritranking.h"

#include <iostream>
using namespace std;

xchain::json meritranking::to_json() {
    xchain::json j = {
        {"ranking", ranking()},
        {"id", id()},
        {"value", value()},
    };

    return j;
}

bool Buddha::_is_meritranking_exist(const string& ranking,meritranking& ent) {
    if (!get_meritranking_table().find({{"ranking", ranking}}, &ent))
        return false;

    return true;
}

bool Buddha::_scan_meritranking(xchain::json& ja, const string& cond) {
    auto it = get_meritranking_table().scan({{"id",cond}});
    while(it->next() ) {
        meritranking ent;
        if (!it->get(&ent) ) {
            mycout << "meritranking table get failure : " << it->error(true) << endl;
            return false;
        }

        ja.push_back(ent.to_json());
    }

    return true;
}

static bool _compare_merit( const meritranking& r1, const meritranking& r2) {
    return r1.value() > r2.value();
}

bool Buddha::_scan_meritranking(vector<meritranking>& v, const string& cond) {
    auto it = get_meritranking_table().scan({{"id",cond}});
    while(it->next() ) {
        meritranking ent;
        if (!it->get(&ent) ) {
            mycout << "meritranking table get failure : " << it->error(true) << endl;
            return false;
        }

        v.push_back(ent);
    }

    return true;
}

bool Buddha::_add_meritranking(const string& id, const int64_t value ) {
    //添加本质上就是找到合适的位置，然后进行覆盖，删除最后一名

    //检索出所有的记录
    vector<meritranking> v;
    if(!_scan_meritranking(v) ) {
        mycout << "scan table failure ." << endl;
        return false;
    }

    //清空排名表
    if( !_clear_meritranking() ) {
        mycout << "clear table failure ." << endl;
        return false ;
    }

    //把id插入到vector中，如果存在则覆盖，不存在则添加
    bool flag = false;
    for( meritranking& o : v ) {
        if ( o.id() == id ) {
            o.set_value(value);
            flag = true ;
            break; 
        }
    }

    if(!flag) {
        meritranking o ;
        o.set_ranking(0);
        o.set_id(id);
        o.set_value(value);
        v.push_back(o);
    }
        

    //排序
    std::sort( v.begin(),v.end(), _compare_merit );
    
    //对前100名加入名次，存入表中，删除超过100名的记录
    int i = 1;
    for( meritranking& o : v ) {        
        if( i >= 101 ) 
            break;

        o.set_ranking(i++);

        //存入表中
        if (!get_meritranking_table().put(o) ) {
            mycout << "table put failure ." << o.to_json() << endl;
            return false;
        }
    }

    mycout << "add meritranking success" << endl;

    return true ;
}

// bool Buddha::_delete_meritranking_record(const string& id) {
//     meritranking ent;
//     if (!_is_meritranking_exist(id, ent)){
//         mycout << "meritranking " << id << " is not exist ." << endl ;
//         return false;
//     }

//     if( !get_meritranking_table().del(ent) ) {
//         mycout << "delete meritranking " << ent.to_json().dump() << " failure ." << endl ;
//         return false;
//     }

//     mycout << "delete meritranking " << ent.to_json().dump() << " success ." << endl ;
//     return true;
// }

bool Buddha::_clear_meritranking() {
    //获取所有的记录
    vector<meritranking> v;
    if(!_scan_meritranking(v) ) {
        mycout << "scan meritranking table failure ." << endl ;
        return false;
    }

    for( meritranking& o : v ) {
        if( !get_meritranking_table().del(o) ) {
            mycout << "delete meritranking " << o.to_json().dump() << " failure ." << endl ;
            return false;
        }
    }

    return true ;
}


namespace 分界线{}

void Buddha::get_meritranking() {
    const string& ranking = ctx->arg("ranking");
    if( ranking.empty() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "ranking is empty .");
        return ;
    }

    int64_t r = stoll(ranking);
    if( r >= 100 ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "ranking value mast little than 101 .");
        return ;
    }

    //判断此功德值排名是否已经存在
    meritranking ent;
    if (!_is_meritranking_exist(ranking,ent))  {
        _log_ok(__FILE__, __FUNCTION__, __LINE__, "meritranking " + ranking + " is not exist .");
        return ;
    }

    _log_ok(__FILE__, __FUNCTION__, __LINE__, "find", ent.to_json());
}

void Buddha::list_meritranking() {
    const string& id = ctx->arg("id");

    //身份检查，部署者，基金会成员具有权限
    if( is_deployer() ||
        is_founder() ) {
        xchain::json ja ;
        if(!_scan_meritranking(ja, id) ) {
            _log_error(__FILE__, __FUNCTION__, __LINE__, "scan table failure .");
            return;
        }

        _log_ok(__FILE__, __FUNCTION__, __LINE__, "scan", ja);
        return;
    }

    //非合约部署者和基金会成员，name不能为空，即禁止其他角色遍历所有售后功德值记录
    if( id.empty() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "meritranking id is empty .");
        return ;
    }

    xchain::json ja ;
    if(!_scan_meritranking(ja, id) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "scan table failure .");
        return;
    }

    _log_ok(__FILE__, __FUNCTION__, __LINE__, "scan", ja);
}

DEFINE_METHOD(Buddha, get_meritranking)              { self.get_meritranking();          }
DEFINE_METHOD(Buddha, list_meritranking)             { self.list_meritranking();         }