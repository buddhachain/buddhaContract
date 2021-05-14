#include <inttypes.h>
#include "xchain/xchain.h"
#include "xchain/account.h"
#include "xchain/contract.pb.h"
#include "xchain/syscall.h"
#include "identity.pb.h"
#include "identity.h"
#include "main.h"

#include <iostream>
using namespace std;

xchain::json BIdentity::to_json() const {
    xchain::json j = {
        {"id", id()},
        {"type", type()},
    };

    return j;
}

bool Main::_add_identity(const string& id, const int64_t type) {
    //判断此身份是否存在
    BIdentity ent;
    if( _is_identity_exist(ent, id) ) {
        mycout << id << " BIdentity is exist ." << ent.to_json() << endl;

        //删除旧数据
        if( !_delete_identity_record(ent) )
            return false;
    }

    ent.set_id(id);
    ent.set_type(type);
    if (!get_identity_table().put(ent) ) {
        mycout << "identify table put failure ." << ent.to_json() << endl;
        return false;
    }

    mycout << "table put success ." << ent.to_json() << endl;
    return true ;
}


bool Main::_is_identity_exist(BIdentity& ent, const string& id){
    if (!get_identity_table().find({{"id", id}}, &ent))
        return false;

    return true;
}

bool Main::_scan_identity(xchain::json& ja, const string& type) {
    auto it = get_identity_table().scan({{"type", type}});
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

bool Main::_delete_identity_record(const BIdentity& ent) {
    if( !get_identity_table().del(ent) ) {
        mycout << "delete identity " << ent.to_json().dump() << " failure ." << endl ;
        return false;
    }

    mycout << "delete identity " << ent.to_json().dump() << " success ." << endl ;
    return true;
}

namespace 分界线{}

bool Main::find_identity() {
    BIdentity id_ent;

    string id = ctx->arg("id");
    if( id.empty() )
        id = ctx->initiator();

    if (!_is_identity_exist(id_ent, id)){
        _log_error(__FILE__, __FUNCTION__, __LINE__, ctx->initiator() + " is not in identity table .") ;
        return false;
    }
    
    switch( id_ent.type() ) {
        case VISITOR : {
            _log_ok(__FILE__, __FUNCTION__, __LINE__, ctx->initiator() + " is identity .") ;
            break;
        }
        case USER : {
            _log_ok(__FILE__, __FUNCTION__, __LINE__, ctx->initiator() + " is user .") ;
            break;
        }
        case IDENTIFYUSER : {
            _log_ok(__FILE__, __FUNCTION__, __LINE__, ctx->initiator() + " is identity user .") ;
            break;
        }
        case MASTER : {
            _log_ok(__FILE__, __FUNCTION__, __LINE__, ctx->initiator() + " is master .") ;
            break;
        }
        case TEMPLE : {
            _log_ok(__FILE__, __FUNCTION__, __LINE__, ctx->initiator() + " is temple .") ;
            break;
        }
        case THEDEAD : {
            _log_ok(__FILE__, __FUNCTION__, __LINE__, ctx->initiator() + " is the dead .") ;
            break;
        }
        default : {
            _log_error(__FILE__, __FUNCTION__, __LINE__, ctx->initiator() + " type is error .") ;
            return false;
        }
    }

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


DEFINE_METHOD(Main, find_identity)              { self.find_identity();            }
DEFINE_METHOD(Main, list_identity)              { self.list_identity();            }
