#include <inttypes.h>
#include "xchain/xchain.h"
#include "xchain/account.h"
#include "xchain/contract.pb.h"
#include "xchain/syscall.h"
#include "buddha.pb.h"
#include "buddha.h"

#include <iostream>
using namespace std;

xchain::json BOrder::to_json() const {
    xchain::json j = {
        {"id", id()},
        {"owner", owner()},
        {"kdowner", kdowner()},
        {"kdid", kdid()},
        {"specid", specid()},
        {"count", count()},
        {"amount", amount()},
        {"timestamp", timestamp()},
    };

    return j;
}

bool Main::_is_order_exist(order& ent, const string& id) {
    if (!get_order_table().find({{"id", id}}, &ent))
        return false;

    return true;
}

bool Main::_is_user(const string& id) {
    if( _is_deployer(id)) 
        return false;

    if( _is_founder(id)) 
        return false;

    if( _is_temple(id)) 
        return false;

    if( _is_master(id)) 
        return false;

    return true ;
}

bool Main::_scan_order_by_id(xchain::json& ja, const string& cond) {
    auto it = get_order_table().scan({{"id",cond}});
    while(it->next() ) {
        order ent;
        if (!it->get(&ent) ) {
            mycout << "order table get failure : " << it->error(true) << endl;
            return false;
        }

        ja.push_back(ent.to_json());
    }

    return true;
}

bool Main::_scan_order_by_kdowner(xchain::json& ja, const string& cond) {
    auto it = get_order_table().scan({{"kdowner",cond}});
    while(it->next() ) {
        order ent;
        if (!it->get(&ent) ) {
            mycout << "order table get failure : " << it->error(true) << endl;
            return false;
        }

        ja.push_back(ent.to_json());
    }

    return true;
}

bool Main::_delete_order_record(const string& id) {
    //判断订单是否存在
    order ent;
    if( !_is_order_exist(ent, id)){
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

void Main::pray_kinddeed() {

    const string& orderid = ctx->arg("id");
    if( orderid.empty() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "orderid is empty .");
        return ;
    }

    const string& kdid = ctx->arg("kinddeed");
    if( kdid.empty() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "kdid is empty .");
        return ;
    }

    const string& specid = ctx->arg("spec");
    if( specid.empty() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "specid is empty .");
        return ;
    }

    const string& count = ctx->arg("count");
    if( count.empty() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "count is empty .");
        return ;
    }

    const string& amount = ctx->transfer_amount();
    if( amount.empty() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "amount is empty .");
        return ;
    }

    const string& timestamp = ctx->arg("timestamp");
    if( timestamp.empty() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "timestamp is empty .");
        return ;
    }

    //判断订单是否存在
    order od;
    if (_is_order_exist(od, orderid))  {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "order " + orderid + " is exist .", od.to_json() );
        return ;
    }

    //判断善举是否存在
    kinddeed kd;
    if (!_is_kinddeed_exist(kd, kdid))  {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "kinddeed " + kdid + " is not exist .");
        return ;
    }

    //判断善举是否已经上架
    if (!_is_kinddeed_online(kdid) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "kinddeed " + kdid + " is not online .");
        return ;
    }

    //判断善举规格是否存在
    kinddeedspec spec;
    if (!_is_kinddeedspec_exist(spec, kdid, specid))  {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "kinddeedspec " + kdid + "," + specid + " is not exist .");
        return ;
    }

    //计算总价格，要求转账过来的总价格跟订单计算出的总价格要求必须一直
    int64_t calced_amount = spec.price() * stoll(count);
    if( calced_amount != stoll(amount)){
        _log_error(__FILE__, __FUNCTION__, __LINE__, "delive amount " + amount
                   + ", real amount=" + to_string(calced_amount));
        return;
    }
    
    od.set_id(orderid);
    od.set_owner(ctx->initiator());
    od.set_kdowner(kd.owner());
    od.set_kdid(kdid);
    od.set_specid(stoll(specid));
    od.set_count(stoll(count));
    od.set_amount(calced_amount);
    od.set_timestamp(timestamp);
    if (!get_order_table().put(od) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "order table put failure .", od.to_json());
        return;
    }
    
    _log_ok(__FILE__, __FUNCTION__, __LINE__, od.to_json());
}

void Main::delete_pray_kinddeed() {

    const string& orderid = ctx->arg("id");
    if( orderid.empty() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "orderid is empty .");
        return ;
    }

    //判断订单是否存在
    order ent;
    if (!_is_order_exist(ent, orderid))  {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "order " + orderid + " is not exist .");
        return ;
    }

    //身份检查，部署者，基金会成员，善举所有者，购买者具有权限
    if( !is_deployer() &&
        !is_founder() &&
        ctx->initiator() != ent.kdowner() &&
        ctx->initiator() != ent.owner() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__,ctx->initiator() + " have no authority to delete the pray kinddeed .");
        return ;
    }

    //删除此订单
    if( !_delete_order_record(orderid) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "delete failure .", ent.to_json());
        return;
    }

    _log_ok(__FILE__, __FUNCTION__, __LINE__, "delete", ent.to_json());
}

void Main::find_pray_kinddeed() {
    const string& id = ctx->arg("id");
    if( id.empty() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "order id is empty .");
        return ;
    }

    //判断订单是否存在
    order ent;       
    if (!_is_order_exist(ent, id) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "order " + id + " is not exist .");
        return ;
    }

    //身份检查，部署者，基金会成员，寺院，法师，购买者具有权限
    if( !is_deployer() &&
        !is_founder() &&
        !is_temple() &&
        !is_master() &&
        ent.owner() != ctx->initiator() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__,ctx->initiator() + " have no authority to find pray kinddeed .");
        return ;
    }

    _log_ok(__FILE__, __FUNCTION__, __LINE__, "find", ent.to_json());
}

void Main::list_pray_kinddeed() {
    //身份检查，合约部署者和基金会成员可以查看所有订单
    if( is_deployer() || 
        is_founder() ) {
        xchain::json ja ;
        if(!_scan_order_by_id(ja,ctx->arg("id")) ) {
            _log_error(__FILE__, __FUNCTION__, __LINE__, "scan table failure .");
            return;
        }

        _log_ok(__FILE__, __FUNCTION__, __LINE__, "scan", ja);
        return ;
    }

    //身份检查，寺院和法师只能查看属于自己善举的所有订单
    if( is_temple() || 
        is_master() ) {
        xchain::json ja ;
        if(!_scan_order_by_kdowner(ja,ctx->initiator()) ) {
            _log_error(__FILE__, __FUNCTION__, __LINE__, "scan table failure .");
            return;
        }
        
        _log_ok(__FILE__, __FUNCTION__, __LINE__, "scan", ja);
        return ;
    }

    _log_error(__FILE__, __FUNCTION__, __LINE__,ctx->initiator() + " have no authority to list order .");
}

bool Main::is_user() {
    if (!_is_user(ctx->initiator()) ) {
        _log_ok(__FILE__, __FUNCTION__, __LINE__, ctx->initiator() + " is not user .") ;
        return false;
    }

    _log_ok(__FILE__, __FUNCTION__, __LINE__, ctx->initiator() + " is user .") ;
    return true;
}


DEFINE_METHOD(Main, pray_kinddeed)            { self.pray_kinddeed();             }
DEFINE_METHOD(Main, delete_pray_kinddeed)     { self.delete_pray_kinddeed();      }
DEFINE_METHOD(Main, find_pray_kinddeed)       { self.find_pray_kinddeed();        }
DEFINE_METHOD(Main, list_pray_kinddeed)       { self.list_pray_kinddeed();        }
DEFINE_METHOD(Main, is_user)                  { self.is_user();                   }