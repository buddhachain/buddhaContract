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

void Buddha::apply_online_kinddeed() {
    const string& id = ctx->arg("id");
    if( id.empty()) {
        _log_error(__FUNCTION__, __LINE__,"kinddeed id is empty .");
        return ;
    }

    if( !is_temple() &&
        !is_master() ) {
        _log_error(__FUNCTION__, __LINE__,ctx->initiator() + " is not temple nor master, have no authority to apply online kinddeed .");
        return ;
    }

    //判断善举是否存在
    kinddeed ent;
    if (!_is_kinddeed_exist(id, ent))  {
        _log_error(__FUNCTION__, __LINE__,"kinddeed " + id + " is not exist .");
        return ;
    }

    if (ent.online()==true){
        _log_error(__FUNCTION__, __LINE__,"kinddeed " + ent.to_string() + " is already online .");
        return ;
    }

    if( ent.owner() != ctx->initiator() ) {
        _log_error(__FUNCTION__, __LINE__,"kinddeed " + ent.to_string() + " is not belong to you .");
        return ;
    }

    //删除此善举
    if( !_delete_kinddeed_record(id) ) {
        _log_error(__FUNCTION__, __LINE__,"delete kinddeed " + ent.to_string() + " failure .");
        return;
    }

    ent.set_applied(true);
    if (!get_kinddeed_table().put(ent)) {
        _log_error(__FUNCTION__, __LINE__,"kinddeed table put " + ent.to_string() + " failure .");
        return;
    }

    _log_ok(__FUNCTION__, __LINE__, "kinddeed " + ent.to_string() + " apply online over, please wait for approve .");
}

void Buddha::apply_offline_kinddeed() {
    const string& id = ctx->arg("id");
    if( id.empty()) {
        _log_error(__FUNCTION__, __LINE__,"kinddeed id is empty .");
        return ;
    }

    if( !is_temple() &&
        !is_master() ) {
        _log_error(__FUNCTION__, __LINE__,ctx->initiator() + " is not temple nor master, have no authority to apply offline kinddeed .");
        return ;
    }

    //判断善举是否存在
    kinddeed ent;
    if (!_is_kinddeed_exist(id, ent))  {
        _log_error(__FUNCTION__, __LINE__,"kinddeed " + id + " is not exist .");
        return ;
    }

    if (ent.online()==false){
        _log_error(__FUNCTION__, __LINE__,"kinddeed " + ent.to_string() + " is already offline .");
        return ;
    }

    if( ent.owner() != ctx->initiator() ) {
        _log_error(__FUNCTION__, __LINE__,"kinddeed " + ent.to_string() + " is not belong to you .");
        return ;
    }

    //删除此善举
    if( !_delete_kinddeed_record(id) ) {
        _log_error(__FUNCTION__, __LINE__,"delete kinddeed " + ent.to_string() + " failure .");
        return;
    }

    ent.set_applied(true);
    if (!get_kinddeed_table().put(ent)) {
        _log_error(__FUNCTION__, __LINE__,"kinddeed table put " + ent.to_string() + " failure .");
        return;
    }

    _log_ok(__FUNCTION__, __LINE__, "kinddeed " + ent.to_string() + " apply offline over, please wait for approve .");
}

void Buddha::approve_online_kinddeed() {
    const string& id = ctx->arg("id");
    if( id.empty()) {
        _log_error(__FUNCTION__, __LINE__,"kinddeed id is empty .");
        return ;
    }

    if( !is_founder()) {
        _log_error(__FUNCTION__, __LINE__,ctx->initiator() + " is not founder, have no authority to approve online kinddeed .");
        return ;
    }

    //判断善举是否存在
    kinddeed ent;
    if (!_is_kinddeed_exist(id, ent))  {
        _log_error(__FUNCTION__, __LINE__,"kinddeed " + id + " is not exist .");
        return ;
    }

    if (ent.online()==true){
        _log_error(__FUNCTION__, __LINE__,"kinddeed " + ent.to_string() + " is already online .");
        return ;
    }

    if (ent.applied()==false)  {
        _log_error(__FUNCTION__, __LINE__,"kinddeed " + ent.to_string() + " is not apply online .");
        return ;
    }

    //删除此善举
    if( !_delete_kinddeed_record(id) ) {
        _log_error(__FUNCTION__, __LINE__,"delete kinddeed " + ent.to_string() + " failure .");
        return;
    }

    ent.set_applied(false);
    ent.set_online(true);
    if (!get_kinddeed_table().put(ent)) {
        _log_error(__FUNCTION__, __LINE__,"kinddeed table put " + ent.to_string() + " failure .");
        return;
    }

    _log_ok(__FUNCTION__, __LINE__, "approve kinddeed " + ent.to_string() + " online success .");
}

void Buddha::approve_offline_kinddeed() {
    const string& id = ctx->arg("id");
    if( id.empty()) {
        _log_error(__FUNCTION__, __LINE__,"kinddeed id is empty .");
        return ;
    }

    if( !is_founder()) {
        _log_error(__FUNCTION__, __LINE__,ctx->initiator() + " is not founder, have no authority to approve offline kinddeed .");
        return ;
    }

    //判断善举是否存在
    kinddeed ent;
    if (!_is_kinddeed_exist(id, ent))  {
        _log_error(__FUNCTION__, __LINE__,"kinddeed " + id + " is not exist .");
        return ;
    }

    if (ent.online()==false){
        _log_error(__FUNCTION__, __LINE__,"kinddeed " + ent.to_string() + " is already offline .");
        return ;
    }

    if (ent.applied()==false)  {
        _log_error(__FUNCTION__, __LINE__,"kinddeed " + ent.to_string() + " is not apply offline .");
        return ;
    }

    //删除此善举
    if( !_delete_kinddeed_record(id) ) {
        _log_error(__FUNCTION__, __LINE__,"delete kinddeed " + ent.to_string() + " failure .");
        return;
    }

    ent.set_applied(false);
    ent.set_online(false);
    if (!get_kinddeed_table().put(ent)) {
        _log_error(__FUNCTION__, __LINE__,"kinddeed table put " + ent.to_string() + " failure .");
        return;
    }

    _log_ok(__FUNCTION__, __LINE__, "approve kinddeed " + ent.to_string() + " offline success .");
}

DEFINE_METHOD(Buddha, apply_online_kinddeed)    { self.apply_online_kinddeed();     }
DEFINE_METHOD(Buddha, apply_offline_kinddeed)   { self.apply_offline_kinddeed();    }
DEFINE_METHOD(Buddha, approve_online_kinddeed)  { self.approve_online_kinddeed();   }
DEFINE_METHOD(Buddha, approve_offline_kinddeed) { self.approve_offline_kinddeed();  }
