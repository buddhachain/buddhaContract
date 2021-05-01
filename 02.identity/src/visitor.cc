#include <inttypes.h>
#include "xchain/xchain.h"
#include "xchain/account.h"
#include "xchain/contract.pb.h"
#include "xchain/syscall.h"
#include "identity.h"
#include "visitor.pb.h"
#include "visitor.h"

#include <iostream>
using namespace std;

xchain::json BVisitor::to_json() {
    xchain::json j = {
        {"id", id()},
        {"nickname", nickname()},
        {"wechat", wechat()},
    };

    return j;
}

bool Main::_is_visitor_exist(BVisitor& ent, const string& id){
    BIdentity id_ent;
    if (!_is_identity_exist(id_ent, id))
        return false;

    if (!get_visitor_table().find({{"id", id}}, &ent)) {
        if( !get_identity_table().del(id_ent) )
            mycout << "delete identity " << id_ent.to_json().dump() << " failure ." << endl ;
        return false;
    }

    return true;
}

bool Main::_is_visitor(const string& id) {
    BVisitor ent;
    if (!_is_visitor_exist(ent, id))
        return false;

    return true;
}

bool Main::_scan_visitor(xchain::json& ja,
                         const string& id,
                         const string& nickname,
                         const string& wechat) {
    auto it = get_visitor_table().scan({{"id",cond}});
    while(it->next() ) {
        BVisitor ent;
        if (!it->get(&ent) ) {
            mycout << "visitor table get failure : " << it->error(true) << endl;
            return false;
        }

        ja.push_back(ent.to_json());
    }

    return true;
}

bool Main::_delete_visitor_record(const string& id) {
    BVisitor ent;
    if (!_is_visitor_exist(ent, id)){
        mycout << "visitor " << id << " is not exist ." << endl ;
        return false;
    }

    if( !get_visitor_table().del(ent) ) {
        mycout << "delete visitor " << ent.to_json().dump() << " failure ." << endl ;
        return false;
    }

    mycout << "delete visitor " << ent.to_json().dump() << " success ." << endl ;
    return true;
}

namespace 分界线{}

void Main::add_visitor(){
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
    if( is_visitor() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__,ctx->initiator() + " is already visitor .");
        return ;
    }

    //判断此寺院是否存在
    BVisitor ent;
    if( _is_visitor_exist(ent, ctx->initiator()) ) {
        _log_ok(__FILE__, __FUNCTION__, __LINE__, "visitor " + ctx->initiator() + " is applying .", ent.to_json() );
        return ;
    }

    ent.set_id(ctx->initiator());
    ent.set_nickname(nickname);
    ent.set_wechat(wechat);
    ent.set_approved(false);
    if (!get_visitor_table().put(ent) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "table put failure .", ent.to_json());
        return;
    }

    _log_ok(__FILE__, __FUNCTION__, __LINE__, ctx->initiator() + " apply visitor over, please wait for approve .");
}

bool Main::is_visitor() {
    if (!_is_visitor(ctx->initiator()) ) {
        _log_ok(__FILE__, __FUNCTION__, __LINE__, ctx->initiator() + " is not visitor .") ;
        return false;
    }
    
    _log_ok(__FILE__, __FUNCTION__, __LINE__, ctx->initiator() + " is visitor .") ;
    return true;
}

void Main::list_visitor() {
    //身份检查，部署者和基金会成员具有权限
    if( !is_deployer() &&
        !is_founder() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__,ctx->initiator() + " is not deployer nor founder, have no authority to list visitor .");
        return ;
    }

    xchain::json ja ;
    if(!_scan_visitor(ja, ctx->arg("id")) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "scan table failure .");
        return;
    }

    _log_ok(__FILE__, __FUNCTION__, __LINE__, "scan", ja);
}

DEFINE_METHOD(Buddha, is_visitor)              { self.is_visitor();              }
DEFINE_METHOD(Buddha, list_visitor)            { self.list_visitor();            }
DEFINE_METHOD(Buddha, add_visitor)             { self.add_visitor();             }

