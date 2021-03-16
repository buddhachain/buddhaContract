#include <inttypes.h>
#include "xchain/xchain.h"
#include "xchain/account.h"
#include "xchain/contract.pb.h"
#include "xchain/syscall.h"
#include "buddha.pb.h"
#include "buddha.h"

#include <iostream>
using namespace std;


void Buddha::apply_founder(){
    const string& desc = ctx->arg("desc");
    if( desc.empty()) {
        _log_error(__FUNCTION__, __LINE__, "desc is empty .");
        return ;
    }

    const string& address = ctx->arg("address");
    if( address.empty()) {
        _log_error(__FUNCTION__, __LINE__, "address is empty .");
        return ;
    }

    const string& timestamp = ctx->arg("timestamp");
    if( timestamp.empty()) {
        _log_error(__FUNCTION__, __LINE__, "timestamp is empty .");
        return ;
    }

    const string& guaranty = ctx->transfer_amount();
    if( guaranty.empty()) {
        _log_error(__FUNCTION__, __LINE__, "guaranty is empty .");
        return ;
    }

    if( is_founder()) {
        _log_error(__FUNCTION__, __LINE__,ctx->initiator() + " is already founder .");
        return ;
    }

    _delete_founder_record(ctx->initiator());

    founder ent;
    ent.set_id(ctx->initiator());
    ent.set_desc(desc);
    ent.set_address(address);
    ent.set_timestamp(timestamp);
    ent.set_guaranty(ent.guaranty() + stoll(guaranty));
    ent.set_approved(false);
    if (!get_founder_table().put(ent)) {
        _log_error(__FUNCTION__, __LINE__, "table put failure .", ent.to_json());
        return;
    }

    _log_ok(__FUNCTION__, __LINE__, ent.to_json(), "apply founder over, please wait for approve .");
}

void Buddha::approve_founder() {
    const string& id = ctx->arg("id");
    if( id.empty()) {
        _log_error(__FUNCTION__, __LINE__, "founder id is empty .");
        return ;
    }

    if( !is_deployer()) {
        _log_error(__FUNCTION__, __LINE__,ctx->initiator() + " is not deployer, have no authority to approve founder .");
        return ;
    }

    //判断此基金会成员是否存在
    founder ent;
    if( !_is_founder_exist(id,ent)) {
        _log_error(__FUNCTION__, __LINE__, "founder " + id + " is not exist .");
        return ;
    }

    //判断是否是基金会成员
    if( _is_founder(id)) {
        _log_error(__FUNCTION__, __LINE__,ent.to_string() + " is already founder .");
        return ;
    }

    //删除此基金会成员
    if( !_delete_founder_record(id) ) {
        _log_error(__FUNCTION__, __LINE__, "delete failure .", ent.to_json());
        return;
    }

    ent.set_approved(true);
    if (!get_founder_table().put(ent)) {
        _log_error(__FUNCTION__, __LINE__, "table put failure .", ent.to_json());
        return;
    }

    _log_ok(__FUNCTION__, __LINE__, "audit " + ent.to_string() + " to be founder .");
}

void Buddha::recusal_founder() {
    const string& id = ctx->arg("id");
    if( id.empty()) {
        _log_error(__FUNCTION__, __LINE__, "founder id is empty .");
        return ;
    }

    if( !is_deployer()) {
        _log_error(__FUNCTION__, __LINE__,ctx->initiator() + " is not deployer, have no authority recusal founder .");
        return ;
    }

    //判断此基金会成员是否存在
    founder ent;
    if( !_is_founder_exist(id,ent)) {
        _log_error(__FUNCTION__, __LINE__, "founder " + id + " is not exist .");
        return ;
    }

    //删除此基金会成员
    if( !_delete_founder_record(id) ) {
        _log_error(__FUNCTION__, __LINE__, "delete failure .", ent.to_json());
        return;
    }

    //将抵押退还
    string guaranty = to_string(ent.guaranty());
    if( !_transfer(id, guaranty)) {
        _log_error(__FUNCTION__, __LINE__, "refund transfer " + guaranty + " to " + id + " failure .");
        return ;
    }

    _log_ok(__FUNCTION__, __LINE__, "recusal founder "+ id + " success , guaranty " + guaranty + " has refund, please check balance .");
}

bool Buddha::is_founder() {
    if (!_is_founder(ctx->initiator())) {
        _log_ok(__FUNCTION__, __LINE__, ctx->initiator() + " is not founder .") ;
        return false;
    }
    
    _log_ok(__FUNCTION__, __LINE__, ctx->initiator() + " is founder .") ;
    return true;
}

void Buddha::list_founder() {
    if( !is_deployer() &&
        !is_founder()) {
        _log_error(__FUNCTION__, __LINE__,ctx->initiator() + " is not deployer nor founder, have no authority to list founder .");
        return ;
    }

    //获取所有的基金会成员
    xchain::json v ;
    if(!_scan_founder(v, ctx->arg("id")) ) {
        _log_error(__FUNCTION__, __LINE__, "scan founder failure .");
        return;
    }

    _log_ok(__FUNCTION__, __LINE__, v);
}



DEFINE_METHOD(Buddha, apply_founder)            { self.apply_founder();             }
DEFINE_METHOD(Buddha, approve_founder)          { self.approve_founder();           }
DEFINE_METHOD(Buddha, recusal_founder)          { self.recusal_founder();           }
DEFINE_METHOD(Buddha, is_founder)               { self.is_founder();                }
DEFINE_METHOD(Buddha, list_founder)             { self.list_founder();              }