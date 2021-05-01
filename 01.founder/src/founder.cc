#include <inttypes.h>
#include "xchain/xchain.h"
#include "xchain/account.h"
#include "xchain/contract.pb.h"
#include "xchain/syscall.h"
#include "founder.h"
#include "main.h"

#include <iostream>
using namespace std;

xchain::json BFounder::to_json() {
    xchain::json j = {
        {"id", id()},
        {"type", type()},
        {"desc", desc()},
        {"address", address()},
        {"timestamp", timestamp()},
        {"guaranty", guaranty()},
        {"approved", approved()},
    };

    return j;
}

bool Main::_is_founder_exist(BFounder& ent, const string& id) {
    if (!get_founder_table().find({{"id", id}}, &ent))
        return false;

    return true;
}

bool Main::_is_founder(const string& id) {
    BFounder ent;
    if (!_is_founder_exist(ent, id))
        return false;
    
    return ent.approved();
}

bool Main::_is_president(const string& id) {
    BFounder ent;
    if (!_is_founder_exist(ent, id))
        return false;

    if(ent.type() != PRESIDENT) {
        mycout << id << " is not prisident ." << endl ;
        return false ;
    }    

    return ent.approved();
}

bool Main::_scan_founder(xchain::json& ja, const string& id) {
    auto it = get_founder_table().scan({{"id", id}});
    while(it->next() ) {
        BFounder ent;
        if (!it->get(&ent) ) {
            mycout << "founder table get failure : " << it->error(true) << endl;
            return false;
        }

        ja.push_back(ent.to_json());
    }

    return true;
}

bool Main::_delete_founder_record(const string& id) {
    BFounder ent;
    if (!_is_founder_exist(ent, id)){
        mycout << "founder " << id << " is not exist ." << endl ;
        return false;
    }

    if( !get_founder_table().del(ent) ) {
        mycout << "delete founder " << ent.to_json().dump() << " failure ." << endl ;
        return false;
    }

    mycout << "delete founder " << ent.to_json().dump() << " success ." << endl ;
    return true;
}

namespace 分界线{}

void Main::apply_founder(){
    const string& desc = ctx->arg("desc");
    if( desc.empty() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "desc is empty .");
        return ;
    }

    const string& address = ctx->arg("address");
    if( address.empty() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "address is empty .");
        return ;
    }

    const string& timestamp = ctx->arg("timestamp");
    if( timestamp.empty() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "timestamp is empty .");
        return ;
    }

    const string& guaranty = ctx->transfer_amount();
    if( guaranty.empty() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "guaranty is empty .");
        return ;
    }

    //判断是否已经是基金会成员
    if( is_founder() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__,ctx->initiator() + " is already founder .");
        return ;
    }

    //判断此基金会成员是否存在
    BFounder ent;
    if( _is_founder_exist(ent, ctx->initiator()) ) {
        _log_ok(__FILE__, __FUNCTION__, __LINE__, "founder " + ctx->initiator() + " is applying .", ent.to_json() );
        return ;
    }

    ent.set_id(ctx->initiator());
    ent.set_type(MEMBER);
    ent.set_desc(desc);
    ent.set_address(address);
    ent.set_timestamp(timestamp);
    ent.set_guaranty(ent.guaranty() + stoll(guaranty));
    ent.set_approved(false);
    if (!get_founder_table().put(ent) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "table put failure .", ent.to_json());
        return;
    }

    _log_ok(__FILE__, __FUNCTION__, __LINE__, "apply founder over, please wait for approve .", ent.to_json());
}

void Main::approve_founder() {
    const string& id = ctx->arg("id");
    if( id.empty() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "founder id is empty .");
        return ;
    }

    //身份检查，部署者具有权限
    if( !is_deployer() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__,ctx->initiator() + " is not deployer, have no authority to approve founder .");
        return ;
    }

    //判断此基金会成员是否存在
    BFounder ent;
    if( !_is_founder_exist(ent, id) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "founder " + id + " is not exist .");
        return ;
    }

    //判断是否是基金会成员
    if( _is_founder(id) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, id + " is already founder .", ent.to_json());
        return ;
    }

    //删除此基金会成员
    if( !_delete_founder_record(id) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "delete failure .", ent.to_json());
        return;
    }

    //授权
    ent.set_approved(true);
    if (!get_founder_table().put(ent) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "table put failure .", ent.to_json());
        return;
    }

    _log_ok(__FILE__, __FUNCTION__, __LINE__, "audit " + id +  " to be founder .", ent.to_json() );
}

void Main::recusal_founder() {
    const string& id = ctx->arg("id");
    if( id.empty() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "founder id is empty .");
        return ;
    }

    //身份检查，部署者具有权限
    if( !is_deployer() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__,ctx->initiator() + " is not deployer, have no authority recusal founder .");
        return ;
    }

    //判断此基金会成员是否存在
    BFounder ent;
    if( !_is_founder_exist(ent, id) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "founder " + id + " is not exist .");
        return ;
    }

    //删除此基金会成员
    if( !_delete_founder_record(id) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "delete failure .", ent.to_json());
        return;
    }

    //将抵押退还
    string guaranty = to_string(ent.guaranty());
    if( !_transfer(id, guaranty) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "refund transfer " + guaranty + " to " + id + " failure .");
        return ;
    }

    _log_ok(__FILE__, __FUNCTION__, __LINE__, "recusal founder "+ id + " success , guaranty " + guaranty + " has refund, please check balance .");
}

bool Main::is_founder() {
    if (!_is_founder(ctx->initiator()) ) {
        _log_ok(__FILE__, __FUNCTION__, __LINE__, ctx->initiator() + " is not founder .") ;
        return false;
    }
    
    _log_ok(__FILE__, __FUNCTION__, __LINE__, ctx->initiator() + " is founder .") ;
    return true;
}


bool Main::is_president() {
    if (!_is_president(ctx->initiator()) ) {
        _log_ok(__FILE__, __FUNCTION__, __LINE__, ctx->initiator() + " is not president .") ;
        return false;
    }
    
    _log_ok(__FILE__, __FUNCTION__, __LINE__, ctx->initiator() + " is president .") ;
    return true;
}

void Main::list_founder() {
    //身份检查，部署者和基金会成员具有权限
    if( !is_deployer() &&
        !is_founder() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__,ctx->initiator() + " is not deployer nor founder, have no authority to list founder .");
        return ;
    }

    //获取所有的基金会成员
    xchain::json ja ;
    if(!_scan_founder(ja, ctx->arg("id")) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "scan founder failure .");
        return;
    }

    _log_ok(__FILE__, __FUNCTION__, __LINE__, "scan", ja);
}



DEFINE_METHOD(Main, apply_founder)            { self.apply_founder();             }
DEFINE_METHOD(Main, approve_founder)          { self.approve_founder();           }
DEFINE_METHOD(Main, recusal_founder)          { self.recusal_founder();           }
DEFINE_METHOD(Main, is_founder)               { self.is_founder();                }
DEFINE_METHOD(Main, is_president)             { self.is_president();              }
DEFINE_METHOD(Main, list_founder)             { self.list_founder();              }