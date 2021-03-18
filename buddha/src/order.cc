#include <inttypes.h>
#include "xchain/xchain.h"
#include "xchain/account.h"
#include "xchain/contract.pb.h"
#include "xchain/syscall.h"
#include "buddha.pb.h"
#include "buddha.h"

#include <iostream>
using namespace std;

string order::to_string() {
    string str ;
    str += "{" ;
    str += id() + ",";
    str += owner() + ",";
    str += kdowner() + ",";
    str += kdid() + ",";
    str += std::to_string(specid()) + ",";
    str += std::to_string(count()) + ",";
    str += std::to_string(amount()) + ",";
    str += timestamp() ;
    str += "}";
    return str;
}

xchain::json order::to_json() {
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

bool Buddha::_is_order_exist(const string& id,order& ent) {
    if (!get_order_table().find({{"id", id}}, &ent))
        return false;

    return true;
}

bool Buddha::_is_user(const string& id) {
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

bool Buddha::_scan_order_by_id(xchain::json& v, const string& cond) {
    auto it = get_order_table().scan({{"id",cond}});
    while(it->next()) {
        order ent;
        if (!it->get(&ent)) {
            mycout << "order table get failure : " << it->error(true) << endl;
            return false;
        }

        v.push_back(ent.to_json());
    }

    return true;
}

bool Buddha::_scan_order_by_kdowner(xchain::json& v, const string& cond) {
    auto it = get_order_table().scan({{"kdowner",cond}});
    while(it->next()) {
        order ent;
        if (!it->get(&ent)) {
            mycout << "order table get failure : " << it->error(true) << endl;
            return false;
        }

        v.push_back(ent.to_json());
    }

    return true;
}

bool Buddha::_delete_order_record(const string& id) {
    //判断订单是否存在
    order ent;
    if( !_is_order_exist(id, ent)){
        mycout << "order " << id << " is not exist ." << endl ;
        return false;
    }

    if( !get_order_table().del(ent)) {
        mycout << "delete order " << ent.to_string() << " failure ." << endl ;
        return false;
    }

    mycout << "delete order " << ent.to_string() << " success ." << endl ;
    return true;
}

namespace 分界线{}

void Buddha::pray_kinddeed() {

    const string& orderid = ctx->arg("id");
    if( orderid.empty()) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "orderid is empty .");
        return ;
    }

    const string& kdid = ctx->arg("kinddeed");
    if( kdid.empty()) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "kdid is empty .");
        return ;
    }

    const string& specid = ctx->arg("spec");
    if( specid.empty()) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "specid is empty .");
        return ;
    }

    const string& count = ctx->arg("count");
    if( count.empty()) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "count is empty .");
        return ;
    }

    const string& amount = ctx->transfer_amount();
    if( amount.empty()) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "amount is empty .");
        return ;
    }

    const string& timestamp = ctx->arg("timestamp");
    if( timestamp.empty()) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "timestamp is empty .");
        return ;
    }

    //判断订单是否存在
    order od;
    if (_is_order_exist(orderid,od))  {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "order " + orderid + " is exist .");
        return ;
    }

    //判断善举是否存在
    kinddeed kd;
    if (!_is_kinddeed_exist(kdid, kd))  {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "kinddeed " + kdid + " is not exist .");
        return ;
    }

    //判断善举是否已经上架
    if (!_is_kinddeed_online(kdid)) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "kinddeed " + kdid + " is not online .");
        return ;
    }

    //判断善举规格是否存在
    kinddeedspec spec;
    if (!_is_kinddeedspec_exist(kdid, specid, spec))  {
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
    if (!get_order_table().put(od)) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "table put failure .", od.to_json());
        return;
    }
    
    _log_ok(__FILE__, __FUNCTION__, __LINE__, od.to_json());
}

void Buddha::delete_pray_kinddeed() {

    const string& orderid = ctx->arg("id");
    if( orderid.empty()) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "orderid is empty .");
        return ;
    }

    //判断订单是否存在
    order ent;
    if (!_is_order_exist(orderid,ent))  {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "order " + orderid + " is not exist .");
        return ;
    }

    //判断身份
    //判断是否是订单所有者，判断是否是善举所有者，判断是否是基金会成员或部署
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

    _log_ok(__FILE__, __FUNCTION__, __LINE__, "create success .", ent.to_json());
}

void Buddha::find_pray_kinddeed() {
    const string& id = ctx->arg("id");
    if( id.empty()) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "order id is empty .");
        return ;
    }

    //判断订单是否存在
    order ent;       
    if (!_is_order_exist(id, ent)) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "order " + id + " is not exist .");
        return ;
    }

    if( !is_deployer() &&
        !is_founder() &&
        !is_temple() &&
        !is_master() &&
        ent.owner() != ctx->initiator()) {
        _log_error(__FILE__, __FUNCTION__, __LINE__,ctx->initiator() + " have no authority to find pray kinddeed .");
        return ;
    }

    _log_ok(__FILE__, __FUNCTION__, __LINE__, ent.to_string());
}

void Buddha::list_pray_kinddeed() {
    if( is_deployer() || 
        is_founder() ) {
        xchain::json v ;
        if(!_scan_order_by_id(v,ctx->arg("id")) ) {
            _log_error(__FILE__, __FUNCTION__, __LINE__, "scan table failure .");
            return;
        }

        _log_ok(__FILE__, __FUNCTION__, __LINE__, v);
        return ;
    }

    if( is_temple() || 
        is_master()) {
        xchain::json v ;
        if(!_scan_order_by_kdowner(v,ctx->initiator()) ) {
            _log_error(__FILE__, __FUNCTION__, __LINE__, "scan table failure .");
            return;
        }
        
        _log_ok(__FILE__, __FUNCTION__, __LINE__, v);
        return ;
    }

    _log_error(__FILE__, __FUNCTION__, __LINE__,ctx->initiator() + " have no authority to list order .");
}

bool Buddha::is_user() {
    if (!_is_user(ctx->initiator())) {
        _log_ok(__FILE__, __FUNCTION__, __LINE__, ctx->initiator() + " is not user .") ;
        return false;
    }

    _log_ok(__FILE__, __FUNCTION__, __LINE__, ctx->initiator() + " is user .") ;
    return true;
}


DEFINE_METHOD(Buddha, pray_kinddeed)            { self.pray_kinddeed();             }
DEFINE_METHOD(Buddha, delete_pray_kinddeed)     { self.delete_pray_kinddeed();      }
DEFINE_METHOD(Buddha, find_pray_kinddeed)       { self.find_pray_kinddeed();        }
DEFINE_METHOD(Buddha, list_pray_kinddeed)       { self.list_pray_kinddeed();        }
DEFINE_METHOD(Buddha, is_user)                  { self.is_user();                   }