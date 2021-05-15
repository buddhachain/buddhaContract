#include <inttypes.h>
#include "xchain/xchain.h"
#include "xchain/account.h"
#include "xchain/contract.pb.h"
#include "xchain/syscall.h"
#include "buddha.pb.h"
#include "buddha.h"

#include <iostream>
using namespace std;

xchain::json BMaster::to_json() const {
    xchain::json j = {
        {"id", id()},
        {"creditcode", creditcode()},
        {"proof", proof()},
        {"approved", approved()},
    };

    return j;
}

bool Main::_is_redeemsell_exist(BMaster& ent, const string& id){
    if (!get_redeemsell_table().find({{"id", id}}, &ent))
        return false;

    return true;
}

bool Main::_is_redeemsell_exist_by_proof(BMaster& ent, const string& proof){
    if (!get_redeemsell_table().find({{"proof", proof}}, &ent))
        return false;

    return true;
}

bool Main::_is_redeem(const string& id) {
    BMaster ent;
    if (!_is_redeemsell_exist(ent, id))
        return false;

    return ent.approved();
}

bool Main::_scan_redeem(xchain::json& ja, const string& cond) {
    auto it = get_redeemsell_table().scan({{"id",cond}});
    while(it->next() ) {
        BMaster ent;
        if (!it->get(&ent) ) {
            mycout << "redeem table get failure : " << it->error(true) << endl;
            return false;
        }

        ja.push_back(ent.to_json());
    }

    return true;
}

bool Main::_delete_redeemsell_record(const string& id) {
    BMaster ent;
    if (!_is_redeemsell_exist(ent, id)){
        mycout << "redeem " << id << " is not exist ." << endl ;
        return false;
    }

    if( !get_redeemsell_table().del(ent) ) {
        mycout << "delete redeem " << ent.to_json().dump() << " failure ." << endl ;
        return false;
    }

    mycout << "delete redeem " << ent.to_json().dump() << " success ." << endl ;
    return true;
}

namespace 分界线{}

void Main::apply_redeem(){
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
        _log_error(__FILE__, __FUNCTION__, __LINE__,ctx->initiator() + " is not user, have no authority to apply  redeem .");
        return ;
    }

    //判断是否已经是法师
    if( is_redeem() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__,ctx->initiator() + " is already redeem .");
        return ;
    }

    //判断此赎回是否存在
    BMaster ent;
    if( _is_redeemsell_exist(ent, ctx->initiator()) ) {
        _log_ok(__FILE__, __FUNCTION__, __LINE__, "redeem " + ctx->initiator() + " is applying .", ent.to_json() );
        return ;
    }

    ent.set_id(ctx->initiator());
    ent.set_creditcode(creditcode);
    ent.set_proof(proof);
    ent.set_approved(false);
    if (!get_redeemsell_table().put(ent) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "redeem table put failure .", ent.to_json());
        return;
    }

    _log_ok(__FILE__, __FUNCTION__, __LINE__, ctx->initiator() + " apply redeem over, please wait for approve .");
}

void Main::approve_redeem() {
    const string& id = ctx->arg("id");
    if( id.empty() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "redeem id is empty .");
        return ;
    }

    //判断是否是基金会成员
    if( !is_founder() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__,ctx->initiator() + " is not founder, have no authority to approve redeem .");
        return ;
    }

    //判断此法师是否存在
    BMaster ent;
    if( !_is_redeemsell_exist(ent, id) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "redeem " + id + " is not exist .");
        return ;
    }

    //判断是否是法师
    if( _is_redeem(id) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, id + " is already redeem .", ent.to_json() );
        return ;
    }

    //删除此法师
    if( !_delete_redeemsell_record(id) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "delete failure .", ent.to_json());
        return;
    }

    //授权
    ent.set_approved(true);
    if (!get_redeemsell_table().put(ent) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "redeem table put failure .", ent.to_json());
        return;
    }

    _log_ok(__FILE__, __FUNCTION__, __LINE__, "approve redeem " + id + " success .", ent.to_json() );
}

void Main::recusal_redeem() {
    const string& id = ctx->arg("id");
    if( id.empty() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "redeem id is empty .");
        return ;
    }

    //判断是否是基金会成员
    if( !is_founder() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__,ctx->initiator() + " is not founder, have no authority to recusal redeem .");
        return ;
    }

    //判断此法师是否存在
    BMaster ent;
    if( !_is_redeemsell_exist(ent, id) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "redeem " + id + " is not exist .");
        return ;
    }

    //删除此法师
    if( !_delete_redeemsell_record(id) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "delete failure .", ent.to_json());
        return;
    }

    _log_ok(__FILE__, __FUNCTION__, __LINE__, "delete", ent.to_json() );
}

bool Main::is_redeem() {
    if (!_is_redeem(ctx->initiator()) ) {
        _log_ok(__FILE__, __FUNCTION__, __LINE__, ctx->initiator() + " is not redeem .") ;
        return false;
    }
    
    _log_ok(__FILE__, __FUNCTION__, __LINE__, ctx->initiator() + " is redeem .") ;
    return true;
}

void Main::list_redeem() {
    //身份检查，部署者和基金会成员具有权限
    if( !is_deployer() &&
        !is_founder() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__,ctx->initiator() + " is not deployer nor founder, have no authority to list redeem .");
        return ;
    }

    xchain::json ja ;
    if(!_scan_redeem(ja, ctx->arg("id")) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "scan table failure .");
        return;
    }

    _log_ok(__FILE__, __FUNCTION__, __LINE__, "scan", ja);
}


DEFINE_METHOD(Main, apply_redeem)             { self.apply_redeem();              }
DEFINE_METHOD(Main, approve_redeem)           { self.approve_redeem();            }
DEFINE_METHOD(Main, recusal_redeem)           { self.recusal_redeem();            }
DEFINE_METHOD(Main, is_redeem)                { self.is_redeem();                 }
DEFINE_METHOD(Main, list_redeem)              { self.list_redeem();               }