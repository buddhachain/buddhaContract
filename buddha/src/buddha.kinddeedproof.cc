#include <inttypes.h>
#include "xchain/json/json.h"
#include "xchain/xchain.h"
#include "xchain/account.h"
#include "xchain/contract.pb.h"
#include "xchain/syscall.h"
#include "buddha.pb.h"
#include "buddha.h"

#include <iostream>
using namespace std;

void Buddha::upload_kinddeedproof() {
    const string& orderid = ctx->arg("orderid");
    if( orderid.empty()) {
        _log_error(__FUNCTION__, __LINE__,"kinddeedproof orderid is empty .");
        return ;
    }

    const string& proof = ctx->arg("proof");
    if( proof.empty()) {
        _log_error(__FUNCTION__, __LINE__,"kinddeedproof hash is empty .");
        return ;
    }

    const string& timestamp = ctx->arg("timestamp");
    if( timestamp.empty()) {
        _log_error(__FUNCTION__, __LINE__,"kinddeedproof timestamp is empty .");
        return ;
    }

    //判断善举凭证是否已经存在
    kinddeedproof ent;
    if (_is_kinddeedproof_exist(orderid, ent))  {
        _log_error(__FUNCTION__, __LINE__,"kinddeedproof " + orderid + " is exist .");
        return ;
    }

    //判断订单是否存在
    order od;
    if (!_is_order_exist(orderid, od)) {
        _log_error(__FUNCTION__, __LINE__,"order and suborder lost, kinddeedproof " + orderid + " be delete .");
        return ;
    }
    
    if( od.kdowner() != ctx->initiator() ) {
        _log_error(__FUNCTION__, __LINE__,ctx->initiator() + " is not the right kinddeed owner, it should be " + od.kdowner());
        return ;
    }

    ent.set_orderid(orderid);
    ent.set_owner(ctx->initiator());
    ent.set_proof(proof);
    ent.set_timestamp(timestamp);
    ent.set_approved(false);
    if (!get_kinddeedproof_table().put(ent)) {
        _log_error(__FUNCTION__, __LINE__,"kinddeedproof table put " + ent.to_string() + " failure .");
        return;
    }

    _log_ok(__FUNCTION__, __LINE__, "apply kinddeed " + ent.to_string() + " proof over, please wait for approve .");
}

void Buddha::approve_kinddeedproof() {
    const string& orderid = ctx->arg("orderid");
    if( orderid.empty()) {
        _log_error(__FUNCTION__, __LINE__,"kinddeedproof orderid is empty .");
        return ;
    }

    if( !is_founder()) {
        _log_error(__FUNCTION__, __LINE__,ctx->initiator() + " is not founder, have no authority to approve kinddeedproof .");
        return ;
    }

    //判断善举凭证是否已经存在
    kinddeedproof ent;
    if (!_is_kinddeedproof_exist(orderid, ent))  {
        _log_error(__FUNCTION__, __LINE__,"kinddeedproof " + orderid + " is not exist .");
        return ;
    }

    //判断订单是否存在
    order od;
    if (!_is_order_exist(orderid, od)) {
        //删除此善举凭证
        _delete_kinddeedproof_record(orderid);
        _log_error(__FUNCTION__, __LINE__,"order and suborder lost, kinddeedproof " + orderid + " be delete .");
        return ;
    }

    if (ent.approved())  {
        _log_ok(__FUNCTION__, __LINE__, "kinddeedproof " + orderid + " has approved yet .");
        return ;
    }

    //判断善举是否存在
    kinddeed kd;
    if( !_is_kinddeed_exist(od.kdid(), kd)) {
        _log_error(__FUNCTION__, __LINE__,"kinddeed " + od.kdid() + " is not exist .");
        return ;
    }

    if( ent.owner() != od.kdowner() &&
        ent.owner() != kd.owner()) {
        _log_error(__FUNCTION__, __LINE__,ent.owner() +","+ od.kdowner() + "," + kd.owner() + " failure .");
        return ;
    }

    //删除此善举凭证
    if( !_delete_kinddeedproof_record(orderid) ) {
        _log_error(__FUNCTION__, __LINE__,"delete kinddeedproof " + ent.to_string() + " failure .");
        return;
    }

    ent.set_approved(true);
    if (!get_kinddeedproof_table().put(ent)) {
        _log_error(__FUNCTION__, __LINE__,"kinddeedproof table put " + ent.to_string() + " failure .");
        return;
    }

    if( !_transfer(ent.owner(), to_string(od.amount()))) {
        _log_error(__FUNCTION__, __LINE__,"transfer to " + ent.owner() + " " +  to_string(od.amount()) + " failure .");
        return ;
    }

    _log_ok(__FUNCTION__, __LINE__, "approve kinddeed " + ent.to_string() + " proof success .");
}

void Buddha::refuse_kinddeedproof() {
    const string& orderid = ctx->arg("orderid");
    if( orderid.empty()) {
        _log_error(__FUNCTION__, __LINE__,"kinddeedproof orderid is empty .");
        return ;
    }

    if( !is_founder()) {
        _log_error(__FUNCTION__, __LINE__,ctx->initiator() + " is not founder, have no authority to approve kinddeedproof .");
        return ;
    }

    //判断善举凭证是否已经存在
    kinddeedproof ent;
    if (!_is_kinddeedproof_exist(orderid, ent))  {
        _log_error(__FUNCTION__, __LINE__,"kinddeedproof " + orderid + " is not exist .");
        return ;
    }

    //判断订单是否存在
    order od;
    if (!_is_order_exist(orderid, od)) {
        //删除此善举凭证
        _delete_kinddeedproof_record(orderid);
        _log_error(__FUNCTION__, __LINE__,"order lost, kinddeedproof " + orderid + " be delete .");
        return ;
    }

    if (ent.approved())  {
        _log_ok(__FUNCTION__, __LINE__, "kinddeedproof " + orderid + " has approved yet .");
        return ;
    }

    //删除此善举凭证
    if( !_delete_kinddeedproof_record(orderid) ) {
        _log_error(__FUNCTION__, __LINE__,"delete kinddeedproof " + ent.to_string() + " failure .");
        return;
    }

    _log_ok(__FUNCTION__, __LINE__, "refuse kinddeed " + ent.to_string() + " proof success .");
}

void Buddha::find_kinddeedproof() {
    const string& orderid = ctx->arg("orderid");

    if( orderid.empty() ) {
        _log_error(__FUNCTION__, __LINE__,"kinddeedproof hash and orderid is empty .");
        return ;
    }

    //判断订单是否存在
    order od;        
    if (!_is_order_exist(orderid, od))  {
        _log_error(__FUNCTION__, __LINE__,"order " + orderid + " is not exist .");
        return ;
    }

    //判断善举凭证是否已经存在
    kinddeedproof ent;
    if (!_is_kinddeedproof_exist(orderid, ent))  {
        _log_error(__FUNCTION__, __LINE__,"kinddeedproof " + orderid + " is not exist .");
        return ;
    }
    
    if( !is_deployer() &&
        !is_founder() &&
        ent.owner() != ctx->initiator() ) {
        _log_error(__FUNCTION__, __LINE__,ctx->initiator() + " have no authority to find kinddeedproof .");
        return ;
    }

    _log_ok(__FUNCTION__, __LINE__, ent.to_string());
}

void Buddha::list_kinddeedproof() {
    if( is_deployer() ||
        is_founder()) {
        auto it = get_kinddeedproof_table().scan({{"orderid",ctx->arg("orderid")}});
        int i = 0;
        string ret;
        while(it->next()) {
            kinddeedproof ent;
            if (!it->get(&ent)) {
                _log_error(__FUNCTION__, __LINE__, "kinddeedproof table get failure : " + it->error(true));
                return;
            }

            i++;
            ret += ent.to_string();
        }
        _log_ok(__FUNCTION__, __LINE__, "size=" + to_string(i) + " " + ret);
        return;
    }

    if( is_temple() || 
        is_master()) {
        auto it = get_kinddeedproof_table().scan({{"owner",ctx->initiator()},{"orderid",ctx->arg("orderid")}});
        int i = 0;
        string ret;
        while(it->next()) {
            kinddeedproof ent;
            if (!it->get(&ent)) {
                _log_error(__FUNCTION__, __LINE__, "kinddeedproof table get failure : " + it->error(true));
                return;
            }

            i++;
            ret += ent.to_string();
        }
        _log_ok(__FUNCTION__, __LINE__, "size=" + to_string(i) + " " + ret);
        return;
    }

    _log_error(__FUNCTION__, __LINE__,ctx->initiator() + " have no authority to list kinddeedproof .");
    return ;
}


DEFINE_METHOD(Buddha, upload_kinddeedproof)     { self.upload_kinddeedproof();      }
DEFINE_METHOD(Buddha, approve_kinddeedproof)    { self.approve_kinddeedproof();     }
DEFINE_METHOD(Buddha, refuse_kinddeedproof)     { self.refuse_kinddeedproof();      }
DEFINE_METHOD(Buddha, find_kinddeedproof)       { self.find_kinddeedproof();        }
DEFINE_METHOD(Buddha, list_kinddeedproof)       { self.list_kinddeedproof();        }
