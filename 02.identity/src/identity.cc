#include <inttypes.h>
#include "xchain/xchain.h"
#include "xchain/account.h"
#include "xchain/contract.pb.h"
#include "xchain/syscall.h"
#include "identity.pb.h"
#include "identity.h"

#include <iostream>
using namespace std;

xchain::json BIdentity::to_json() {
    xchain::json j = {
        {"id", id()},
        {"type", type()},
    };

    return j;
}

bool Main::_is_identity_exist(BIdentity& ent, const string& id){
    if (!get_identity_table().find({{"id", id}}, &ent))
        return false;

    return true;
}

bool Main::_scan_identity(xchain::json& ja, const string& cond) {
    auto it = get_identity_table().scan({{"type",cond}});
    while(it->next() ) {
        BIdentity ent;
        if (!it->get(&ent) ) {
            mycout << "identity table get failure : " << it->error(true) << endl;
            return false;
        }

        ja.push_back(ent.to_json());
    }

    return true;
}

bool Main::_delete_identity_record(const string& id) {
    BIdentity ent;
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
    if(!_scan_identity(ja, ctx->arg("type")) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "scan table failure .");
        return;
    }

    _log_ok(__FILE__, __FUNCTION__, __LINE__, "scan", ja);
}


DEFINE_METHOD(Main, apply_identity)             { self.find_identity();              }
DEFINE_METHOD(Main, approve_identity)           { self.list_identity();            }
