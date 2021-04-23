#include <inttypes.h>
#include "xchain/xchain.h"
#include "xchain/account.h"
#include "xchain/contract.pb.h"
#include "xchain/syscall.h"
#include "guaranty.pb.h"
#include "guaranty.h"

#include <iostream>
using namespace std;
    
xchain::json BGuaranty::to_json() {
    xchain::json j = {
        { "id",          id()        },
        { "seller",      seller()    },
        { "amount",      amount()    },
        { "left",        left()      },
        { "price",       price()     },
        { "timestamp",   timestamp() },
    };

    return j;
}

bool Otc::_is_guaranty_exist(guaranty& ent, const string& id){
    if (!get_guaranty_table().find({{"id", id}}, &ent))
        return false;

    return true;
}

bool Otc::_is_guaranty_exist_by_amount(guaranty& ent, const string& amount){
    if (!get_guaranty_table().find({{"amount", amount}}, &ent))
        return false;

    return true;
}

bool Otc::_is_guaranty(const string& id) {
    guaranty ent;
    if (!_is_guaranty_exist(ent, id))
        return false;

    return ent.left();
}

bool Otc::_scan_guaranty(xchain::json& ja, const string& cond) {
    auto it = get_guaranty_table().scan({{"id",cond}});
    while(it->next() ) {
        guaranty ent;
        if (!it->get(&ent) ) {
            mycout << "guaranty table get failure : " << it->error(true) << endl;
            return false;
        }

        ja.push_back(ent.to_json());
    }

    return true;
}

bool Otc::_delete_guaranty_record(const string& id) {
    guaranty ent;
    if (!_is_guaranty_exist(ent, id)){
        mycout << "guaranty " << id << " is not exist ." << endl ;
        return false;
    }

    if( !get_guaranty_table().del(ent) ) {
        mycout << "delete guaranty " << ent.to_json().dump() << " failure ." << endl ;
        return false;
    }

    mycout << "delete guaranty " << ent.to_json().dump() << " success ." << endl ;
    return true;
}

namespace 分界线{}

void Otc::apply_guaranty(){
    const string& seller = ctx->arg("seller");
    if( seller.empty() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "seller is empty .");
        return ;
    }

    const string& amount = ctx->arg("amount");
    if( amount.empty() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "amount is empty .");
        return ;
    }

    //身份检查，只有用户才能申请成为法师
    if( !is_user() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__,ctx->initiator() + " is not user, have no authority to apply  guaranty .");
        return ;
    }

    //判断是否已经是法师
    if( is_guaranty() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__,ctx->initiator() + " is already guaranty .");
        return ;
    }

    //判断此寺院是否存在
    guaranty ent;
    if( _is_guaranty_exist(ent, ctx->initiator()) ) {
        _log_ok(__FILE__, __FUNCTION__, __LINE__, "guaranty " + ctx->initiator() + " is applying .", ent.to_json() );
        return ;
    }

    ent.set_id(ctx->initiator());
    ent.set_seller(seller);
    ent.set_amount(amount);
    ent.set_left(false);
    if (!get_guaranty_table().put(ent) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "table put failure .", ent.to_json());
        return;
    }

    _log_ok(__FILE__, __FUNCTION__, __LINE__, ctx->initiator() + " apply guaranty over, please wait for approve .");
}

void Otc::approve_guaranty() {
    const string& id = ctx->arg("id");
    if( id.empty() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "guaranty id is empty .");
        return ;
    }

    //判断是否是基金会成员
    if( !is_founder() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__,ctx->initiator() + " is not founder, have no authority to approve guaranty .");
        return ;
    }

    //判断此法师是否存在
    guaranty ent;
    if( !_is_guaranty_exist(ent, id) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "guaranty " + id + " is not exist .");
        return ;
    }

    //判断是否是法师
    if( _is_guaranty(id) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, id + " is already guaranty .", ent.to_json() );
        return ;
    }

    //删除此法师
    if( !_delete_guaranty_record(id) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "delete failure .", ent.to_json());
        return;
    }

    //授权
    ent.set_left(true);
    if (!get_guaranty_table().put(ent) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "table put failure .", ent.to_json());
        return;
    }

    _log_ok(__FILE__, __FUNCTION__, __LINE__, "approve guaranty " + id + " success .", ent.to_json() );
}

void Otc::recusal_guaranty() {
    const string& id = ctx->arg("id");
    if( id.empty() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "guaranty id is empty .");
        return ;
    }

    //判断是否是基金会成员
    if( !is_founder() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__,ctx->initiator() + " is not founder, have no authority to recusal guaranty .");
        return ;
    }

    //判断此法师是否存在
    guaranty ent;
    if( !_is_guaranty_exist(ent, id) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "guaranty " + id + " is not exist .");
        return ;
    }

    //删除此法师
    if( !_delete_guaranty_record(id) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "delete failure .", ent.to_json());
        return;
    }

    _log_ok(__FILE__, __FUNCTION__, __LINE__, "delete", ent.to_json() );
}

bool Otc::is_guaranty() {
    if (!_is_guaranty(ctx->initiator()) ) {
        _log_ok(__FILE__, __FUNCTION__, __LINE__, ctx->initiator() + " is not guaranty .") ;
        return false;
    }
    
    _log_ok(__FILE__, __FUNCTION__, __LINE__, ctx->initiator() + " is guaranty .") ;
    return true;
}

void Otc::list_guaranty() {
    //身份检查，部署者和基金会成员具有权限
    if( !is_deployer() &&
        !is_founder() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__,ctx->initiator() + " is not deployer nor founder, have no authority to list guaranty .");
        return ;
    }

    xchain::json ja ;
    if(!_scan_guaranty(ja, ctx->arg("id")) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "scan table failure .");
        return;
    }

    _log_ok(__FILE__, __FUNCTION__, __LINE__, "scan", ja);
}


DEFINE_METHOD(Otc, apply_guaranty)             { self.apply_guaranty();              }
DEFINE_METHOD(Otc, approve_guaranty)           { self.approve_guaranty();            }
DEFINE_METHOD(Otc, recusal_guaranty)           { self.recusal_guaranty();            }
DEFINE_METHOD(Otc, is_guaranty)                { self.is_guaranty();                 }
DEFINE_METHOD(Otc, list_guaranty)              { self.list_guaranty();               }