#include <inttypes.h>
#include "xchain/xchain.h"
#include "xchain/account.h"
#include "xchain/contract.pb.h"
#include "xchain/syscall.h"

#include "buy_order.pb.h"
#include "buy_order.h"
#include "main.h"

#include <iostream>
using namespace std;

xchain::json BCBuyOrder::to_json() const {
    xchain::json j = {
        {"id", id()},
        {"sellid", sellid()},
        {"buyer", buyer()},
        {"amount", amount()},
        {"state", state()},
        {"start_timestamp", start_timestamp()},
        {"confirm_timestamp", confirm_timestamp()},
    };

    return j;
}

bool Main::_is_buyorder_exist(BCBuyOrder& ent, const string& id){
    if (!get_buyorder_table().find({{"id", id}}, &ent))
        return false;

    return true;
}

bool Main::_scan_buyorder(xchain::json& ja, const string& id) {
    auto it = get_buyorder_table().scan({{"id", id}});
    while(it->next() ) {
        BCBuyOrder ent;
        if (!it->get(&ent) ) {
            mycout << "buyorder table get failure : " << it->error(true) << endl;
            return false;
        }

        ja.push_back(ent.to_json());
    }

    return true;
}

bool Main::_delete_buyorder_record(const string& id) {
    BCBuyOrder ent;
    if (!_is_buyorder_exist(ent, id)){
        mycout << "order " << id << " is not exist ." << endl ;
        return false;
    }

    if( !get_buyorder_table().del(ent) ) {
        mycout << "delete order " << ent.to_json().dump() << " failure ." << endl ;
        return false;
    }

    mycout << "delete order " << ent.to_json().dump() << " success ." << endl ;
    return true;
}

namespace 分界线{}

void Main::buy(){
    const string& id = ctx->arg("id");
    if( id.empty() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "id is empty .");
        return ;
    }

    const string& sellid = ctx->arg("sellid");
    if( sellid.empty() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "sellid is empty .");
        return ;
    }

    const string& buyer = ctx->initiator();

    const string& amount = ctx->arg("amount");
    if( amount.empty() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "amount is empty .");
        return ;
    }

    const string& timestamp = ctx->arg("timestamp");
    if( timestamp.empty() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "timestamp is empty .");
        return ;
    }

    //判断此订单是否存在
    BCBuyOrder ent;
    if( _is_buyorder_exist(ent, id) ) {
        _log_ok(__FILE__, __FUNCTION__, __LINE__, "buy order " + id + " is exist .", ent.to_json() );
        return ;
    }

    ent.set_id(id);
    ent.set_sellid(sellid);
    ent.set_buyer(buyer);
    ent.set_amount(stoll(amount));
    ent.set_state(START);
    ent.set_start_timestamp(timestamp);
    //ent.set_confirm_timestamp(confirm_timestamp);
    if (!get_buyorder_table().put(ent) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "buy order table put failure .", ent.to_json());
        return;
    }

    _log_ok(__FILE__, __FUNCTION__, __LINE__, "order is setting up, please pay for it in 15 minutes .");
}

void Main::confirm_buy() {
    const string& id = ctx->arg("id");
    if( id.empty() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "order id is empty .");
        return ;
    }

    const string& timestamp = ctx->arg("timestamp");
    if( timestamp.empty() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "timestamp is empty .");
        return ;
    }

    const string& seller = ctx->initiator();

    //判断当前身份是否是认证用户
    if( !_is_identifyuser(seller) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, seller + " is not a identify user ." );
        return ;
    }

    //商家判断当前的卖单id是否属于自己的
    //通过订单id， 去查询 buyorder 表中的 卖单id
    //通过卖单id， 去查询 sell 表中的 商家id
    //判断 当前的调用者 是否时对的 商家

    //判断此订单是否存在
    BCBuyOrder buyorderEntry;
    if( !_is_buyorder_exist(buyorderEntry, id) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "order " + id + " is not exist .");
        return ;
    }

    BBSell sellEntry;
    if( !_is_sell_exist(sellEntry, buyorderEntry.sellid()) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "sell " + buyorderEntry.sellid() + " is not exist .");
        return ;
    }

    if( seller != sellEntry.account() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "order " + id + " is not belong to you .");
        return ;
    }

    //判断此订单是否已经确认过
    if( buyorderEntry.state() == CONFIRM ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "order " + id + " is confirmed .", buyorderEntry.to_json());
        return ;
    }


    //写商家卖单表
    if( sellEntry.left() < buyorderEntry.amount() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "order amount(" + std::to_string(buyorderEntry.amount()) + ") error, seller only (" + std::to_string(sellEntry.left()) + ") left .");
        return ;
    }

    sellEntry.set_left(sellEntry.left() - buyorderEntry.amount());

    //删除此卖单表记录
    if( !_delete_sell_record(sellEntry.id()) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "delete sell table record failure .", sellEntry.to_json());
        return;
    }

    //存储
    if (!get_sell_table().put(sellEntry) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "sell table put failure .", sellEntry.to_json());
        return;
    }


    //写客户购买订单表
    buyorderEntry.set_state(CONFIRM);
    buyorderEntry.set_confirm_timestamp(timestamp);

    //删除此购买订单
    if( !_delete_buyorder_record(id) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "delete failure .", buyorderEntry.to_json());
        return;
    }

    //存储
    if (!get_buyorder_table().put(buyorderEntry) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "buy order table put failure .", buyorderEntry.to_json());
        return;
    }

    //执行转账
    if( !_transfer( buyorderEntry.buyer(), std::to_string(buyorderEntry.amount())) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__,
            "transfer to " + buyorderEntry.buyer() + 
            " amount(" + std::to_string(buyorderEntry.amount()) + ") failure .");
        return ;
    }

    _log_ok(__FILE__, __FUNCTION__, __LINE__, "buy order " + id + " confirm success .", buyorderEntry.to_json() );
}

void Main::recusal_buy() {
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

    //判断此认证用户是否存在
    BCBuyOrder ent;
    if( !_is_buyorder_exist(ent, id) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "order " + id + " is not exist .");
        return ;
    }

    //删除此认证用户
    if( !_delete_buyorder_record(id) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "delete failure .", ent.to_json());
        return;
    }

    _log_ok(__FILE__, __FUNCTION__, __LINE__, "delete", ent.to_json() );
}

bool Main::is_buyorder() {
    if (!_is_buyorder(ctx->initiator()) ) {
        _log_ok(__FILE__, __FUNCTION__, __LINE__, ctx->initiator() + " is not order .") ;
        return false;
    }
    
    _log_ok(__FILE__, __FUNCTION__, __LINE__, ctx->initiator() + " is order .") ;
    return true;
}

void Main::list_buyorder() {
    //身份检查，部署者和基金会成员具有权限
    if( !is_deployer() &&
        !is_founder() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__,ctx->initiator() + " is not deployer nor founder, have no authority to list order .");
        return ;
    }

    xchain::json ja ;
    if(!_scan_buyorder(ja, ctx->arg("id")) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "scan table failure .");
        return;
    }

    _log_ok(__FILE__, __FUNCTION__, __LINE__, "scan", ja);
}


DEFINE_METHOD(Main, apply_order)             { self.buy();              }
DEFINE_METHOD(Main, approve_order)           { self.confirm_buy();      }
DEFINE_METHOD(Main, recusal_order)           { self.recusal_buy();      }
DEFINE_METHOD(Main, is_order)                { self.is_buyorder();      }
DEFINE_METHOD(Main, list_order)              { self.list_buyorder();    }