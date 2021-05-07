#include <inttypes.h>
#include "xchain/xchain.h"
#include "xchain/account.h"
#include "xchain/contract.pb.h"
#include "xchain/syscall.h"
#include "identifyuser.h"
#include "main.h"

#include <iostream>
using namespace std;

xchain::json BIdentifyUser::to_json() const {
    xchain::json j = {
        {"id", id()},
        {"nickname", nickname()},
        {"wechat", wechat()},
        {"photo", photo()},
        {"name", name()},
        {"sex", sex()},
        {"phone", phone()},
        {"email", email()},
        {"home_address", home_address()},
        {"born_timestamp", born_timestamp()},
        {"idcard", idcard()},
        {"idname", idname()},
        {"otherid", otherid()},
        {"photos", photos()},
        {"desc", desc()},
        {"degree", degree()},
        {"job", job()},
        {"income", income()},
        {"marry", marry()},
        {"hobyy", hobyy()},
        {"recommender", recommender()},
        {"belief", belief()},
        {"approved", approved()},
    };

    return j;
}

bool Main::_is_identifyuser_exist(BIdentifyUser& ent, const string& id){
    BIdentity id_ent;
    if (!_is_identity_exist(id_ent, id))
        return false;

    if (!get_identifyuser_table().find({{"id", id}}, &ent)) {
        if( !get_identity_table().del(id_ent) )
            mycout << "delete identity user " << id_ent.to_json().dump() << " failure ." << endl ;
        return false;
    }

    return true;
}

bool Main::_is_identifyuser(const string& id) {
    BIdentifyUser ent;
    if (!_is_identifyuser_exist(ent, id))
        return false;

    return true;
}

bool Main::_scan_identifyuser(xchain::json& ja, const string& cond) {
    auto it = get_identifyuser_table().scan({{"id",cond}});
    while(it->next() ) {
        BIdentifyUser ent;
        if (!it->get(&ent) ) {
            mycout << "identity user table get failure : " << it->error(true) << endl;
            return false;
        }

        ja.push_back(ent.to_json());
    }

    return true;
}

bool Main::_delete_identifyuser_record(const BIdentifyUser& ent) {
    if( !get_identifyuser_table().del(ent) ) {
        mycout << "delete identity user " << ent.to_json().dump() << " failure ." << endl ;
        return false;
    }

    mycout << "delete identity user " << ent.to_json().dump() << " success ." << endl ;
    return true;
}

namespace 分界线{}

void Main::apply_identifyuser(){
    const string& nickname = ctx->arg("nickname");
    if( nickname.empty() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "nickname is empty .");
        return ;
    }

    const string& wechat = ctx->arg("wechat");
    if( wechat.empty() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "wechat is empty .");
        return ;
    }

    //身份检查，只有用户才能申请成为认证用户
    if( !is_user() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__,ctx->initiator() + " is not user, have no authority to apply  identifyuser .");
        return ;
    }

    //判断是否已经是认证用户
    if( is_identifyuser() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__,ctx->initiator() + " is already identifyuser .");
        return ;
    }

    //判断此认证用户是否存在
    BIdentifyUser ent;
    if( _is_identifyuser_exist(ent, ctx->initiator()) ) {
        _log_ok(__FILE__, __FUNCTION__, __LINE__, "identifyuser " + ctx->initiator() + " is applying .", ent.to_json() );
        return ;
    }

    ent.set_id(ctx->initiator());
    ent.set_nickname(nickname);
    ent.set_wechat(wechat);
    ent.set_approved(false);
    if (!get_identifyuser_table().put(ent) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "identifyuser table put failure .", ent.to_json());
        return;
    }

    _log_ok(__FILE__, __FUNCTION__, __LINE__, ctx->initiator() + " apply identifyuser over, please wait for approve .");
}

void Main::approve_identifyuser() {
    const string& id = ctx->arg("id");
    if( id.empty() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "identifyuser id is empty .");
        return ;
    }

    //判断是否是基金会成员
    if( !is_founder() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__,ctx->initiator() + " is not founder, have no authority to approve identifyuser .");
        return ;
    }

    //判断此认证用户是否存在
    BIdentifyUser ent;
    if( !_is_identifyuser_exist(ent, id) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "identifyuser " + id + " is not exist .");
        return ;
    }

    //判断是否是认证用户
    if( _is_identifyuser(id) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, id + " is already identifyuser .", ent.to_json() );
        return ;
    }

    //删除此认证用户
    if( !_delete_identifyuser_record(ent) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "delete failure .", ent.to_json());
        return;
    }

    //授权
    ent.set_approved(true);
    if (!get_identifyuser_table().put(ent) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "identifyuser table put failure .", ent.to_json());
        return;
    }

    _log_ok(__FILE__, __FUNCTION__, __LINE__, "approve identifyuser " + id + " success .", ent.to_json() );
}

void Main::recusal_identifyuser() {
    const string& id = ctx->arg("id");
    if( id.empty() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "identifyuser id is empty .");
        return ;
    }

    //判断是否是基金会成员
    if( !is_founder() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__,ctx->initiator() + " is not founder, have no authority to recusal identifyuser .");
        return ;
    }

    //判断此认证用户是否存在
    BIdentifyUser ent;
    if( !_is_identifyuser_exist(ent, id) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "identifyuser " + id + " is not exist .");
        return ;
    }

    //删除此认证用户
    if( !_delete_identifyuser_record(ent) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "delete failure .", ent.to_json());
        return;
    }

    _log_ok(__FILE__, __FUNCTION__, __LINE__, "delete", ent.to_json() );
}

bool Main::is_identifyuser() {
    if (!_is_identifyuser(ctx->initiator()) ) {
        _log_ok(__FILE__, __FUNCTION__, __LINE__, ctx->initiator() + " is not identifyuser .") ;
        return false;
    }
    
    _log_ok(__FILE__, __FUNCTION__, __LINE__, ctx->initiator() + " is identifyuser .") ;
    return true;
}

void Main::list_identifyuser() {
    //身份检查，部署者和基金会成员具有权限
    if( !is_deployer() &&
        !is_founder() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__,ctx->initiator() + " is not deployer nor founder, have no authority to list identifyuser .");
        return ;
    }

    xchain::json ja ;
    if(!_scan_identifyuser(ja, 
                     ctx->arg("id")
                     ) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "scan table failure .");
        return;
    }

    _log_ok(__FILE__, __FUNCTION__, __LINE__, "scan", ja);
}


DEFINE_METHOD(Main, apply_identifyuser)             { self.apply_identifyuser();              }
DEFINE_METHOD(Main, approve_identifyuser)           { self.approve_identifyuser();            }
DEFINE_METHOD(Main, recusal_identifyuser)           { self.recusal_identifyuser();            }
DEFINE_METHOD(Main, is_identifyuser)                { self.is_identifyuser();                 }
DEFINE_METHOD(Main, list_identifyuser)              { self.list_identifyuser();               }
