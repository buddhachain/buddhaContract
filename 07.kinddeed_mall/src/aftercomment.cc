#include <inttypes.h>
#include "xchain/xchain.h"
#include "xchain/account.h"
#include "xchain/contract.pb.h"
#include "xchain/syscall.h"
#include "buddha.pb.h"
#include "buddha.h"

#include <iostream>
using namespace std;

xchain::json BAfterComment::to_json() const {
    xchain::json j = {
        {"orderid", orderid()},
        {"owner", owner()},
        {"comment", comment()},
        {"timestamp", timestamp()},
    };

    return j;
}

bool Main::_is_aftercomment_exist(aftercomment& ent,
                                    const string& orderid,
                                    const string& owner) {
    if (!get_aftercomment_table().find({{"orderid", orderid}, {"owner", owner}}, &ent))
        return false;

    return true;
}

bool Main::_scan_aftercomment_by_orderid(xchain::json& ja, const string& cond) {
    auto it = get_aftercomment_table().scan({{"orderid",cond}});
    while(it->next() ) {
        aftercomment ent;
        if (!it->get(&ent) ) {
            mycout << "aftercomment table get failure : " << it->error(true) << endl;
            return false;
        }

        ja.push_back(ent.to_json());
    }

    return true;
}

bool Main::_delete_aftercomment_record(const string& orderid, const string& owner) {
    aftercomment ent;
    if (!_is_aftercomment_exist(ent,orderid,owner)){
        mycout << "aftercomment " << orderid << " is not exist ." << endl ;
        return false;
    }

    if( !get_aftercomment_table().del(ent) ) {
        mycout << "delete aftercomment " << ent.to_json().dump() << " failure ." << endl ;
        return false;
    }

    mycout << "delete aftercomment " << ent.to_json().dump() << " success ." << endl ;
    return true;
}

namespace 分界线{}

void Main::add_aftercomment() {
    const string& orderid = ctx->arg("orderid");
    if( orderid.empty() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "aftercomment orderid is empty .");
        return ;
    }

    const string& comment = ctx->arg("comment");
    if( comment.empty() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "aftercomment comment is empty .");
        return ;
    }

    const string& timestamp = ctx->arg("timestamp");
    if( timestamp.empty() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "aftercomment timestamp is empty .");
        return ;
    }

    const string& owner = ctx->initiator() ;

    //判断此评论是否已经存在
    aftercomment ent;
    if( _is_aftercomment_exist(ent,orderid,owner) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "aftercomment " + orderid + " is exist .", ent.to_json() );
        return ;
    }

    //判断订单是否存在
    order od;        
    if (!_is_order_exist(od, orderid))  {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "order " + orderid + " is not exist .");
        return ;
    }

    //判断订单的所有者是否是当前的评论者
    if( od.owner() != owner ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "order " + orderid + " is not belong to you .");
        return ;
    }

    ent.set_orderid(orderid);
    ent.set_owner(owner);
    ent.set_comment(comment);
    ent.set_timestamp(timestamp);
    if (!get_aftercomment_table().put(ent) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "aftercomment table put failure .", ent.to_json());
        return;
    }

    _log_ok(__FILE__, __FUNCTION__, __LINE__, "create", ent.to_json());
}

void Main::delete_aftercomment() {
    const string& orderid = ctx->arg("orderid");
    if( orderid.empty() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "aftercomment orderid is empty .");
        return ;
    }

    const string& owner = ctx->initiator();

    //判断此评论是否已经存在
    aftercomment ent;
    if( !_is_aftercomment_exist(ent,orderid,owner) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "aftercomment " + orderid + " is not exist .");
        return ;
    }

    //判断订单是否存在
    order od;        
    if (!_is_order_exist(od, orderid))  {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "order " + orderid + " is not exist .");
        return ;
    }

    //身份检查，基金会成员，订单所有者具有权限
    if( !is_founder() &&
        ent.owner() != owner) {
        _log_error(__FILE__, __FUNCTION__, __LINE__,ctx->initiator() + " is not founder nor owner, have no authority to delete the comment .");
        return ;
    }

    //删除此善举售后评论
    if( !_delete_aftercomment_record(orderid,owner) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "delete failure .", ent.to_json());
        return;
    }

    _log_ok(__FILE__, __FUNCTION__, __LINE__, "delete", ent.to_json());
}

void Main::update_aftercomment() {
    const string& orderid = ctx->arg("orderid");
    if( orderid.empty() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "aftercomment orderid is empty .");
        return ;
    }

    const string& comment = ctx->arg("comment");
    if( comment.empty() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "aftercomment comment is empty .");
        return ;
    }

    const string& timestamp = ctx->arg("timestamp");
    if( timestamp.empty() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "aftercomment timestamp is empty .");
        return ;
    }

    const string& owner = ctx->initiator() ;

    //判断此评论是否已经存在
    aftercomment ent;
    if( !_is_aftercomment_exist(ent,orderid,owner) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "kindeed type " + orderid + " is not exist .");
        return ;
    }

    //判断订单是否存在
    order od;        
    if (!_is_order_exist(od, orderid))  {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "order " + orderid + " is not exist .");
        return ;
    }

    if( ent.owner() != owner) {
        _log_error(__FILE__, __FUNCTION__, __LINE__,ctx->initiator() + " is not owner, have no authority to update the comment .");
        return ;
    }

    //删除此善举售后评论
    if( !_delete_aftercomment_record(orderid,owner) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "delete failure .", ent.to_json());
        return;
    }

    ent.set_orderid(orderid);
    ent.set_owner(owner);
    ent.set_comment(comment);
    ent.set_timestamp(timestamp);
    if (!get_aftercomment_table().put(ent) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "aftercomment table put failure .", ent.to_json());
        return;
    }

    _log_ok(__FILE__, __FUNCTION__, __LINE__, "update", ent.to_json());
}

void Main::find_aftercomment() {
    const string& orderid = ctx->arg("orderid");
    if( orderid.empty() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "aftercomment orderid is empty .");
        return ;
    }

    //判断订单是否存在
    order od;        
    if (!_is_order_exist(od, orderid))  {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "order " + orderid + " is not exist .");
        return ;
    }

    //身份检查，基金会成员，订单所有者，善举所有者具有权限
    if( !is_founder() &&
        od.owner() != ctx->initiator() &&
        od.kdowner() != ctx->initiator() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__,ctx->initiator() + " have no authority to update the comment .");
        return ;
    }

    //判断此评论是否已经存在
    aftercomment ent;
    if (!_is_aftercomment_exist(ent, orderid, od.owner()))  {
        _log_ok(__FILE__, __FUNCTION__, __LINE__, "aftercomment " + orderid + " is not exist .");
        return ;
    }

    _log_ok(__FILE__, __FUNCTION__, __LINE__, "find", ent.to_json());
}

void Main::list_aftercomment() {
    const string& orderid = ctx->arg("orderid");

    //身份检查，部署者，基金会成员具有权限
    if( is_deployer() ||
        is_founder() ) {
        xchain::json ja ;
        if(!_scan_aftercomment_by_orderid(ja, orderid) ) {
            _log_error(__FILE__, __FUNCTION__, __LINE__, "scan table failure .");
            return;
        }

        _log_ok(__FILE__, __FUNCTION__, __LINE__, "scan", ja);
        return;
    }

    //非合约部署者和基金会成员，orderid不能为空，即禁止其他角色遍历所有售后评论记录
    if( orderid.empty() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "aftercomment orderid is empty .");
        return ;
    }

    //判断订单是否存在
    order od;        
    if (!_is_order_exist(od, orderid))  {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "order " + orderid + " is not exist .");
        return ;
    }

    xchain::json ja ;
    if(!_scan_aftercomment_by_orderid(ja, orderid) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "scan table failure .");
        return;
    }
    _log_ok(__FILE__, __FUNCTION__, __LINE__, "scan", ja);
}


DEFINE_METHOD(Main, add_aftercomment)         { self.add_aftercomment();          }
DEFINE_METHOD(Main, delete_aftercomment)      { self.delete_aftercomment();       }
DEFINE_METHOD(Main, update_aftercomment)      { self.update_aftercomment();       }
DEFINE_METHOD(Main, find_aftercomment)        { self.find_aftercomment();         }
DEFINE_METHOD(Main, list_aftercomment)        { self.list_aftercomment();         }

