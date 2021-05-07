#include <inttypes.h>
#include "xchain/xchain.h"
#include "xchain/account.h"
#include "xchain/contract.pb.h"
#include "xchain/syscall.h"
#include "buddha.pb.h"
#include "buddha.h"

#include <iostream>
using namespace std;

xchain::json room::to_json() const {
    xchain::json j = {
        {"id", id()},
        {"creditcode", creditcode()},
        {"proof", proof()},
        {"approved", approved()},
    };

    return j;
}

bool Main::_is_room_exist(room& ent, const string& id){
    if (!get_room_table().find({{"id", id}}, &ent))
        return false;

    return true;
}

bool Main::_is_room_exist_by_proof(room& ent, const string& proof){
    if (!get_room_table().find({{"proof", proof}}, &ent))
        return false;

    return true;
}

bool Main::_is_room(const string& id) {
    room ent;
    if (!_is_room_exist(ent, id))
        return false;

    return ent.approved();
}

bool Main::_scan_room(xchain::json& ja, const string& cond) {
    auto it = get_room_table().scan({{"id",cond}});
    while(it->next() ) {
        room ent;
        if (!it->get(&ent) ) {
            mycout << "room table get failure : " << it->error(true) << endl;
            return false;
        }

        ja.push_back(ent.to_json());
    }

    return true;
}

bool Main::_delete_room_record(const string& id) {
    room ent;
    if (!_is_room_exist(ent, id)){
        mycout << "room " << id << " is not exist ." << endl ;
        return false;
    }

    if( !get_room_table().del(ent) ) {
        mycout << "delete room " << ent.to_json().dump() << " failure ." << endl ;
        return false;
    }

    mycout << "delete room " << ent.to_json().dump() << " success ." << endl ;
    return true;
}

namespace 分界线{}

void Main::apply_room(){
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
        _log_error(__FILE__, __FUNCTION__, __LINE__,ctx->initiator() + " is not user, have no authority to apply  room .");
        return ;
    }

    //判断是否已经是法师
    if( is_room() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__,ctx->initiator() + " is already room .");
        return ;
    }

    //判断此房间是否存在
    room ent;
    if( _is_room_exist(ent, ctx->initiator()) ) {
        _log_ok(__FILE__, __FUNCTION__, __LINE__, "room " + ctx->initiator() + " is applying .", ent.to_json() );
        return ;
    }

    ent.set_id(ctx->initiator());
    ent.set_creditcode(creditcode);
    ent.set_proof(proof);
    ent.set_approved(false);
    if (!get_room_table().put(ent) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "room table put failure .", ent.to_json());
        return;
    }

    _log_ok(__FILE__, __FUNCTION__, __LINE__, ctx->initiator() + " apply room over, please wait for approve .");
}

void Main::approve_room() {
    const string& id = ctx->arg("id");
    if( id.empty() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "room id is empty .");
        return ;
    }

    //判断是否是基金会成员
    if( !is_founder() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__,ctx->initiator() + " is not founder, have no authority to approve room .");
        return ;
    }

    //判断此法师是否存在
    room ent;
    if( !_is_room_exist(ent, id) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "room " + id + " is not exist .");
        return ;
    }

    //判断是否是法师
    if( _is_room(id) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, id + " is already room .", ent.to_json() );
        return ;
    }

    //删除此法师
    if( !_delete_room_record(id) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "delete failure .", ent.to_json());
        return;
    }

    //授权
    ent.set_approved(true);
    if (!get_room_table().put(ent) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "room table put failure .", ent.to_json());
        return;
    }

    _log_ok(__FILE__, __FUNCTION__, __LINE__, "approve room " + id + " success .", ent.to_json() );
}

void Main::recusal_room() {
    const string& id = ctx->arg("id");
    if( id.empty() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "room id is empty .");
        return ;
    }

    //判断是否是基金会成员
    if( !is_founder() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__,ctx->initiator() + " is not founder, have no authority to recusal room .");
        return ;
    }

    //判断此法师是否存在
    room ent;
    if( !_is_room_exist(ent, id) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "room " + id + " is not exist .");
        return ;
    }

    //删除此法师
    if( !_delete_room_record(id) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "delete failure .", ent.to_json());
        return;
    }

    _log_ok(__FILE__, __FUNCTION__, __LINE__, "delete", ent.to_json() );
}

bool Main::is_room() {
    if (!_is_room(ctx->initiator()) ) {
        _log_ok(__FILE__, __FUNCTION__, __LINE__, ctx->initiator() + " is not room .") ;
        return false;
    }
    
    _log_ok(__FILE__, __FUNCTION__, __LINE__, ctx->initiator() + " is room .") ;
    return true;
}

void Main::list_room() {
    //身份检查，部署者和基金会成员具有权限
    if( !is_deployer() &&
        !is_founder() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__,ctx->initiator() + " is not deployer nor founder, have no authority to list room .");
        return ;
    }

    xchain::json ja ;
    if(!_scan_room(ja, ctx->arg("id")) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "scan table failure .");
        return;
    }

    _log_ok(__FILE__, __FUNCTION__, __LINE__, "scan", ja);
}


DEFINE_METHOD(Main, apply_room)             { self.apply_room();              }
DEFINE_METHOD(Main, approve_room)           { self.approve_room();            }
DEFINE_METHOD(Main, recusal_room)           { self.recusal_room();            }
DEFINE_METHOD(Main, is_room)                { self.is_room();                 }
DEFINE_METHOD(Main, list_room)              { self.list_room();               }