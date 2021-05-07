#include <inttypes.h>
#include "xchain/xchain.h"
#include "xchain/account.h"
#include "xchain/contract.pb.h"
#include "xchain/syscall.h"
#include "buddha.pb.h"
#include "buddha.h"

#include <iostream>
using namespace std;

xchain::json fend::to_json() const {
    xchain::json j = {
        {"id", id()},
        {"creditcode", creditcode()},
        {"proof", proof()},
        {"approved", approved()},
    };

    return j;
}

bool Main::_is_fend_exist(fend& ent, const string& id){
    if (!get_fend_table().find({{"id", id}}, &ent))
        return false;

    return true;
}

bool Main::_is_fend_exist_by_proof(fend& ent, const string& proof){
    if (!get_fend_table().find({{"proof", proof}}, &ent))
        return false;

    return true;
}

bool Main::_is_fend(const string& id) {
    fend ent;
    if (!_is_fend_exist(ent, id))
        return false;

    return ent.approved();
}

bool Main::_scan_fend(xchain::json& ja, const string& cond) {
    auto it = get_fend_table().scan({{"id",cond}});
    while(it->next() ) {
        fend ent;
        if (!it->get(&ent) ) {
            mycout << "fend table get failure : " << it->error(true) << endl;
            return false;
        }

        ja.push_back(ent.to_json());
    }

    return true;
}

bool Main::_delete_fend_record(const string& id) {
    fend ent;
    if (!_is_fend_exist(ent, id)){
        mycout << "fend " << id << " is not exist ." << endl ;
        return false;
    }

    if( !get_fend_table().del(ent) ) {
        mycout << "delete fend " << ent.to_json().dump() << " failure ." << endl ;
        return false;
    }

    mycout << "delete fend " << ent.to_json().dump() << " success ." << endl ;
    return true;
}

namespace 分界线{}

void Main::apply_fend(){
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
        _log_error(__FILE__, __FUNCTION__, __LINE__,ctx->initiator() + " is not user, have no authority to apply  fend .");
        return ;
    }

    //判断是否已经是法师
    if( is_fend() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__,ctx->initiator() + " is already fend .");
        return ;
    }

    //判断此供养是否存在
    fend ent;
    if( _is_fend_exist(ent, ctx->initiator()) ) {
        _log_ok(__FILE__, __FUNCTION__, __LINE__, "fend " + ctx->initiator() + " is applying .", ent.to_json() );
        return ;
    }

    ent.set_id(ctx->initiator());
    ent.set_creditcode(creditcode);
    ent.set_proof(proof);
    ent.set_approved(false);
    if (!get_fend_table().put(ent) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "fend table put failure .", ent.to_json());
        return;
    }

    _log_ok(__FILE__, __FUNCTION__, __LINE__, ctx->initiator() + " apply fend over, please wait for approve .");
}

void Main::approve_fend() {
    const string& id = ctx->arg("id");
    if( id.empty() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "fend id is empty .");
        return ;
    }

    //判断是否是基金会成员
    if( !is_founder() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__,ctx->initiator() + " is not founder, have no authority to approve fend .");
        return ;
    }

    //判断此法师是否存在
    fend ent;
    if( !_is_fend_exist(ent, id) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "fend " + id + " is not exist .");
        return ;
    }

    //判断是否是法师
    if( _is_fend(id) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, id + " is already fend .", ent.to_json() );
        return ;
    }

    //删除此法师
    if( !_delete_fend_record(id) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "delete failure .", ent.to_json());
        return;
    }

    //授权
    ent.set_approved(true);
    if (!get_fend_table().put(ent) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "fend table put failure .", ent.to_json());
        return;
    }

    _log_ok(__FILE__, __FUNCTION__, __LINE__, "approve fend " + id + " success .", ent.to_json() );
}

void Main::recusal_fend() {
    const string& id = ctx->arg("id");
    if( id.empty() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "fend id is empty .");
        return ;
    }

    //判断是否是基金会成员
    if( !is_founder() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__,ctx->initiator() + " is not founder, have no authority to recusal fend .");
        return ;
    }

    //判断此法师是否存在
    fend ent;
    if( !_is_fend_exist(ent, id) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "fend " + id + " is not exist .");
        return ;
    }

    //删除此法师
    if( !_delete_fend_record(id) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "delete failure .", ent.to_json());
        return;
    }

    _log_ok(__FILE__, __FUNCTION__, __LINE__, "delete", ent.to_json() );
}

bool Main::is_fend() {
    if (!_is_fend(ctx->initiator()) ) {
        _log_ok(__FILE__, __FUNCTION__, __LINE__, ctx->initiator() + " is not fend .") ;
        return false;
    }
    
    _log_ok(__FILE__, __FUNCTION__, __LINE__, ctx->initiator() + " is fend .") ;
    return true;
}

void Main::list_fend() {
    //身份检查，部署者和基金会成员具有权限
    if( !is_deployer() &&
        !is_founder() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__,ctx->initiator() + " is not deployer nor founder, have no authority to list fend .");
        return ;
    }

    xchain::json ja ;
    if(!_scan_fend(ja, ctx->arg("id")) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "scan table failure .");
        return;
    }

    _log_ok(__FILE__, __FUNCTION__, __LINE__, "scan", ja);
}


DEFINE_METHOD(Main, apply_fend)             { self.apply_fend();              }
DEFINE_METHOD(Main, approve_fend)           { self.approve_fend();            }
DEFINE_METHOD(Main, recusal_fend)           { self.recusal_fend();            }
DEFINE_METHOD(Main, is_fend)                { self.is_fend();                 }
DEFINE_METHOD(Main, list_fend)              { self.list_fend();               }