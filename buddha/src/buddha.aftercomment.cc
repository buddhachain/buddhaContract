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


void Buddha::add_aftercomment() {
    const string& orderid = ctx->arg("orderid");
    if( orderid.empty()) {
        _log_error(__FUNCTION__, __LINE__,"aftercomment orderid is empty .");
        return ;
    }

    const string& comment = ctx->arg("comment");
    if( comment.empty()) {
        _log_error(__FUNCTION__, __LINE__,"aftercomment comment is empty .");
        return ;
    }

    const string& timestamp = ctx->arg("timestamp");
    if( timestamp.empty()) {
        _log_error(__FUNCTION__, __LINE__,"aftercomment timestamp is empty .");
        return ;
    }

    const string& owner = ctx->initiator() ;

    aftercomment ent;
    if( _is_aftercomment_exist(orderid,owner,ent)) {
        _log_error(__FUNCTION__, __LINE__,"aftercomment " + orderid + " is exist .");
        return ;
    }

    order od;        
    if (!_is_order_exist(orderid, od))  {
        _log_error(__FUNCTION__, __LINE__,"order " + orderid + " is not exist .");
        return ;
    }

    if( od.owner() != owner ) {
        _log_error(__FUNCTION__, __LINE__,"order " + orderid + " is not belong to you .");
        return ;
    }

    ent.set_orderid(orderid);
    ent.set_owner(owner);
    ent.set_comment(comment);
    ent.set_timestamp(timestamp);
    if (!get_aftercomment_table().put(ent)) {
        _log_error(__FUNCTION__, __LINE__,"aftercomment table put " + ent.to_string() + " failure .");
        return;
    }

    _log_ok("add aftercomment " + ent.to_string() + " success .");
}

void Buddha::delete_aftercomment() {
    const string& orderid = ctx->arg("orderid");
    if( orderid.empty()) {
        _log_error(__FUNCTION__, __LINE__,"aftercomment orderid is empty .");
        return ;
    }

    const string& owner = ctx->initiator();

    aftercomment ent;
    if( !_is_aftercomment_exist(orderid,owner,ent)) {
        _log_error(__FUNCTION__, __LINE__,"aftercomment " + orderid + " is not exist .");
        return ;
    }

    order od;        
    if (!_is_order_exist(orderid, od))  {
        _log_error(__FUNCTION__, __LINE__,"order " + orderid + " is not exist .");
        return ;
    }

    if( !is_founder() &&
        ent.owner() != owner) {
        _log_error(__FUNCTION__, __LINE__,ctx->initiator() + " is not founder nor owner, have no authority to delete the comment .");
        return ;
    }

    if( !_delete_aftercomment_record(orderid,owner) ) {
        _log_error(__FUNCTION__, __LINE__,"delete aftercomment " + ent.to_string() + " failure .");
        return;
    }

    _log_ok("delete aftercomment " + ent.to_string() + " success .");
}

void Buddha::update_aftercomment() {
    const string& orderid = ctx->arg("orderid");
    if( orderid.empty()) {
        _log_error(__FUNCTION__, __LINE__,"aftercomment orderid is empty .");
        return ;
    }

    const string& comment = ctx->arg("comment");
    if( comment.empty()) {
        _log_error(__FUNCTION__, __LINE__,"aftercomment comment is empty .");
        return ;
    }

    const string& timestamp = ctx->arg("timestamp");
    if( timestamp.empty()) {
        _log_error(__FUNCTION__, __LINE__,"aftercomment timestamp is empty .");
        return ;
    }

    const string& owner = ctx->initiator() ;

    aftercomment ent;
    if( !_is_aftercomment_exist(orderid,owner,ent)) {
        _log_error(__FUNCTION__, __LINE__,"kindeed type " + orderid + " is not exist .");
        return ;
    }

    order od;        
    if (!_is_order_exist(orderid, od))  {
        _log_error(__FUNCTION__, __LINE__,"order " + orderid + " is not exist .");
        return ;
    }

    if( ent.owner() != owner) {
        _log_error(__FUNCTION__, __LINE__,ctx->initiator() + " is not owner, have no authority to update the comment .");
        return ;
    }

    if( !_delete_aftercomment_record(orderid,owner) ) {
        _log_error(__FUNCTION__, __LINE__,"delete aftercomment " + ent.to_string() + " failure .");
        return;
    }

    ent.set_orderid(orderid);
    ent.set_owner(owner);
    ent.set_comment(comment);
    ent.set_timestamp(timestamp);
    if (!get_aftercomment_table().put(ent)) {
        _log_error(__FUNCTION__, __LINE__,"aftercomment table put " + ent.to_string() + " failure .");
        return;
    }

    _log_ok("update aftercomment " + ent.to_string() + " success .");
}

void Buddha::find_aftercomment() {
    const string& orderid = ctx->arg("orderid");
    if( orderid.empty()) {
        _log_error(__FUNCTION__, __LINE__,"aftercomment orderid is empty .");
        return ;
    }

    order od;        
    if (!_is_order_exist(orderid, od))  {
        _log_error(__FUNCTION__, __LINE__,"order " + orderid + " is not exist .");
        return ;
    }

    if( !is_founder() &&
        od.owner() != ctx->initiator() &&
        od.kdowner() != ctx->initiator()) {
        _log_error(__FUNCTION__, __LINE__,ctx->initiator() + " have no authority to update the comment .");
        return ;
    }

    aftercomment ent;
    if (!_is_aftercomment_exist(orderid,od.owner(),ent))  {
        _log_ok("aftercomment " + orderid + " is not exist .");
        return ;
    }

    _log_ok(ent.to_string());
}

void Buddha::list_aftercomment() {
    const string& orderid = ctx->arg("orderid");

    if( is_deployer() ||
        is_founder()) {
        auto it = get_aftercomment_table().scan({{"orderid",orderid}});
        int i = 0;
        string ret;
        while(it->next()) {
            aftercomment ent;
            if (!it->get(&ent)) {
                _log_error(__FUNCTION__, __LINE__, "aftercomment table get failure : " + it->error(true));
                return;
            }

            i++;
            ret += ent.to_string();
        }
        _log_ok("size=" + to_string(i) + " " + ret);
        return;
    }
    
    if( orderid.empty()) {
        _log_error(__FUNCTION__, __LINE__,"aftercomment orderid is empty .");
        return ;
    }

    order od;        
    if (!_is_order_exist(orderid, od))  {
        _log_error(__FUNCTION__, __LINE__,"order " + orderid + " is not exist .");
        return ;
    }

    auto it = get_aftercomment_table().scan({{"orderid",orderid}});
    int i = 0;
    string ret;
    while(it->next()) {
        aftercomment ent;
        if (!it->get(&ent)) {
            _log_error(__FUNCTION__, __LINE__, "aftercomment table get failure : " + it->error(true));
            return;
        }

        i++;
        ret += ent.to_string();
    }
    _log_ok("size=" + to_string(i) + " " + ret);

}


DEFINE_METHOD(Buddha, add_aftercomment)         { self.add_aftercomment();          }
DEFINE_METHOD(Buddha, delete_aftercomment)      { self.delete_aftercomment();       }
DEFINE_METHOD(Buddha, update_aftercomment)      { self.update_aftercomment();       }
DEFINE_METHOD(Buddha, find_aftercomment)        { self.find_aftercomment();         }
DEFINE_METHOD(Buddha, list_aftercomment)        { self.list_aftercomment();         }

