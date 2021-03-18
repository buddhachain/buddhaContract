#include <inttypes.h>
#include "xchain/xchain.h"
#include "xchain/account.h"
#include "xchain/contract.pb.h"
#include "xchain/syscall.h"
#include "buddha.pb.h"
#include "buddha.h"

#include <iostream>
using namespace std;

string founder::to_string() {
    string str ;
    str += "{" ;
    str += id() + ",";
    str += desc() + ",";
    str += address() + ",";
    str += timestamp() + ",";
    str += std::to_string(guaranty()) + ",";
    str += std::to_string(approved());
    str += "}";
    return str;
}


xchain::json founder::to_json() {
    xchain::json j = {
        {"id", id()},
        {"desc", desc()},
        {"address", address()},
        {"timestamp", timestamp()},
        {"guaranty", guaranty()},
        {"approved", approved()},
    };

    return j;
}

bool Buddha::_is_founder_exist(const string& id,founder& ent) {
    if (!get_founder_table().find({{"id", id}}, &ent))
        return false;

    return true;
}

bool Buddha::_is_founder(const string& id) {
    founder ent;
    if (!_is_founder_exist(id, ent))
        return false;
    
    return ent.approved();
}

bool Buddha::_scan_founder(xchain::json& v, const string& cond) {
    auto it = get_founder_table().scan({{"id",cond}});
    while(it->next()) {
        founder ent;
        if (!it->get(&ent)) {
            mycout << "founder table get failure : " << it->error(true) << endl;
            return false;
        }

        v.push_back(ent.to_json());
    }

    return true;
}

bool Buddha::_delete_founder_record(const string& id) {
    founder ent;
    if (!_is_founder_exist(id, ent)){
        mycout << "founder " << id << " is not exist ." << endl ;
        return false;
    }

    if( !get_founder_table().del(ent) ) {
        mycout << "delete founder " << ent.to_string() << " failure ." << endl ;
        return false;
    }

    mycout << "delete founder " << ent.to_string() << " success ." << endl ;
    return true;
}

namespace 分界线{}

void Buddha::apply_founder(){
    const string& desc = ctx->arg("desc");
    if( desc.empty()) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "desc is empty .");
        return ;
    }

    const string& address = ctx->arg("address");
    if( address.empty()) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "address is empty .");
        return ;
    }

    const string& timestamp = ctx->arg("timestamp");
    if( timestamp.empty()) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "timestamp is empty .");
        return ;
    }

    const string& guaranty = ctx->transfer_amount();
    if( guaranty.empty()) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "guaranty is empty .");
        return ;
    }

    //判断是否已经是基金会成员
    if( is_founder()) {
        _log_error(__FILE__, __FUNCTION__, __LINE__,ctx->initiator() + " is already founder .");
        return ;
    }

    //判断此基金会成员是否存在
    founder ent;
    if( _is_founder_exist(ctx->initiator(),ent)) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "founder " + id + " is applying .");
        return ;
    }

    ent.set_id(ctx->initiator());
    ent.set_desc(desc);
    ent.set_address(address);
    ent.set_timestamp(timestamp);
    ent.set_guaranty(ent.guaranty() + stoll(guaranty));
    ent.set_approved(false);
    if (!get_founder_table().put(ent)) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "table put failure .", ent.to_json());
        return;
    }

    _log_ok(__FILE__, __FUNCTION__, __LINE__, ent.to_json(), "apply founder over, please wait for approve .");
}

void Buddha::approve_founder() {
    const string& id = ctx->arg("id");
    if( id.empty()) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "founder id is empty .");
        return ;
    }

    //判断是否是部署者
    if( !is_deployer()) {
        _log_error(__FILE__, __FUNCTION__, __LINE__,ctx->initiator() + " is not deployer, have no authority to approve founder .");
        return ;
    }

    //判断此基金会成员是否存在
    founder ent;
    if( !_is_founder_exist(id,ent)) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "founder " + id + " is not exist .");
        return ;
    }

    //判断是否是基金会成员
    if( _is_founder(id)) {
        _log_error(__FILE__, __FUNCTION__, __LINE__,ent.to_string() + " is already founder .");
        return ;
    }

    //删除此基金会成员
    if( !_delete_founder_record(id) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "delete failure .", ent.to_json());
        return;
    }

    //授权
    ent.set_approved(true);
    if (!get_founder_table().put(ent)) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "table put failure .", ent.to_json());
        return;
    }

    _log_ok(__FILE__, __FUNCTION__, __LINE__, "audit " + ent.to_string() + " to be founder .");
}

void Buddha::recusal_founder() {
    const string& id = ctx->arg("id");
    if( id.empty()) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "founder id is empty .");
        return ;
    }

    //判断是否是部署者
    if( !is_deployer()) {
        _log_error(__FILE__, __FUNCTION__, __LINE__,ctx->initiator() + " is not deployer, have no authority recusal founder .");
        return ;
    }

    //判断此基金会成员是否存在
    founder ent;
    if( !_is_founder_exist(id,ent)) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "founder " + id + " is not exist .");
        return ;
    }

    //删除此基金会成员
    if( !_delete_founder_record(id) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "delete failure .", ent.to_json());
        return;
    }

    //将抵押退还
    string guaranty = to_string(ent.guaranty());
    if( !_transfer(id, guaranty)) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "refund transfer " + guaranty + " to " + id + " failure .");
        return ;
    }

    _log_ok(__FILE__, __FUNCTION__, __LINE__, "recusal founder "+ id + " success , guaranty " + guaranty + " has refund, please check balance .");
}

bool Buddha::is_founder() {
    if (!_is_founder(ctx->initiator())) {
        _log_ok(__FILE__, __FUNCTION__, __LINE__, ctx->initiator() + " is not founder .") ;
        return false;
    }
    
    _log_ok(__FILE__, __FUNCTION__, __LINE__, ctx->initiator() + " is founder .") ;
    return true;
}

void Buddha::list_founder() {
    if( !is_deployer() &&
        !is_founder()) {
        _log_error(__FILE__, __FUNCTION__, __LINE__,ctx->initiator() + " is not deployer nor founder, have no authority to list founder .");
        return ;
    }

    //获取所有的基金会成员
    xchain::json v ;
    if(!_scan_founder(v, ctx->arg("id")) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "scan founder failure .");
        return;
    }

    _log_ok(__FILE__, __FUNCTION__, __LINE__, v);
}



DEFINE_METHOD(Buddha, apply_founder)            { self.apply_founder();             }
DEFINE_METHOD(Buddha, approve_founder)          { self.approve_founder();           }
DEFINE_METHOD(Buddha, recusal_founder)          { self.recusal_founder();           }
DEFINE_METHOD(Buddha, is_founder)               { self.is_founder();                }
DEFINE_METHOD(Buddha, list_founder)             { self.list_founder();              }