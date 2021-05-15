#include <inttypes.h>
#include "xchain/xchain.h"
#include "xchain/account.h"
#include "xchain/contract.pb.h"
#include "xchain/syscall.h"
#include "sell.pb.h"
#include "sell.h"

#include <iostream>
using namespace std;
    
xchain::json BSell::to_json() const {
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

bool Otc::_is_sell_exist(sell& ent, const string& id){
    if (!get_sell_table().find({{"id", id}}, &ent))
        return false;

    return true;
}

bool Otc::_is_sell_exist_by_amount(sell& ent, const string& amount){
    if (!get_sell_table().find({{"amount", amount}}, &ent))
        return false;

    return true;
}

bool Otc::_is_sell(const string& id) {
    sell ent;
    if (!_is_sell_exist(ent, id))
        return false;

    return ent.left();
}

bool Otc::_scan_sell(xchain::json& ja, const string& cond) {
    auto it = get_sell_table().scan({{"id",cond}});
    while(it->next() ) {
        sell ent;
        if (!it->get(&ent) ) {
            mycout << "sell table get failure : " << it->error(true) << endl;
            return false;
        }

        ja.push_back(ent.to_json());
    }

    return true;
}

bool Otc::_delete_sell_record(const string& id) {
    sell ent;
    if (!_is_sell_exist(ent, id)){
        mycout << "sell " << id << " is not exist ." << endl ;
        return false;
    }

    if( !get_sell_table().del(ent) ) {
        mycout << "delete sell " << ent.to_json().dump() << " failure ." << endl ;
        return false;
    }

    mycout << "delete sell " << ent.to_json().dump() << " success ." << endl ;
    return true;
}

namespace 分界线{}

void Otc::apply_sell(){
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
        _log_error(__FILE__, __FUNCTION__, __LINE__,ctx->initiator() + " is not user, have no authority to apply  sell .");
        return ;
    }

    //判断是否已经是法师
    if( is_sell() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__,ctx->initiator() + " is already sell .");
        return ;
    }

    //判断此抵押是否存在
    sell ent;
    if( _is_sell_exist(ent, ctx->initiator()) ) {
        _log_ok(__FILE__, __FUNCTION__, __LINE__, "sell " + ctx->initiator() + " is applying .", ent.to_json() );
        return ;
    }

    ent.set_id(ctx->initiator());
    ent.set_seller(seller);
    ent.set_amount(amount);
    ent.set_left(false);
    if (!get_sell_table().put(ent) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "sell table put failure .", ent.to_json());
        return;
    }

    _log_ok(__FILE__, __FUNCTION__, __LINE__, ctx->initiator() + " apply sell over, please wait for approve .");
}

void Otc::approve_sell() {
    const string& id = ctx->arg("id");
    if( id.empty() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "sell id is empty .");
        return ;
    }

    //判断是否是基金会成员
    if( !is_founder() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__,ctx->initiator() + " is not founder, have no authority to approve sell .");
        return ;
    }

    //判断此法师是否存在
    sell ent;
    if( !_is_sell_exist(ent, id) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "sell " + id + " is not exist .");
        return ;
    }

    //判断是否是法师
    if( _is_sell(id) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, id + " is already sell .", ent.to_json() );
        return ;
    }

    //删除此法师
    if( !_delete_sell_record(id) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "delete failure .", ent.to_json());
        return;
    }

    //授权
    ent.set_left(true);
    if (!get_sell_table().put(ent) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "sell table put failure .", ent.to_json());
        return;
    }

    _log_ok(__FILE__, __FUNCTION__, __LINE__, "approve sell " + id + " success .", ent.to_json() );
}

void Otc::recusal_sell() {
    const string& id = ctx->arg("id");
    if( id.empty() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "sell id is empty .");
        return ;
    }

    //判断是否是基金会成员
    if( !is_founder() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__,ctx->initiator() + " is not founder, have no authority to recusal sell .");
        return ;
    }

    //判断此法师是否存在
    sell ent;
    if( !_is_sell_exist(ent, id) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "sell " + id + " is not exist .");
        return ;
    }

    //删除此法师
    if( !_delete_sell_record(id) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "delete failure .", ent.to_json());
        return;
    }

    _log_ok(__FILE__, __FUNCTION__, __LINE__, "delete", ent.to_json() );
}

bool Otc::is_sell() {
    if (!_is_sell(ctx->initiator()) ) {
        _log_ok(__FILE__, __FUNCTION__, __LINE__, ctx->initiator() + " is not sell .") ;
        return false;
    }
    
    _log_ok(__FILE__, __FUNCTION__, __LINE__, ctx->initiator() + " is sell .") ;
    return true;
}

void Otc::list_sell() {
    //身份检查，部署者和基金会成员具有权限
    if( !is_deployer() &&
        !is_founder() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__,ctx->initiator() + " is not deployer nor founder, have no authority to list sell .");
        return ;
    }

    xchain::json ja ;
    if(!_scan_sell(ja, ctx->arg("id")) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "scan table failure .");
        return;
    }

    _log_ok(__FILE__, __FUNCTION__, __LINE__, "scan", ja);
}


DEFINE_METHOD(Otc, apply_sell)             { self.apply_sell();              }
DEFINE_METHOD(Otc, approve_sell)           { self.approve_sell();            }
DEFINE_METHOD(Otc, recusal_sell)           { self.recusal_sell();            }
DEFINE_METHOD(Otc, is_sell)                { self.is_sell();                 }
DEFINE_METHOD(Otc, list_sell)              { self.list_sell();               }