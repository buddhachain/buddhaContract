#include <inttypes.h>
#include "xchain/xchain.h"
#include "xchain/account.h"
#include "xchain/contract.pb.h"
#include "xchain/syscall.h"
#include "master.h"
#include "main.h"

#include <iostream>
using namespace std;

xchain::json BMaster::to_json() const {
    xchain::json j = {
        {"id", id()},
        {"photo", photo()},
        {"buddhist_name", buddhist_name()},
        {"sect", sect()},
        {"creditcode", creditcode()},
        {"proof", proof()},
        {"approved", approved()},
    };

    return j;
}

bool Main::_is_master_exist(BMaster& ent, const string& id){
    if (!get_master_table().find({{"id", id}}, &ent))
        return false;

    return true;
}

bool Main::_is_master(const string& id) {
    BMaster ent;
    if (!_is_master_exist(ent, id))
        return false;

    return ent.approved();
}

bool Main::_scan_master(xchain::json& ja,
                        const string& id,
                        const string& buddhist_name,
                        const string& creditcode,
                        const string& proof) {
    auto it = get_master_table().scan({{"id",id},
                                       {"buddhist_name",buddhist_name},
                                       {"creditcode",creditcode},
                                       {"proof",proof}});
    while(it->next() ) {
        BMaster ent;
        if (!it->get(&ent) ) {
            mycout << "master table get failure : " << it->error(true) << endl;
            return false;
        }

        ja.push_back(ent.to_json());
    }

    return true;
}

bool Main::_delete_master_record(const BMaster& ent) {
    if( !get_master_table().del(ent) ) {
        mycout << "delete master " << ent.to_json().dump() << " failure ." << endl ;
        return false;
    }

    mycout << "delete master " << ent.to_json().dump() << " success ." << endl ;
    return true;
}

namespace 分界线{}

void Main::apply_master(){
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

    //判断此法师是否存在
    BMaster ent;
    if( _is_master_exist(ent, ctx->initiator()) ) {
        _log_ok(__FILE__, __FUNCTION__, __LINE__, "master " + ctx->initiator() + " is applying .", ent.to_json() );
        return ;
    }

    ent.set_id(ctx->initiator());
    ent.set_creditcode(creditcode);
    ent.set_proof(proof);
    ent.set_approved(false);
    if (!get_master_table().put(ent) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "master table put failure .", ent.to_json());
        return;
    }

    _log_ok(__FILE__, __FUNCTION__, __LINE__, ctx->initiator() + " apply master over, please wait for approve .");
}

void Main::approve_master() {
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
    BMaster ent;
    if( !_is_master_exist(ent, id) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "master " + id + " is not exist .");
        return ;
    }

    //判断是否是法师
    if( _is_master(id) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, id + " is already master .", ent.to_json() );
        return ;
    }

    //删除此法师
    if( !_delete_master_record(ent) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "delete failure .", ent.to_json());
        return;
    }

    //授权
    ent.set_approved(true);
    if (!get_master_table().put(ent) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "master table put failure .", ent.to_json());
        return;
    }

    _log_ok(__FILE__, __FUNCTION__, __LINE__, "approve master " + id + " success .", ent.to_json() );
}

void Main::recusal_master() {
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
    BMaster ent;
    if( !_is_master_exist(ent, id) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "master " + id + " is not exist .");
        return ;
    }

    //删除此法师
    if( !_delete_master_record(ent) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "delete failure .", ent.to_json());
        return;
    }

    _log_ok(__FILE__, __FUNCTION__, __LINE__, "delete", ent.to_json() );
}

bool Main::is_master() {
    if (!_is_master(ctx->initiator()) ) {
        _log_ok(__FILE__, __FUNCTION__, __LINE__, ctx->initiator() + " is not master .") ;
        return false;
    }
    
    _log_ok(__FILE__, __FUNCTION__, __LINE__, ctx->initiator() + " is master .") ;
    return true;
}

void Main::list_master() {
    //身份检查，部署者和基金会成员具有权限
    if( !is_deployer() &&
        !is_founder() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__,ctx->initiator() + " is not deployer nor founder, have no authority to list master .");
        return ;
    }

    xchain::json ja ;
    if(!_scan_master(ja, 
                     ctx->arg("id"),
                     ctx->arg("buddhist_name"),
                     ctx->arg("creditcode"),
                     ctx->arg("proof")) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "scan table failure .");
        return;
    }

    _log_ok(__FILE__, __FUNCTION__, __LINE__, "scan", ja);
}


DEFINE_METHOD(Main, apply_master)             { self.apply_master();              }
DEFINE_METHOD(Main, approve_master)           { self.approve_master();            }
DEFINE_METHOD(Main, recusal_master)           { self.recusal_master();            }
DEFINE_METHOD(Main, is_master)                { self.is_master();                 }
DEFINE_METHOD(Main, list_master)              { self.list_master();               }