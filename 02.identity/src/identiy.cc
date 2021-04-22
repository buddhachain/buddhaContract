#include <inttypes.h>
#include "xchain/xchain.h"
#include "xchain/account.h"
#include "xchain/contract.pb.h"
#include "xchain/syscall.h"
#include "identity.pb.h"
#include "identity.h"

#include <iostream>
using namespace std;

xchain::json identity::to_json() {
    xchain::json j = {
        {"id", id()},
        {"type", type()},
    };

    return j;
}

bool Main::_is_identity_exist(identity& ent, const string& id){
    if (!get_identity_table().find({{"id", id}}, &ent))
        return false;

    return true;
}

bool Main::_scan_identity(xchain::json& ja, const string& cond) {
    auto it = get_identity_table().scan({{"id",cond}});
    while(it->next() ) {
        identity ent;
        if (!it->get(&ent) ) {
            mycout << "identity table get failure : " << it->error(true) << endl;
            return false;
        }

        ja.push_back(ent.to_json());
    }

    return true;
}

bool Main::_delete_identity_record(const string& id) {
    identity ent;
    if (!_is_identity_exist(ent, id)){
        mycout << "identity " << id << " is not exist ." << endl ;
        return false;
    }

    if( !get_identity_table().del(ent) ) {
        mycout << "delete identity " << ent.to_json().dump() << " failure ." << endl ;
        return false;
    }

    mycout << "delete identity " << ent.to_json().dump() << " success ." << endl ;
    return true;
}

namespace 分界线{}

void Main::apply_identity(){
    const string& creditcode = ctx->arg("creditcode");
    if( creditcode.empty() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "creditcode is empty .");
        return ;
    }

    const string& proof = ctx->arg("proof");
    if( proof.empty() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "proof is empty .");
        return ;
    }

    //身份检查，只有用户才能申请成为法师
    if( !is_user() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__,ctx->initiator() + " is not user, have no authority to apply  identity .");
        return ;
    }

    //判断是否已经是法师
    if( is_identity() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__,ctx->initiator() + " is already identity .");
        return ;
    }

    //判断此寺院是否存在
    identity ent;
    if( _is_identity_exist(ent, ctx->initiator()) ) {
        _log_ok(__FILE__, __FUNCTION__, __LINE__, "identity " + ctx->initiator() + " is applying .", ent.to_json() );
        return ;
    }

    ent.set_id(ctx->initiator());
    ent.set_creditcode(creditcode);
    ent.set_proof(proof);
    ent.set_approved(false);
    if (!get_identity_table().put(ent) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "table put failure .", ent.to_json());
        return;
    }

    _log_ok(__FILE__, __FUNCTION__, __LINE__, ctx->initiator() + " apply identity over, please wait for approve .");
}

void Main::approve_identity() {
    const string& id = ctx->arg("id");
    if( id.empty() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "identity id is empty .");
        return ;
    }

    //判断是否是基金会成员
    if( !is_founder() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__,ctx->initiator() + " is not founder, have no authority to approve identity .");
        return ;
    }

    //判断此法师是否存在
    identity ent;
    if( !_is_identity_exist(ent, id) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "identity " + id + " is not exist .");
        return ;
    }

    //判断是否是法师
    if( _is_identity(id) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, id + " is already identity .", ent.to_json() );
        return ;
    }

    //删除此法师
    if( !_delete_identity_record(id) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "delete failure .", ent.to_json());
        return;
    }

    //授权
    ent.set_approved(true);
    if (!get_identity_table().put(ent) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "table put failure .", ent.to_json());
        return;
    }

    _log_ok(__FILE__, __FUNCTION__, __LINE__, "approve identity " + id + " success .", ent.to_json() );
}

void Main::recusal_identity() {
    const string& id = ctx->arg("id");
    if( id.empty() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "identity id is empty .");
        return ;
    }

    //判断是否是基金会成员
    if( !is_founder() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__,ctx->initiator() + " is not founder, have no authority to recusal identity .");
        return ;
    }

    //判断此法师是否存在
    identity ent;
    if( !_is_identity_exist(ent, id) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "identity " + id + " is not exist .");
        return ;
    }

    //删除此法师
    if( !_delete_identity_record(id) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "delete failure .", ent.to_json());
        return;
    }

    _log_ok(__FILE__, __FUNCTION__, __LINE__, "delete", ent.to_json() );
}

bool Main::is_identity() {
    if (!_is_identity(ctx->initiator()) ) {
        _log_ok(__FILE__, __FUNCTION__, __LINE__, ctx->initiator() + " is not identity .") ;
        return false;
    }
    
    _log_ok(__FILE__, __FUNCTION__, __LINE__, ctx->initiator() + " is identity .") ;
    return true;
}

void Main::list_identity() {
    //身份检查，部署者和基金会成员具有权限
    if( !is_deployer() &&
        !is_founder() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__,ctx->initiator() + " is not deployer nor founder, have no authority to list identity .");
        return ;
    }

    xchain::json ja ;
    if(!_scan_identity(ja, ctx->arg("id")) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "scan table failure .");
        return;
    }

    _log_ok(__FILE__, __FUNCTION__, __LINE__, "scan", ja);
}


DEFINE_METHOD(Main, apply_identity)             { self.apply_identity();              }
DEFINE_METHOD(Main, approve_identity)           { self.approve_identity();            }
DEFINE_METHOD(Main, recusal_identity)           { self.recusal_identity();            }
DEFINE_METHOD(Main, is_identity)                { self.is_identity();                 }
DEFINE_METHOD(Main, list_identity)              { self.list_identity();               }