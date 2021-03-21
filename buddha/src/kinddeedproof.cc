#include <inttypes.h>
#include "xchain/xchain.h"
#include "xchain/account.h"
#include "xchain/contract.pb.h"
#include "xchain/syscall.h"
#include "buddha.pb.h"
#include "buddha.h"

#include <iostream>
using namespace std;


string kinddeedproof::to_string() {
    string str ;
    str += "{" ;
    str += orderid() + ",";
    str += owner() + ",";
    str += proof() + ",";
    str += timestamp() + ",";
    str += std::to_string(approved());
    str += "}";
    return str;
}

xchain::json kinddeedproof::to_json() {
    xchain::json j = {
        {"orderid", orderid()},
        {"owner", owner()},
        {"proof", proof()},
        {"timestamp", timestamp()},
        {"approved", approved()},
    };

    return j;
}

bool Buddha::_is_kinddeedproof_exist(const string& orderid,kinddeedproof& ent) {
    if (!get_kinddeedproof_table().find({{"orderid", orderid}}, &ent))
        return false;

    return true;
}

bool Buddha::_scan_kinddeedproof_by_orderid(xchain::json& v, const string& cond) {
    auto it = get_kinddeedproof_table().scan({{"orderid",cond}});
    while(it->next() ) {
        kinddeedproof ent;
        if (!it->get(&ent) ) {
            mycout << "kinddeedproof table get failure : " << it->error(true) << endl;
            return false;
        }

        v.push_back(ent.to_json());
    }

    return true;
}

bool Buddha::_scan_kinddeedproof_by_owner(xchain::json& v, const string& cond) {
    auto it = get_kinddeedproof_table().scan({{"owner",cond}});
    while(it->next() ) {
        kinddeedproof ent;
        if (!it->get(&ent) ) {
            mycout << "kinddeedproof table get failure : " << it->error(true) << endl;
            return false;
        }

        v.push_back(ent.to_json());
    }

    return true;
}

bool Buddha::_scan_kinddeedproof_by_owner_orderid(xchain::json& v, const string& owner, const string& orderid) {
    auto it = get_kinddeedproof_table().scan({{"owner",owner},{"orderid",orderid}});
    while(it->next() ) {
        kinddeedproof ent;
        if (!it->get(&ent) ) {
            mycout << "kinddeedproof table get failure : " << it->error(true) << endl;
            return false;
        }

        v.push_back(ent.to_json());
    }

    return true;
}

bool Buddha::_delete_kinddeedproof_record(const string& orderid) {
    kinddeedproof ent;
    if (!_is_kinddeedproof_exist(orderid, ent)){
        mycout << "kinddeedproof " << orderid << " is not exist ." << endl ;
        return false;
    }

    if( !get_kinddeedproof_table().del(ent) ) {
        mycout << "delete kinddeedproof " << ent.to_string() << " failure ." << endl ;
        return false;
    }

    mycout << "delete kinddeedproof " << ent.to_string() << " success ." << endl ;
    return true;
}

namespace 分界线{}

void Buddha::upload_kinddeedproof() {
    const string& orderid = ctx->arg("orderid");
    if( orderid.empty() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "kinddeedproof orderid is empty .");
        return ;
    }

    const string& proof = ctx->arg("proof");
    if( proof.empty() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "kinddeedproof hash is empty .");
        return ;
    }

    const string& timestamp = ctx->arg("timestamp");
    if( timestamp.empty() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "kinddeedproof timestamp is empty .");
        return ;
    }

    //判断善举凭证是否已经存在
    kinddeedproof ent;
    if (_is_kinddeedproof_exist(orderid, ent))  {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "kinddeedproof " + orderid + " is exist .", ent.to_json() );
        return ;
    }

    //判断订单是否存在
    order od;
    if (!_is_order_exist(orderid, od) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "order and suborder lost, kinddeedproof " + orderid + " be delete .");
        return ;
    }
    
    if( od.kdowner() != ctx->initiator() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__,ctx->initiator() + " is not the right kinddeed owner, it should be " + od.kdowner());
        return ;
    }

    ent.set_orderid(orderid);
    ent.set_owner(ctx->initiator());
    ent.set_proof(proof);
    ent.set_timestamp(timestamp);
    ent.set_approved(false);
    if (!get_kinddeedproof_table().put(ent) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "kinddeedproof table put " + orderid + " failure .", ent.to_json() );
        return;
    }

    _log_ok(__FILE__, __FUNCTION__, __LINE__, "apply kinddeed " + orderid + " proof over, please wait for approve .", ent.to_json());
}

void Buddha::approve_kinddeedproof() {
    const string& orderid = ctx->arg("orderid");
    if( orderid.empty() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "kinddeedproof orderid is empty .");
        return ;
    }

    //判断是否是基金会成员
    if( !is_founder() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__,ctx->initiator() + " is not founder, have no authority to approve kinddeedproof .");
        return ;
    }

    //判断善举凭证是否已经存在
    kinddeedproof ent;
    if (!_is_kinddeedproof_exist(orderid, ent))  {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "kinddeedproof " + orderid + " is not exist .");
        return ;
    }

    //判断订单是否存在
    order od;
    if (!_is_order_exist(orderid, od) ) {
        //删除此善举凭证
        _delete_kinddeedproof_record(orderid);
        _log_error(__FILE__, __FUNCTION__, __LINE__, "order and suborder lost, kinddeedproof " + orderid + " be delete .");
        return ;
    }

    if (ent.approved())  {
        _log_ok(__FILE__, __FUNCTION__, __LINE__, "kinddeedproof " + orderid + " has approved yet .");
        return ;
    }

    //判断善举是否存在
    kinddeed kd;
    if( !_is_kinddeed_exist(od.kdid(), kd) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "kinddeed " + od.kdid() + " is not exist .");
        return ;
    }

    if( ent.owner() != od.kdowner() &&
        ent.owner() != kd.owner() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__,ent.owner() +","+ od.kdowner() + "," + kd.owner() + " failure .");
        return ;
    }

    //删除此善举凭证
    if( !_delete_kinddeedproof_record(orderid) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "delete failure .", ent.to_json());
        return;
    }

    //授权
    ent.set_approved(true);
    if (!get_kinddeedproof_table().put(ent) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "kinddeedproof table put " + orderid + " failure .", ent.to_json());
        return;
    }

    if( !_transfer(ent.owner(), to_string(od.amount())) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "transfer to " + ent.owner() + " " +  to_string(od.amount()) + " failure .");
        return ;
    }

    _log_ok(__FILE__, __FUNCTION__, __LINE__, "approve kinddeed " + orderid + " proof success .", ent.to_json());
}

void Buddha::refuse_kinddeedproof() {
    const string& orderid = ctx->arg("orderid");
    if( orderid.empty() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "kinddeedproof orderid is empty .");
        return ;
    }

    //判断是否是基金会成员
    if( !is_founder() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__,ctx->initiator() + " is not founder, have no authority to approve kinddeedproof .");
        return ;
    }

    //判断善举凭证是否已经存在
    kinddeedproof ent;
    if (!_is_kinddeedproof_exist(orderid, ent))  {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "kinddeedproof " + orderid + " is not exist .");
        return ;
    }

    //判断订单是否存在
    order od;
    if (!_is_order_exist(orderid, od) ) {
        //删除此善举凭证
        _delete_kinddeedproof_record(orderid);
        _log_error(__FILE__, __FUNCTION__, __LINE__, "order lost, kinddeedproof " + orderid + " be delete .");
        return ;
    }

    if (ent.approved())  {
        _log_ok(__FILE__, __FUNCTION__, __LINE__, "kinddeedproof " + orderid + " has approved yet .");
        return ;
    }

    //删除此善举凭证
    if( !_delete_kinddeedproof_record(orderid) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "delete failure .", ent.to_json());
        return;
    }

    _log_ok(__FILE__, __FUNCTION__, __LINE__, "refuse kinddeed " + orderid + " proof success .", ent.to_json());
}

void Buddha::find_kinddeedproof() {
    const string& orderid = ctx->arg("orderid");

    if( orderid.empty() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "kinddeedproof hash and orderid is empty .");
        return ;
    }

    //判断订单是否存在
    order od;        
    if (!_is_order_exist(orderid, od))  {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "order " + orderid + " is not exist .");
        return ;
    }

    //判断善举凭证是否已经存在
    kinddeedproof ent;
    if (!_is_kinddeedproof_exist(orderid, ent))  {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "kinddeedproof " + orderid + " is not exist .");
        return ;
    }

    //身份检查，部署者，基金会成员，凭证所有者具有权限
    if( !is_deployer() &&
        !is_founder() &&
        ent.owner() != ctx->initiator() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__,ctx->initiator() + " have no authority to find kinddeedproof .");
        return ;
    }

    _log_ok(__FILE__, __FUNCTION__, __LINE__, ent.to_string());
}

void Buddha::list_kinddeedproof() {
    //身份检查，部署者和基金会成员可以查看所有善举凭证
    if( is_deployer() ||
        is_founder() ) {
        xchain::json v ;
        if(!_scan_kinddeedproof_by_orderid(v,ctx->arg("orderid")) ) {
            _log_error(__FILE__, __FUNCTION__, __LINE__, "scan table failure .");
            return;
        }

        _log_ok(__FILE__, __FUNCTION__, __LINE__, "scan", v);
        return;
    }

    //身份检查，寺院和法师只能查看属于自己善举的所有订单id的善举凭证
    if( is_temple() || 
        is_master() ) {
        xchain::json v ;
        if(!_scan_kinddeedproof_by_owner_orderid(v,ctx->initiator(),ctx->arg("orderid")) ) {
            _log_error(__FILE__, __FUNCTION__, __LINE__, "scan table failure .");
            return;
        }

        _log_ok(__FILE__, __FUNCTION__, __LINE__, "scan", v);
        return;
    }

    _log_error(__FILE__, __FUNCTION__, __LINE__,ctx->initiator() + " have no authority to list kinddeedproof .");
    return ;
}


DEFINE_METHOD(Buddha, upload_kinddeedproof)     { self.upload_kinddeedproof();      }
DEFINE_METHOD(Buddha, approve_kinddeedproof)    { self.approve_kinddeedproof();     }
DEFINE_METHOD(Buddha, refuse_kinddeedproof)     { self.refuse_kinddeedproof();      }
DEFINE_METHOD(Buddha, find_kinddeedproof)       { self.find_kinddeedproof();        }
DEFINE_METHOD(Buddha, list_kinddeedproof)       { self.list_kinddeedproof();        }
