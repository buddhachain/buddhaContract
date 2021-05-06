#include <inttypes.h>
#include "xchain/xchain.h"
#include "xchain/account.h"
#include "xchain/contract.pb.h"
#include "xchain/syscall.h"
#include "identity.h"
#include "thedead.h"
#include "main.h"

#include <iostream>
using namespace std;

xchain::json BTheDead::to_json() {
    xchain::json j = {
        {"id", id()},
        {"name", name()},
        {"sex", sex()},
        {"born_timestamp", born_timestamp()},
        {"born_address", born_address()},
        {"dead_timestamp", dead_timestamp()},
        {"dead_address", dead_address()},
        {"idcard", idcard()},
        {"otherid", otherid()},
        {"desc", desc()},
    };

    return j;
}

bool Main::_is_thedead_exist(BTheDead& ent, const string& id){
    BIdentity id_ent;
    if (!_is_identity_exist(id_ent, id))
        return false;

    if (!get_thedead_table().find({{"id", id}}, &ent)) {
        if( !get_identity_table().del(id_ent) )
            mycout << "delete identity " << id_ent.to_json().dump() << " failure ." << endl ;
        return false;
    }

    return true;
}

bool Main::_is_thedead(const string& id) {
    BTheDead ent;
    if (!_is_thedead_exist(ent, id))
        return false;

    return true;
}

bool Main::_scan_thedead(xchain::json& ja,
                         const string& id) {
    auto it = get_thedead_table().scan({{"id",id}});
    while(it->next() ) {
        BTheDead ent;
        if (!it->get(&ent) ) {
            mycout << "thedead table get failure : " << it->error(true) << endl;
            return false;
        }

        ja.push_back(ent.to_json());
    }

    return true;
}

bool Main::_delete_thedead_record(const string& id) {
    BTheDead ent;
    if (!_is_thedead_exist(ent, id)){
        mycout << "thedead " << id << " is not exist ." << endl ;
        return false;
    }

    if( !get_thedead_table().del(ent) ) {
        mycout << "delete thedead " << ent.to_json().dump() << " failure ." << endl ;
        return false;
    }

    mycout << "delete thedead " << ent.to_json().dump() << " success ." << endl ;
    return true;
}

namespace 分界线{}

void Main::add_thedead(){
    const string& name = ctx->arg("name");
    if( name.empty() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "name is empty .");
        return ;
    }

    //判断是否已经是逝者
    if( is_thedead() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__,ctx->initiator() + " is already thedead .");
        return ;
    }

    //判断此逝者是否存在
    BTheDead ent;
    if( _is_thedead_exist(ent, ctx->initiator()) ) {
        _log_ok(__FILE__, __FUNCTION__, __LINE__, "thedead " + ctx->initiator() + " is applying .", ent.to_json() );
        return ;
    }

    ent.set_id(ctx->initiator());
    ent.set_name(name);
    if (!get_thedead_table().put(ent) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "table put failure .", ent.to_json());
        return;
    }

    _log_ok(__FILE__, __FUNCTION__, __LINE__, ctx->initiator() + " apply thedead over, please wait for approve .");
}

bool Main::is_thedead() {
    if (!_is_thedead(ctx->initiator()) ) {
        _log_ok(__FILE__, __FUNCTION__, __LINE__, ctx->initiator() + " is not thedead .") ;
        return false;
    }
    
    _log_ok(__FILE__, __FUNCTION__, __LINE__, ctx->initiator() + " is thedead .") ;
    return true;
}

void Main::list_thedead() {
    //身份检查，部署者和基金会成员具有权限
    if( !is_deployer() &&
        !is_founder() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__,ctx->initiator() + " is not deployer nor founder, have no authority to list thedead .");
        return ;
    }

    xchain::json ja ;
    if(!_scan_thedead(ja, ctx->arg("id")) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "scan table failure .");
        return;
    }

    _log_ok(__FILE__, __FUNCTION__, __LINE__, "scan", ja);
}

DEFINE_METHOD(Main, is_thedead)              { self.is_thedead();              }
DEFINE_METHOD(Main, list_thedead)            { self.list_thedead();            }
DEFINE_METHOD(Main, add_thedead)             { self.add_thedead();             }

