#include <inttypes.h>
#include "xchain/xchain.h"
#include "xchain/account.h"
#include "xchain/contract.pb.h"
#include "xchain/syscall.h"
#include "buddha.pb.h"
#include "buddha.h"

#include <iostream>
using namespace std;

string master::to_string() {
    string str ;
    str += "{" ;
    str += id() + ",";
    str += creditcode() + ",";
    str += proof() + ",";
    str += std::to_string(approved());
    str += "}";
    return str;
}

xchain::json master::to_json() {
    xchain::json j = {
        {"id", id()},
        {"creditcode", creditcode()},
        {"proof", proof()},
        {"approved", approved()},
    };

    return j;
}

bool Buddha::_is_master_exist(const string& id,master& ent){
    if (!get_master_table().find({{"id", id}}, &ent))
        return false;

    return true;
}

bool Buddha::_is_master_exist_by_proof(const string& proof,master& ent){
    if (!get_master_table().find({{"proof", proof}}, &ent))
        return false;

    return true;
}

bool Buddha::_is_master(const string& id) {
    master ent;
    if (!_is_master_exist(id, ent))
        return false;

    return ent.approved();
}

bool Buddha::_scan_master(xchain::json& v, const string& cond) {
    auto it = get_master_table().scan({{"id",cond}});
    while(it->next() ) {
        master ent;
        if (!it->get(&ent) ) {
            mycout << "master table get failure : " << it->error(true) << endl;
            return false;
        }

        v.push_back(ent.to_json());
    }

    return true;
}

bool Buddha::_delete_master_record(const string& id) {
    master ent;
    if (!_is_master_exist(id, ent)){
        mycout << "master " << id << " is not exist ." << endl ;
        return false;
    }

    if( !get_master_table().del(ent) ) {
        mycout << "delete master " << ent.to_string() << " failure ." << endl ;
        return false;
    }

    mycout << "delete master " << ent.to_string() << " success ." << endl ;
    return true;
}

namespace 分界线{}

void Buddha::apply_master(){
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
        _log_error(__FILE__, __FUNCTION__, __LINE__,ctx->initiator() + " is not user, have no authority to apply  master .");
        return ;
    }

    //判断是否已经是法师
    if( is_master() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__,ctx->initiator() + " is already master .");
        return ;
    }

    //判断此寺院是否存在
    master ent;
    if( _is_master_exist(ctx->initiator(),ent) ) {
        _log_ok(__FILE__, __FUNCTION__, __LINE__, "master " + ctx->initiator() + " is applying .", ent.to_json() );
        return ;
    }

    ent.set_id(ctx->initiator());
    ent.set_creditcode(creditcode);
    ent.set_proof(proof);
    ent.set_approved(false);
    if (!get_master_table().put(ent) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "table put failure .", ent.to_json());
        return;
    }

    _log_ok(__FILE__, __FUNCTION__, __LINE__, ctx->initiator() + " apply master over, please wait for approve .");
}

void Buddha::approve_master() {
    const string& id = ctx->arg("id");
    if( id.empty() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "master id is empty .");
        return ;
    }

    //判断是否是基金会成员
    if( !is_founder() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__,ctx->initiator() + " is not founder, have no authority to approve master .");
        return ;
    }

    //判断此法师是否存在
    master ent;
    if( !_is_master_exist(id,ent) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "master " + id + " is not exist .");
        return ;
    }

    //判断是否是法师
    if( _is_master(id) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, id + " is already master .", ent.to_json() );
        return ;
    }

    //删除此法师
    if( !_delete_master_record(id) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "delete failure .", ent.to_json());
        return;
    }

    //授权
    ent.set_approved(true);
    if (!get_master_table().put(ent) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "table put failure .", ent.to_json());
        return;
    }

    _log_ok(__FILE__, __FUNCTION__, __LINE__, "approve master " + id + " success .", ent.to_json() );
}

void Buddha::recusal_master() {
    const string& id = ctx->arg("id");
    if( id.empty() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "master id is empty .");
        return ;
    }

    //判断是否是基金会成员
    if( !is_founder() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__,ctx->initiator() + " is not founder, have no authority to recusal master .");
        return ;
    }

    //判断此法师是否存在
    master ent;
    if( !_is_master_exist(id,ent) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "master " + id + " is not exist .");
        return ;
    }

    //删除此法师
    if( !_delete_master_record(id) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "delete failure .", ent.to_json());
        return;
    }

    _log_ok(__FILE__, __FUNCTION__, __LINE__, "recusal master " + id + " success .", ent.to_json() );
}

bool Buddha::is_master() {
    if (!_is_master(ctx->initiator()) ) {
        _log_ok(__FILE__, __FUNCTION__, __LINE__, ctx->initiator() + " is not master .") ;
        return false;
    }
    
    _log_ok(__FILE__, __FUNCTION__, __LINE__, ctx->initiator() + " is master .") ;
    return true;
}

void Buddha::list_master() {
    //身份检查，部署者和基金会成员具有权限
    if( !is_deployer() &&
        !is_founder() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__,ctx->initiator() + " is not deployer nor founder, have no authority to list master .");
        return ;
    }

    xchain::json v ;
    if(!_scan_master(v, ctx->arg("id")) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "scan table failure .");
        return;
    }

    _log_ok(__FILE__, __FUNCTION__, __LINE__, "scan", v);
}


DEFINE_METHOD(Buddha, apply_master)             { self.apply_master();              }
DEFINE_METHOD(Buddha, approve_master)           { self.approve_master();            }
DEFINE_METHOD(Buddha, recusal_master)           { self.recusal_master();            }
DEFINE_METHOD(Buddha, is_master)                { self.is_master();                 }
DEFINE_METHOD(Buddha, list_master)              { self.list_master();               }