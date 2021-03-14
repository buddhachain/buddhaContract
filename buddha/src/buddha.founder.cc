#include <inttypes.h>
#include "xchain/json/json.h"
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
        _log_error(__FUNCTION__, __LINE__,"desc is empty .");
        return ;
    }

    const string& address = ctx->arg("address");
    if( address.empty()) {
        _log_error(__FUNCTION__, __LINE__,"address is empty .");
        return ;
    }

    const string& timestamp = ctx->arg("timestamp");
    if( timestamp.empty()) {
        _log_error(__FUNCTION__, __LINE__,"timestamp is empty .");
        return ;
    }

    const string& guaranty = ctx->transfer_amount();
    if( guaranty.empty()) {
        _log_error(__FUNCTION__, __LINE__,"guaranty is empty .");
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
        _log_error(__FUNCTION__, __LINE__,"founder table put " + ent.to_string() + " failure .");
        return;
    }

    _log_ok(ent.to_string() + " apply  founder over, please wait for approve .");
}

void Buddha::approve_founder() {
    const string& id = ctx->arg("id");
    if( id.empty()) {
        _log_error(__FUNCTION__, __LINE__,"founder id is empty .");
        return ;
    }

    if( !is_deployer()) {
        _log_error(__FUNCTION__, __LINE__,ctx->initiator() + " is not deployer, have no authority to approve founder .");
        return ;
    }

    //判断此基金会成员是否存在
    founder ent;
    if( !_is_founder_exist(id,ent)) {
        _log_error(__FUNCTION__, __LINE__,"founder " + id + " is not exist .");
        return ;
    }

    if( _is_founder(id)) {
        _log_error(__FUNCTION__, __LINE__,ent.to_string() + " is already founder .");
        return ;
    }

    if( !_delete_founder_record(id) ) {
        _log_error(__FUNCTION__, __LINE__,"delete founder " + ent.to_string() + " failure .");
        return;
    }

    ent.set_approved(true);
    if (!get_founder_table().put(ent)) {
        _log_error(__FUNCTION__, __LINE__,"founder table put " + ent.to_string() + " failure .");
        return;
    }

    _log_ok("audit " + ent.to_string() + " to be founder .");
}

void Buddha::recusal_founder() {
    const string& id = ctx->arg("id");
    if( id.empty()) {
        _log_error(__FUNCTION__, __LINE__,"founder id is empty .");
        return ;
    }

    if( !is_deployer()) {
        _log_error(__FUNCTION__, __LINE__,ctx->initiator() + " is not deployer, have no authority recusal founder .");
        return ;
    }

    //判断此基金会成员是否存在
    founder ent;
    if( !_is_founder_exist(id,ent)) {
        _log_error(__FUNCTION__, __LINE__,"founder " + id + " is not exist .");
        return ;
    }

    if( !_delete_founder_record(id) ) {
        _log_error(__FUNCTION__, __LINE__,"delete founder " + ent.to_string() + " failure .");
        return;
    }

    //将抵押退还
    string guaranty = to_string(ent.guaranty());
    if( !_transfer(id, guaranty)) {
        _log_error(__FUNCTION__, __LINE__,"refund transfer " + guaranty + " to " + id + " failure .");
        return ;
    }

    _log_ok("recusal founder "+ id + " success , guaranty " + guaranty + " has refund, please check balance .");
}

bool Buddha::is_founder() {
    if (!_is_founder(ctx->initiator())) {
        _log_ok(ctx->initiator() + " is not founder .") ;
        return false;
    }
    
    _log_ok(ctx->initiator() + " is founder .") ;
    return true;
}

void Buddha::list_founder() {
    if( !is_deployer() &&
        !is_founder()) {
        _log_error(__FUNCTION__, __LINE__,ctx->initiator() + " is not deployer nor founder, have no authority to list founder .");
        return ;
    }

    auto it = get_founder_table().scan({{"id",ctx->arg("id")}});
    int i = 0;
    string ret;
    while(it->next()) {
        founder ent;
        if (!it->get(&ent)) {
            _log_error(__FUNCTION__, __LINE__, "founder table get failure : " + it->error(true));
            return;
        }

        i++;
        ret += ent.to_string();
    }
    _log_ok("size=" + to_string(i) + " " + ret);
}



DEFINE_METHOD(Buddha, apply_founder)            { self.apply_founder();             }
DEFINE_METHOD(Buddha, approve_founder)          { self.approve_founder();           }
DEFINE_METHOD(Buddha, recusal_founder)          { self.recusal_founder();           }
DEFINE_METHOD(Buddha, is_founder)               { self.is_founder();                }
DEFINE_METHOD(Buddha, list_founder)             { self.list_founder();              }