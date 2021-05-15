#include <inttypes.h>
#include "xchain/xchain.h"
#include "xchain/account.h"
#include "xchain/contract.pb.h"
#include "xchain/syscall.h"
#include "buddha.pb.h"
#include "buddha.h"

#include <iostream>
using namespace std;

xchain::json BMaster::to_json() const {
    xchain::json j = {
        {"id", id()},
        {"creditcode", creditcode()},
        {"proof", proof()},
        {"approved", approved()},
    };

    return j;
}

bool Main::_is_order_exist(BMaster& ent, const string& id){
    if (!get_order_table().find({{"id", id}}, &ent))
        return false;

    return true;
}

bool Main::_is_order_exist_by_proof(BMaster& ent, const string& proof){
    if (!get_order_table().find({{"proof", proof}}, &ent))
        return false;

    return true;
}

bool Main::_is_order(const string& id) {
    BMaster ent;
    if (!_is_order_exist(ent, id))
        return false;

    return ent.approved();
}

bool Main::_scan_order(xchain::json& ja, const string& cond) {
    auto it = get_order_table().scan({{"id",cond}});
    while(it->next() ) {
        BMaster ent;
        if (!it->get(&ent) ) {
            mycout << "order table get failure : " << it->error(true) << endl;
            return false;
        }

        ja.push_back(ent.to_json());
    }

    return true;
}

bool Main::_delete_order_record(const string& id) {
    BMaster ent;
    if (!_is_order_exist(ent, id)){
        mycout << "order " << id << " is not exist ." << endl ;
        return false;
    }

    if( !get_order_table().del(ent) ) {
        mycout << "delete order " << ent.to_json().dump() << " failure ." << endl ;
        return false;
    }

    mycout << "delete order " << ent.to_json().dump() << " success ." << endl ;
    return true;
}

namespace 分界线{}

void Main::apply_order(){
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
        _log_error(__FILE__, __FUNCTION__, __LINE__,ctx->initiator() + " is not user, have no authority to apply  order .");
        return ;
    }

    //判断是否已经是法师
    if( is_order() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__,ctx->initiator() + " is already order .");
        return ;
    }

    //判断此订单是否存在
    BMaster ent;
    if( _is_order_exist(ent, ctx->initiator()) ) {
        _log_ok(__FILE__, __FUNCTION__, __LINE__, "order " + ctx->initiator() + " is applying .", ent.to_json() );
        return ;
    }

    ent.set_id(ctx->initiator());
    ent.set_creditcode(creditcode);
    ent.set_proof(proof);
    ent.set_approved(false);
    if (!get_order_table().put(ent) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "order table put failure .", ent.to_json());
        return;
    }

    _log_ok(__FILE__, __FUNCTION__, __LINE__, ctx->initiator() + " apply order over, please wait for approve .");
}

void Main::approve_order() {
    const string& id = ctx->arg("id");
    if( id.empty() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "order id is empty .");
        return ;
    }

    //判断是否是基金会成员
    if( !is_founder() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__,ctx->initiator() + " is not founder, have no authority to approve order .");
        return ;
    }

    //判断此法师是否存在
    BMaster ent;
    if( !_is_order_exist(ent, id) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "order " + id + " is not exist .");
        return ;
    }

    //判断是否是法师
    if( _is_order(id) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, id + " is already order .", ent.to_json() );
        return ;
    }

    //删除此法师
    if( !_delete_order_record(id) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "delete failure .", ent.to_json());
        return;
    }

    //授权
    ent.set_approved(true);
    if (!get_order_table().put(ent) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "order table put failure .", ent.to_json());
        return;
    }

    _log_ok(__FILE__, __FUNCTION__, __LINE__, "approve order " + id + " success .", ent.to_json() );
}

void Main::recusal_order() {
    const string& id = ctx->arg("id");
    if( id.empty() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "order id is empty .");
        return ;
    }

    //判断是否是基金会成员
    if( !is_founder() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__,ctx->initiator() + " is not founder, have no authority to recusal order .");
        return ;
    }

    //判断此法师是否存在
    BMaster ent;
    if( !_is_order_exist(ent, id) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "order " + id + " is not exist .");
        return ;
    }

    //删除此法师
    if( !_delete_order_record(id) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "delete failure .", ent.to_json());
        return;
    }

    _log_ok(__FILE__, __FUNCTION__, __LINE__, "delete", ent.to_json() );
}

bool Main::is_order() {
    if (!_is_order(ctx->initiator()) ) {
        _log_ok(__FILE__, __FUNCTION__, __LINE__, ctx->initiator() + " is not order .") ;
        return false;
    }
    
    _log_ok(__FILE__, __FUNCTION__, __LINE__, ctx->initiator() + " is order .") ;
    return true;
}

void Main::list_order() {
    //身份检查，部署者和基金会成员具有权限
    if( !is_deployer() &&
        !is_founder() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__,ctx->initiator() + " is not deployer nor founder, have no authority to list order .");
        return ;
    }

    xchain::json ja ;
    if(!_scan_order(ja, ctx->arg("id")) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "scan table failure .");
        return;
    }

    _log_ok(__FILE__, __FUNCTION__, __LINE__, "scan", ja);
}


DEFINE_METHOD(Main, apply_order)             { self.apply_order();              }
DEFINE_METHOD(Main, approve_order)           { self.approve_order();            }
DEFINE_METHOD(Main, recusal_order)           { self.recusal_order();            }
DEFINE_METHOD(Main, is_order)                { self.is_order();                 }
DEFINE_METHOD(Main, list_order)              { self.list_order();               }