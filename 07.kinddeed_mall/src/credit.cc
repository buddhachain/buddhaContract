#include <inttypes.h>
#include "xchain/xchain.h"
#include "xchain/account.h"
#include "xchain/contract.pb.h"
#include "xchain/syscall.h"
#include "buddha.pb.h"
#include "buddha.h"
#include "credit.h"

#include <iostream>
using namespace std;

xchain::json BCredit::to_json() {
    xchain::json j = {
        {"id", id()},
        {"value", value()},
    };

    return j;
}

bool Main::_is_credit_exist(credit& ent, const string& id) {
    if (!get_credit_table().find({{"id", id}}, &ent))
        return false;

    return true;
}

bool Main::_scan_credit(xchain::json& ja, const string& cond) {
    auto it = get_credit_table().scan({{"id",cond}});
    while(it->next() ) {
        credit ent;
        if (!it->get(&ent) ) {
            mycout << "credit table get failure : " << it->error(true) << endl;
            return false;
        }

        ja.push_back(ent.to_json());
    }

    return true;
}

bool Main::_add_credit(const string& id, const int64_t value, int64_t& total_value) {
    //判断此信用值是否存在
    credit ent;
    if( _is_credit_exist(ent, id) ) {
        mycout << id << " credit is exist ." << ent.to_json() << endl;

        //删除旧数据
        if( !_delete_credit_record(id) ) {
            mycout << "delete failure ." << ent.to_json() << endl;
            return false;
        }
    }

    total_value = ent.value() + value;

    ent.set_id(id);
    ent.set_value(total_value);
    if (!get_credit_table().put(ent) ) {
        mycout << "table put failure ." << ent.to_json() << endl;
        return false;
    }

    mycout << "table put success ." << ent.to_json() << endl;
    return true ;
}

bool Main::_delete_credit_record(const string& id) {
    credit ent;
    if (!_is_credit_exist(ent, id)){
        mycout << "credit " << id << " is not exist ." << endl ;
        return false;
    }

    if( !get_credit_table().del(ent) ) {
        mycout << "delete credit " << ent.to_json().dump() << " failure ." << endl ;
        return false;
    }

    mycout << "delete credit " << ent.to_json().dump() << " success ." << endl ;
    return true;
}


namespace 分界线{}

void Main::find_credit() {
    const string& id = ctx->arg("id");
    if( id.empty() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "credit id is empty .");
        return ;
    }

    //判断此信用值是否已经存在
    credit ent;
    if (!_is_credit_exist(ent, id))  {
        _log_ok(__FILE__, __FUNCTION__, __LINE__, "credit " + id + " is not exist .");
        return ;
    }

    _log_ok(__FILE__, __FUNCTION__, __LINE__, "find", ent.to_json());
}

void Main::list_credit() {
    const string& id = ctx->arg("id");

    //身份检查，部署者，基金会成员具有权限
    if( is_deployer() ||
        is_founder() ) {
        xchain::json ja ;
        if(!_scan_credit(ja, id) ) {
            _log_error(__FILE__, __FUNCTION__, __LINE__, "scan table failure .");
            return;
        }

        _log_ok(__FILE__, __FUNCTION__, __LINE__, "scan", ja);
        return;
    }

    //非合约部署者和基金会成员，name不能为空，即禁止其他角色遍历所有售后信用值记录
    if( id.empty() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "credit id is empty .");
        return ;
    }

    //判断订单是否存在
    order od;        
    if (!_is_order_exist(od, id))  {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "order " + id + " is not exist .");
        return ;
    }

    xchain::json ja ;
    if(!_scan_credit(ja, id) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "scan table failure .");
        return;
    }

    _log_ok(__FILE__, __FUNCTION__, __LINE__, "scan", ja);
}

DEFINE_METHOD(Main, find_credit)             { self.find_credit();              }
DEFINE_METHOD(Main, list_credit)             { self.list_credit();              }