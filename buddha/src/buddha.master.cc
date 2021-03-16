#include <inttypes.h>
#include "xchain/xchain.h"
#include "xchain/account.h"
#include "xchain/contract.pb.h"
#include "xchain/syscall.h"
#include "buddha.pb.h"
#include "buddha.h"

#include <iostream>
using namespace std;

void Buddha::apply_master(){
    const string& creditcode = ctx->arg("creditcode");
    if( creditcode.empty()) {
        _log_error(__FUNCTION__, __LINE__, "creditcode is empty .");
        return ;
    }

    const string& proof = ctx->arg("proof");
    if( proof.empty()) {
        _log_error(__FUNCTION__, __LINE__, "proof is empty .");
        return ;
    }

    if( !is_user()) {
        _log_error(__FUNCTION__, __LINE__,ctx->initiator() + " is not user, have no authority to apply  master .");
        return ;
    }

    if( is_master()) {
        _log_error(__FUNCTION__, __LINE__,ctx->initiator() + " is already master .");
        return ;
    }

    _delete_master_record(ctx->initiator());

    master ent;
    ent.set_id(ctx->initiator());
    ent.set_creditcode(creditcode);
    ent.set_proof(proof);
    ent.set_approved(false);
    if (!get_master_table().put(ent)) {
        _log_error(__FUNCTION__, __LINE__, "table put failure .", ent.to_json());
        return;
    }

    _log_ok(__FUNCTION__, __LINE__, ent.to_string() + " apply  master over, please wait for approve .");
}

void Buddha::approve_master() {
    const string& id = ctx->arg("id");
    if( id.empty()) {
        _log_error(__FUNCTION__, __LINE__, "master id is empty .");
        return ;
    }

    if( !is_founder()) {
        _log_error(__FUNCTION__, __LINE__,ctx->initiator() + " is not founder, have no authority to approve master .");
        return ;
    }

    //判断此法师是否存在
    master ent;
    if( !_is_master_exist(id,ent)) {
        _log_error(__FUNCTION__, __LINE__, "master " + id + " is not exist .");
        return ;
    }

    //判断是否是法师
    if( _is_master(id)) {
        _log_error(__FUNCTION__, __LINE__,ent.to_string() + " is already master .");
        return ;
    }

    //删除此法师
    if( !_delete_master_record(id) ) {
        _log_error(__FUNCTION__, __LINE__, "delete failure .", ent.to_json());
        return;
    }

    ent.set_approved(true);
    if (!get_master_table().put(ent)) {
        _log_error(__FUNCTION__, __LINE__, "table put failure .", ent.to_json());
        return;
    }

    _log_ok(__FUNCTION__, __LINE__, "approve master " + ent.to_string() + " success .");
}

void Buddha::recusal_master() {
    const string& id = ctx->arg("id");
    if( id.empty()) {
        _log_error(__FUNCTION__, __LINE__, "master id is empty .");
        return ;
    }
    
    if( !is_founder()) {
        _log_error(__FUNCTION__, __LINE__,ctx->initiator() + " is not founder, have no authority to recusal master .");
        return ;
    }

    //判断此法师是否存在
    master ent;
    if( !_is_master_exist(id,ent)) {
        _log_error(__FUNCTION__, __LINE__, "master " + id + " is not exist .");
        return ;
    }

    //删除此法师
    if( !_delete_master_record(id) ) {
        _log_error(__FUNCTION__, __LINE__, "delete failure .", ent.to_json());
        return;
    }

    _log_ok(__FUNCTION__, __LINE__, "recusal master " + ent.to_string() + " success .");
}

bool Buddha::is_master() {
    if (!_is_master(ctx->initiator())) {
        _log_ok(__FUNCTION__, __LINE__, ctx->initiator() + " is not master .") ;
        return false;
    }
    
    _log_ok(__FUNCTION__, __LINE__, ctx->initiator() + " is master .") ;
    return true;
}

void Buddha::list_master() {
    if( !is_deployer() &&
        !is_founder()) {
        _log_error(__FUNCTION__, __LINE__,ctx->initiator() + " is not deployer nor founder, have no authority to list master .");
        return ;
    }

    xchain::json v ;
    if(!_scan_master(v, ctx->arg("id")) ) {
        _log_error(__FUNCTION__, __LINE__, "scan table failure .");
        return;
    }

    _log_ok(__FUNCTION__, __LINE__, v);
}


DEFINE_METHOD(Buddha, apply_master)             { self.apply_master();              }
DEFINE_METHOD(Buddha, approve_master)           { self.approve_master();            }
DEFINE_METHOD(Buddha, recusal_master)           { self.recusal_master();            }
DEFINE_METHOD(Buddha, is_master)                { self.is_master();                 }
DEFINE_METHOD(Buddha, list_master)              { self.list_master();               }