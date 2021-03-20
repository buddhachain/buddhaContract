#include <inttypes.h>
#include "xchain/xchain.h"
#include "xchain/account.h"
#include "xchain/contract.pb.h"
#include "xchain/syscall.h"
#include "buddha.pb.h"
#include "buddha.h"

#include <iostream>
using namespace std;

namespace 分界线{}

void Buddha::apply_online_kinddeed() {
    const string& id = ctx->arg("id");
    if( id.empty() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "kinddeed id is empty .");
        return ;
    }

    //身份检查，判断是否是寺院，法师
    if( !is_temple() &&
        !is_master() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__,ctx->initiator() + " is not temple nor master, have no authority to apply online kinddeed .");
        return ;
    }

    //判断善举是否存在
    kinddeed ent;
    if (!_is_kinddeed_exist(id, ent))  {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "kinddeed " + id + " is not exist .");
        return ;
    }

    if (ent.online()==true){
        _log_error(__FILE__, __FUNCTION__, __LINE__, "kinddeed " + id + " is already online .", ent.to_json() );
        return ;
    }

    if( ent.owner() != ctx->initiator() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "kinddeed " + id + " is not belong to you .", ent.to_json() );
        return ;
    }

    //删除此善举
    if( !_delete_kinddeed_record(id) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "delete failure .", ent.to_json());
        return;
    }

    ent.set_applied(true);
    if (!get_kinddeed_table().put(ent) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "table put failure .", ent.to_json());
        return;
    }

    _log_ok(__FILE__, __FUNCTION__, __LINE__, "kinddeed " + id + " apply online over, please wait for approve .", ent.to_json() );
}

void Buddha::apply_offline_kinddeed() {
    const string& id = ctx->arg("id");
    if( id.empty() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "kinddeed id is empty .");
        return ;
    }

    //身份检查，判断是否是寺院，法师
    if( !is_temple() &&
        !is_master() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__,ctx->initiator() + " is not temple nor master, have no authority to apply offline kinddeed .");
        return ;
    }

    //判断善举是否存在
    kinddeed ent;
    if (!_is_kinddeed_exist(id, ent))  {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "kinddeed " + id + " is not exist .");
        return ;
    }

    if (ent.online()==false){
        _log_error(__FILE__, __FUNCTION__, __LINE__, "kinddeed " + id + " is already offline .", ent.to_json() );
        return ;
    }

    if( ent.owner() != ctx->initiator() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "kinddeed " + id + " is not belong to you .", ent.to_json() );
        return ;
    }

    //删除此善举
    if( !_delete_kinddeed_record(id) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "delete failure .", ent.to_json());
        return;
    }

    ent.set_applied(true);
    if (!get_kinddeed_table().put(ent) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "table put failure .", ent.to_json());
        return;
    }

    _log_ok(__FILE__, __FUNCTION__, __LINE__, "kinddeed " + id + " apply offline over, please wait for approve .", ent.to_json() );
}

void Buddha::approve_online_kinddeed() {
    const string& id = ctx->arg("id");
    if( id.empty() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "kinddeed id is empty .");
        return ;
    }

    //判断是否是基金会成员
    if( !is_founder() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__,ctx->initiator() + " is not founder, have no authority to approve online kinddeed .");
        return ;
    }

    //判断善举是否存在
    kinddeed ent;
    if (!_is_kinddeed_exist(id, ent))  {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "kinddeed " + id + " is not exist .");
        return ;
    }

    if (ent.online()==true){
        _log_error(__FILE__, __FUNCTION__, __LINE__, "kinddeed " + id + " is already online .", ent.to_json() );
        return ;
    }

    if (ent.applied()==false)  {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "kinddeed " + id + " is not apply online .", ent.to_json() );
        return ;
    }

    //删除此善举
    if( !_delete_kinddeed_record(id) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "delete failure .", ent.to_json());
        return;
    }

    ent.set_applied(false);
    ent.set_online(true);
    if (!get_kinddeed_table().put(ent) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "table put failure .", ent.to_json());
        return;
    }

    _log_ok(__FILE__, __FUNCTION__, __LINE__, "approve kinddeed " + id + " online success .", ent.to_json() );
}

void Buddha::approve_offline_kinddeed() {
    const string& id = ctx->arg("id");
    if( id.empty() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "kinddeed id is empty .");
        return ;
    }

    //判断是否是基金会成员
    if( !is_founder() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__,ctx->initiator() + " is not founder, have no authority to approve offline kinddeed .");
        return ;
    }

    //判断善举是否存在
    kinddeed ent;
    if (!_is_kinddeed_exist(id, ent))  {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "kinddeed " + id + " is not exist .");
        return ;
    }

    if (ent.online()==false){
        _log_error(__FILE__, __FUNCTION__, __LINE__, "kinddeed " + id + " is already offline .", ent.to_json() );
        return ;
    }

    if (ent.applied()==false)  {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "kinddeed " + id + " is not apply offline .", ent.to_json() );
        return ;
    }

    //删除此善举
    if( !_delete_kinddeed_record(id) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "delete failure .", ent.to_json());
        return;
    }

    ent.set_applied(false);
    ent.set_online(false);
    if (!get_kinddeed_table().put(ent) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "table put failure .", ent.to_json());
        return;
    }

    _log_ok(__FILE__, __FUNCTION__, __LINE__, "approve kinddeed " + id + " offline success .", ent.to_json() );
}

DEFINE_METHOD(Buddha, apply_online_kinddeed)    { self.apply_online_kinddeed();     }
DEFINE_METHOD(Buddha, apply_offline_kinddeed)   { self.apply_offline_kinddeed();    }
DEFINE_METHOD(Buddha, approve_online_kinddeed)  { self.approve_online_kinddeed();   }
DEFINE_METHOD(Buddha, approve_offline_kinddeed) { self.approve_offline_kinddeed();  }
