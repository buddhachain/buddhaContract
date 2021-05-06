#include <inttypes.h>
#include "xchain/xchain.h"
#include "xchain/account.h"
#include "xchain/contract.pb.h"
#include "xchain/syscall.h"
#include "identityuser.h"
#include "main.h"

#include <iostream>
using namespace std;

xchain::json BIdentityUser::to_json() {
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

bool Main::_is_identityuser_exist(BIdentityUser& ent, const string& id){
    BIdentity id_ent;
    if (!_is_identity_exist(id_ent, id))
        return false;

    if (!get_identityuser_table().find({{"id", id}}, &ent)) {
        if( !get_identity_table().del(id_ent) )
            mycout << "delete identity user " << id_ent.to_json().dump() << " failure ." << endl ;
        return false;
    }

    return true;
}

bool Main::_is_identityuser(const string& id) {
    BIdentityUser ent;
    if (!_is_identityuser_exist(ent, id))
        return false;

    return true;
}

bool Main::_scan_identityuser(xchain::json& ja, const string& cond) {
    auto it = get_identityuser_table().scan({{"id",cond}});
    while(it->next() ) {
        BIdentityUser ent;
        if (!it->get(&ent) ) {
            mycout << "identity user table get failure : " << it->error(true) << endl;
            return false;
        }

        ja.push_back(ent.to_json());
    }

    return true;
}

bool Main::_delete_identityuser_record(const string& id) {
    BIdentityUser ent;
    if (!_is_identityuser_exist(ent, id)){
        mycout << "identity user " << id << " is not exist ." << endl ;
        return false;
    }

    if( !get_identityuser_table().del(ent) ) {
        mycout << "delete identity user " << ent.to_json().dump() << " failure ." << endl ;
        return false;
    }

    mycout << "delete identity user " << ent.to_json().dump() << " success ." << endl ;
    return true;
}

namespace 分界线{}

void Main::add_identityuser(){
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

    //判断是否已经是游客
    if( is_identityuser() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__,ctx->initiator() + " is already user .");
        return ;
    }

    //判断此寺院是否存在
    BIdentityUser ent;
    if( _is_identityuser_exist(ent, ctx->initiator()) ) {
        _log_ok(__FILE__, __FUNCTION__, __LINE__, "identity user " + ctx->initiator() + " is applying .", ent.to_json() );
        return ;
    }

    ent.set_id(ctx->initiator());
    ent.set_nickname(nickname);
    ent.set_wechat(wechat);
    ent.set_approved(false);
    if (!get_identityuser_table().put(ent) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "table put failure .", ent.to_json());
        return;
    }

    _log_ok(__FILE__, __FUNCTION__, __LINE__, ctx->initiator() + " apply identity user over, please wait for approve .");
}

bool Main::is_identityuser() {
    if (!_is_identityuser(ctx->initiator()) ) {
        _log_ok(__FILE__, __FUNCTION__, __LINE__, ctx->initiator() + " is not identity user .") ;
        return false;
    }
    
    _log_ok(__FILE__, __FUNCTION__, __LINE__, ctx->initiator() + " is identity user .") ;
    return true;
}

void Main::list_identityuser() {
    //身份检查，部署者和基金会成员具有权限
    if( !is_deployer() &&
        !is_founder() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__,ctx->initiator() + " is not deployer nor founder, have no authority to list user .");
        return ;
    }

    xchain::json ja ;
    if(!_scan_identityuser(ja, ctx->arg("id")) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "scan table failure .");
        return;
    }

    _log_ok(__FILE__, __FUNCTION__, __LINE__, "scan", ja);
}

DEFINE_METHOD(Main, is_identityuser)              { self.is_identityuser();              }
DEFINE_METHOD(Main, list_identityuser)            { self.list_identityuser();            }
DEFINE_METHOD(Main, add_identityuser)             { self.add_identityuser();             }

