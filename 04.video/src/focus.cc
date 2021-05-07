#include <inttypes.h>
#include "xchain/xchain.h"
#include "xchain/account.h"
#include "xchain/contract.pb.h"
#include "xchain/syscall.h"
#include "buddha.pb.h"
#include "buddha.h"

#include <iostream>
using namespace std;

xchain::json focus::to_json() const {
    xchain::json j = {
        {"id", id()},
        {"creditcode", creditcode()},
        {"proof", proof()},
        {"approved", approved()},
    };

    return j;
}

bool Main::_is_focus_exist(focus& ent, const string& id){
    if (!get_focus_table().find({{"id", id}}, &ent))
        return false;

    return true;
}

bool Main::_is_focus_exist_by_proof(focus& ent, const string& proof){
    if (!get_focus_table().find({{"proof", proof}}, &ent))
        return false;

    return true;
}

bool Main::_is_focus(const string& id) {
    focus ent;
    if (!_is_focus_exist(ent, id))
        return false;

    return ent.approved();
}

bool Main::_scan_focus(xchain::json& ja, const string& cond) {
    auto it = get_focus_table().scan({{"id",cond}});
    while(it->next() ) {
        focus ent;
        if (!it->get(&ent) ) {
            mycout << "focus table get failure : " << it->error(true) << endl;
            return false;
        }

        ja.push_back(ent.to_json());
    }

    return true;
}

bool Main::_delete_focus_record(const string& id) {
    focus ent;
    if (!_is_focus_exist(ent, id)){
        mycout << "focus " << id << " is not exist ." << endl ;
        return false;
    }

    if( !get_focus_table().del(ent) ) {
        mycout << "delete focus " << ent.to_json().dump() << " failure ." << endl ;
        return false;
    }

    mycout << "delete focus " << ent.to_json().dump() << " success ." << endl ;
    return true;
}

namespace 分界线{}

void Main::apply_focus(){
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
        _log_error(__FILE__, __FUNCTION__, __LINE__,ctx->initiator() + " is not user, have no authority to apply  focus .");
        return ;
    }

    //判断是否已经是法师
    if( is_focus() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__,ctx->initiator() + " is already focus .");
        return ;
    }

    //判断此关注是否存在
    focus ent;
    if( _is_focus_exist(ent, ctx->initiator()) ) {
        _log_ok(__FILE__, __FUNCTION__, __LINE__, "focus " + ctx->initiator() + " is applying .", ent.to_json() );
        return ;
    }

    ent.set_id(ctx->initiator());
    ent.set_creditcode(creditcode);
    ent.set_proof(proof);
    ent.set_approved(false);
    if (!get_focus_table().put(ent) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "focus table put failure .", ent.to_json());
        return;
    }

    _log_ok(__FILE__, __FUNCTION__, __LINE__, ctx->initiator() + " apply focus over, please wait for approve .");
}

void Main::approve_focus() {
    const string& id = ctx->arg("id");
    if( id.empty() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "focus id is empty .");
        return ;
    }

    //判断是否是基金会成员
    if( !is_founder() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__,ctx->initiator() + " is not founder, have no authority to approve focus .");
        return ;
    }

    //判断此法师是否存在
    focus ent;
    if( !_is_focus_exist(ent, id) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "focus " + id + " is not exist .");
        return ;
    }

    //判断是否是法师
    if( _is_focus(id) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, id + " is already focus .", ent.to_json() );
        return ;
    }

    //删除此法师
    if( !_delete_focus_record(id) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "delete failure .", ent.to_json());
        return;
    }

    //授权
    ent.set_approved(true);
    if (!get_focus_table().put(ent) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "focus table put failure .", ent.to_json());
        return;
    }

    _log_ok(__FILE__, __FUNCTION__, __LINE__, "approve focus " + id + " success .", ent.to_json() );
}

void Main::recusal_focus() {
    const string& id = ctx->arg("id");
    if( id.empty() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "focus id is empty .");
        return ;
    }

    //判断是否是基金会成员
    if( !is_founder() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__,ctx->initiator() + " is not founder, have no authority to recusal focus .");
        return ;
    }

    //判断此法师是否存在
    focus ent;
    if( !_is_focus_exist(ent, id) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "focus " + id + " is not exist .");
        return ;
    }

    //删除此法师
    if( !_delete_focus_record(id) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "delete failure .", ent.to_json());
        return;
    }

    _log_ok(__FILE__, __FUNCTION__, __LINE__, "delete", ent.to_json() );
}

bool Main::is_focus() {
    if (!_is_focus(ctx->initiator()) ) {
        _log_ok(__FILE__, __FUNCTION__, __LINE__, ctx->initiator() + " is not focus .") ;
        return false;
    }
    
    _log_ok(__FILE__, __FUNCTION__, __LINE__, ctx->initiator() + " is focus .") ;
    return true;
}

void Main::list_focus() {
    //身份检查，部署者和基金会成员具有权限
    if( !is_deployer() &&
        !is_founder() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__,ctx->initiator() + " is not deployer nor founder, have no authority to list focus .");
        return ;
    }

    xchain::json ja ;
    if(!_scan_focus(ja, ctx->arg("id")) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "scan table failure .");
        return;
    }

    _log_ok(__FILE__, __FUNCTION__, __LINE__, "scan", ja);
}


DEFINE_METHOD(Main, apply_focus)             { self.apply_focus();              }
DEFINE_METHOD(Main, approve_focus)           { self.approve_focus();            }
DEFINE_METHOD(Main, recusal_focus)           { self.recusal_focus();            }
DEFINE_METHOD(Main, is_focus)                { self.is_focus();                 }
DEFINE_METHOD(Main, list_focus)              { self.list_focus();               }