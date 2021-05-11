#include <inttypes.h>
#include "xchain/xchain.h"
#include "xchain/account.h"
#include "xchain/contract.pb.h"
#include "xchain/syscall.h"
#include "identity.h"
#include "main.h"
#include "visitor.h"

#include <iostream>
using namespace std;

xchain::json BVisitor::to_json() const {
    xchain::json j = {
        {"id", id()},
        {"nickname", nickname()},
        {"wechat", wechat()},
    };

    return j;
}

bool Main::_is_visitor_exist(BVisitor& ent, const string& id){
    if (!get_visitor_table().find({{"id", id}}, &ent))
        return false;

    return true;
}

bool Main::_is_visitor(const string& id) {
    BIdentity id_ent;
    BVisitor ent;

    if (!_is_identity_exist(id_ent, id) && !_is_visitor_exist(ent, id)) 
        return false ;
    
    if (_is_identity_exist(id_ent, id) && !_is_visitor_exist(ent, id)) {
        _delete_identity_record(id_ent);
        return false;
    }

    if (!_is_identity_exist(id_ent, id) && _is_visitor_exist(ent, id) ) {
        _delete_visitor_record(ent);
        return false;
    }

    return true;
}

bool Main::_scan_visitor(xchain::json& ja,
                         const string& id,
                         const string& nickname,
                         const string& wechat) {
    auto it = get_visitor_table().scan({{"id",id}});
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

bool Main::_delete_visitor_record(const BVisitor& ent) {
    if( !get_visitor_table().del(ent) ) {
        mycout << "delete visitor " << ent.to_json().dump() << " failure ." << endl ;
        return false;
    }

    mycout << "delete visitor " << ent.to_json().dump() << " success ." << endl ;
    return true;
}

bool Main::_delete_visitor(const string& id) {
    BIdentity id_ent;
    BVisitor ent;

    if (!_is_identity_exist(id_ent, id) && !_is_visitor_exist(ent, id)) 
        return true ;
    
    if (_is_identity_exist(id_ent, id) && !_is_visitor_exist(ent, id))
        return _delete_identity_record(id_ent);

    if (!_is_identity_exist(id_ent, id) && _is_visitor_exist(ent, id) )
        return _delete_visitor_record(ent);

    return _delete_visitor_record(ent) & _delete_identity_record(id_ent);
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

    BVisitor ent;
    ent.set_id(ctx->initiator());
    ent.set_nickname(nickname);
    ent.set_wechat(wechat);
    if (!get_visitor_table().put(ent) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "visitor table put failure .", ent.to_json());
        return;
    }

    if(!_add_identity(ctx->initiator(), VISITOR)) {
        _delete_visitor_record(ent);
        _log_error(__FILE__, __FUNCTION__, __LINE__, "identity table put failure .", ent.to_json());
        return ;
    }

    _log_ok(__FILE__, __FUNCTION__, __LINE__, "add visitor success .", ent.to_json());
}

void Main::update_visitor(){
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

    string id;

    //身份检查，部署者和基金会成员具有权限
    if( is_deployer() ||
        is_founder() ) {
        if( id.empty() ) {
            _log_error(__FILE__, __FUNCTION__, __LINE__, "id is empty .");
            return ;
        }

        id = ctx->arg("id");
    } else if( is_visitor() ) { //判断是否是游客
        id = ctx->initiator();
    } else {
        _log_error(__FILE__, __FUNCTION__, __LINE__,ctx->initiator() + " is not visitor, deployer, founder .");
        return ;
    }

    if(!_delete_visitor(id)){
        _log_error(__FILE__, __FUNCTION__, __LINE__, "delete visitor " + id + " failure .");
        return ;
    }

    //获取游客信息
    BVisitor ent;
    ent.set_id(id);
    ent.set_nickname(nickname);
    ent.set_wechat(wechat);
    if (!get_visitor_table().put(ent) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "visitor table put failure .", ent.to_json());
        return;
    }

    if(!_add_identity(ctx->initiator(), VISITOR)) {
        _delete_visitor_record(ent);
        _log_error(__FILE__, __FUNCTION__, __LINE__, "identity table put failure .", ent.to_json());
        return ;
    }

    _log_ok(__FILE__, __FUNCTION__, __LINE__, "update visitor success .", ent.to_json());
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

DEFINE_METHOD(Main, add_visitor)             { self.add_visitor();             }
DEFINE_METHOD(Main, update_visitor)          { self.update_visitor();          }
DEFINE_METHOD(Main, is_visitor)              { self.is_visitor();              }
DEFINE_METHOD(Main, list_visitor)            { self.list_visitor();            }

