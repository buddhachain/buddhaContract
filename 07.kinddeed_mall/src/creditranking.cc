#include <inttypes.h>
#include "xchain/xchain.h"
#include "xchain/account.h"
#include "xchain/contract.pb.h"
#include "xchain/syscall.h"
#include "buddha.pb.h"
#include "buddha.h"
#include "creditranking.h"

#include <iostream>
using namespace std;

xchain::json BCreditRanking::to_json() const {
    xchain::json j = {
        {"ranking", ranking()},
        {"id", id()},
        {"value", value()},
    };

    return j;
}

bool Main::_is_creditranking_exist(creditranking& ent, const string& ranking) {
    if (!get_creditranking_table().find({{"ranking", ranking}}, &ent))
        return false;

    return true;
}

bool Main::_scan_creditranking(xchain::json& ja, const string& cond) {
    auto it = get_creditranking_table().scan({{"id",cond}});
    while(it->next() ) {
        creditranking ent;
        if (!it->get(&ent) ) {
            mycout << "creditranking table get failure : " << it->error(true) << endl;
            return false;
        }

        ja.push_back(ent.to_json());
    }

    return true;
}

static bool _compare_credit( const creditranking& r1, const creditranking& r2) {
    return r1.value() > r2.value();
}

bool Main::_scan_creditranking(vector<creditranking>& v, const string& cond) {
    auto it = get_creditranking_table().scan({{"id",cond}});
    while(it->next() ) {
        creditranking ent;
        if (!it->get(&ent) ) {
            mycout << "creditranking table get failure : " << it->error(true) << endl;
            return false;
        }

        v.push_back(ent);
    }

    return true;
}

bool Main::_add_creditranking(const string& id, const int64_t value ) {
    //添加本质上就是找到合适的位置，然后进行覆盖，删除最后一名

    //检索出所有的记录
    vector<creditranking> v;
    if(!_scan_creditranking(v) ) {
        mycout << "scan table failure ." << endl;
        return false;
    }

    //清空排名表
    if( !_clear_creditranking() ) {
        mycout << "clear table failure ." << endl;
        return false ;
    }

    //把id插入到vector中，如果存在则覆盖，不存在则添加
    bool flag = false;
    for( creditranking& o : v ) {
        if ( o.id() == id ) {
            o.set_value(value);
            flag = true ;
            break; 
        }
    }

    if(!flag) {
        creditranking o ;
        o.set_ranking(0);
        o.set_id(id);
        o.set_value(value);
        v.push_back(o);
    }
        

    //排序
    std::sort( v.begin(),v.end(), _compare_credit );
    
    //对前100名加入名次，存入表中，删除超过100名的记录
    int i = 1;
    for( creditranking& o : v ) {        
        if( i >= 101 ) 
            break;

        o.set_ranking(i++);

        //存入表中
        if (!get_creditranking_table().put(o) ) {
            mycout << "creditranking table put failure ." << o.to_json() << endl;
            return false;
        }
    }

    mycout << "add creditranking success" << endl;

    return true ;
}

bool Main::_clear_creditranking() {
    //获取所有的记录
    vector<creditranking> v;
    if(!_scan_creditranking(v) ) {
        mycout << "scan creditranking table failure ." << endl ;
        return false;
    }

    for( creditranking& o : v ) {
        if( !get_creditranking_table().del(o) ) {
            mycout << "delete creditranking " << o.to_json().dump() << " failure ." << endl ;
            return false;
        }
    }

    return true ;
}


namespace 分界线{}

void Main::get_creditranking() {
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

    //判断此信用值排名是否已经存在
    creditranking ent;
    if (!_is_creditranking_exist(ent, ranking))  {
        _log_ok(__FILE__, __FUNCTION__, __LINE__, "creditranking " + ranking + " is not exist .");
        return ;
    }

    _log_ok(__FILE__, __FUNCTION__, __LINE__, "find", ent.to_json());
}

void Main::list_creditranking() {
    const string& id = ctx->arg("id");

    //身份检查，部署者，基金会成员具有权限
    if( is_deployer() ||
        is_founder() ) {
        xchain::json ja ;
        if(!_scan_creditranking(ja, id) ) {
            _log_error(__FILE__, __FUNCTION__, __LINE__, "scan table failure .");
            return;
        }

        _log_ok(__FILE__, __FUNCTION__, __LINE__, "scan", ja);
        return;
    }

    //非合约部署者和基金会成员，name不能为空，即禁止其他角色遍历所有售后信用值记录
    if( id.empty() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "creditranking id is empty .");
        return ;
    }

    xchain::json ja ;
    if(!_scan_creditranking(ja, id) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "scan table failure .");
        return;
    }

    _log_ok(__FILE__, __FUNCTION__, __LINE__, "scan", ja);
}

DEFINE_METHOD(Main, get_creditranking)              { self.get_creditranking();          }
DEFINE_METHOD(Main, list_creditranking)             { self.list_creditranking();         }