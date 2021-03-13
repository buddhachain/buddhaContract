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

#define mycout cout << __func__ << "[" << __LINE__ << "] " 


namespace pb = xchain::contract::sdk;

Buddha::Buddha() :
    _founder_table(         context(), "founder"                ),
    _temple_table(          context(), "temple"                 ),
    _master_table(          context(), "master"                 ),
    _templemaster_table(    context(), "templemaster"           ),
    _kinddeedtype_table(    context(), "kinddeedtype"           ),
    _kinddeed_table(        context(), "kinddeed"               ),
    _kinddeeddetail_table(  context(), "kinddeeddetail"         ),
    _kinddeedspec_table(    context(), "kinddeedspec"           ),
    _commentlabel_table(    context(), "commentlabel"           ),
    _beforecomment_table(   context(), "beforecomment"          ),
    _order_table(           context(), "order"                  ),
    _kinddeedproof_table(   context(), "kinddeedproof"          ),
    _aftercomment_table(    context(), "aftercomment"           ),

    ctx(context())
{
}





void Buddha::_log_error(string fun, int line, string str) {
    cout << fun << "[" << line << "] " << str << endl;
    ctx->error(str);
}

bool Buddha::_is_founder_exist(const string& id,founder& ent) {
    if (!get_founder_table().find({{"id", id}}, &ent))
        return false;

    return true;
}

bool Buddha::_is_temple_exist(const string& id,temple& ent){
    if (!get_temple_table().find({{"id", id}}, &ent))
        return false;

    return true;
}

bool Buddha::_is_temple_exist_by_unit(const string& unit,temple& ent){
    if (!get_temple_table().find({{"unit", unit}}, &ent))
        return false;

    return true;
}

bool Buddha::_is_temple_exist_by_creditcode(const string& creditcode,temple& ent){
    if (!get_temple_table().find({{"creditcode", creditcode}}, &ent))
        return false;

    return true;
}

bool Buddha::_is_temple_exist_by_address(const string& address,temple& ent){
    if (!get_temple_table().find({{"address", address}}, &ent))
        return false;

    return true;
}

bool Buddha::_is_temple_exist_by_proof(const string& proof,temple& ent){
    if (!get_temple_table().find({{"proof", proof}}, &ent))
        return false;

    return true;
}

bool Buddha::_is_master_exist(const string& id,master& ent){
    if (!get_master_table().find({{"id", id}}, &ent))
        return false;

    return true;
}

bool Buddha::_is_master_exist_by_proof(const string& proof,master& ent){
    if (!get_master_table().find({{"proof", proof}}, &ent))
        return false;

    return true;
}

bool Buddha::_is_templemaster_exist(const string& templeid,
                                    const string& masterid,
                                    templemaster& ent){
    if (!get_templemaster_table().find({{"templeid", templeid},{"masterid", masterid}}, &ent))
        return false;

    return true;
}

bool Buddha::_is_kinddeedtype_exist(const string& id,kinddeedtype& ent) {
    if (!get_kinddeedtype_table().find({{"id", id}}, &ent))
        return false;

    return true;
}

bool Buddha::_is_kinddeed_exist(const string& id,kinddeed& ent) {
    if (!get_kinddeed_table().find({{"id", id}}, &ent))
        return false;

    return true;
}

bool Buddha::_is_kinddeeddetail_exist(const string& kdid,
                                       const string& seq,
                                       kinddeeddetail& ent) {
    if (!get_kinddeeddetail_table().find({{"kdid", kdid},{"sequence",seq}}, &ent))
        return false;

    return true;
}


bool Buddha::_is_kinddeeddetail_exist_by_kdid(const string& kdid,vector<kinddeeddetail>& vent) {
    auto it = get_kinddeeddetail_table().scan({{"kdid",kdid}});
    while(it->next()) {
        kinddeeddetail ent;
        if (!it->get(&ent)) {
            if(it->error(true) == "success") 
                return false;
            mycout << "kinddeeddetail table get failure : " << it->error(true) << endl;
            return false;
        }
        vent.push_back(ent);
    }

    if( vent.size()==0)
        return false;

    return true;
}

bool Buddha::_is_kinddeedspec_exist(const string& kdid,
                                       const string& seq,
                                       kinddeedspec& ent) {
    if (!get_kinddeedspec_table().find({{"kdid", kdid},{"sequence",seq}}, &ent))
        return false;

    return true;
}

bool Buddha::_is_kinddeedspec_exist_by_kdid(const string& kdid,vector<kinddeedspec>& vent) {
    auto it = get_kinddeedspec_table().scan({{"kdid",kdid}});
    while(it->next()) {
        kinddeedspec ent;
        if (!it->get(&ent)) {
            if(it->error(true) == "success") 
                return false;
            mycout << "kinddeedspec table get failure : " << it->error(true) << endl;
            return false;
        }

        vent.push_back(ent);
    }

    if( vent.size()==0)
        return false;

    return true;
}

bool Buddha::_is_commentlabel_exist(const string& id,commentlabel& ent) {
    if (!get_commentlabel_table().find({{"id", id}}, &ent))
        return false;

    return true;
}

bool Buddha::_is_all_types_exist_in_commentlabel(const xchain::json& label_array) {
    for(int i = 0 ; i < label_array.size() ; i++) {
        string id = label_array.at(i).template get<string>();
        commentlabel ent;
        if( !_is_commentlabel_exist(id,ent)) {
            mycout << "type " << id << " not exist in commentlabel table ." << endl;
            return false;
        }            
    }

    return true;
}

bool Buddha::_is_beforecomment_exist(const string& kdid, const string& owner,beforecomment& ent) {
    if (!get_beforecomment_table().find({{"kdid", kdid},{"owner", owner}}, &ent))
        return false;

    return true;
}

bool Buddha::_is_order_exist(const string& id,order& ent) {
    if (!get_order_table().find({{"id", id}}, &ent))
        return false;

    return true;
}

bool Buddha::_is_kinddeedproof_exist(const string& orderid,kinddeedproof& ent) {
    if (!get_kinddeedproof_table().find({{"orderid", orderid}}, &ent))
        return false;

    return true;
}

bool Buddha::_is_aftercomment_exist(const string& orderid, const string& owner, aftercomment& ent) {
    if (!get_aftercomment_table().find({{"orderid", orderid}, {"owner", owner}}, &ent))
        return false;

    return true;
}


bool Buddha::_get_kinddeed(const string& id,kinddeed& ent) {
    return get_kinddeed_table().find({{"id", id}}, &ent);
}

bool Buddha::_is_kinddeed_online(const string& id){
    kinddeed ent;
    if (!get_kinddeed_table().find({{"id", id}}, &ent)) {
        mycout << "kinddeed " << id << " is not exist ." << endl;
        return false;
    }

    if( ent.applied() == true) {
        mycout << "kinddeed " << id << " is apply status change ." << endl;
        return false;
    }

    if( ent.online() != true ) {
        mycout << "kinddeed " << id << " is not online ." << endl;
        return false;
    }

    return true;

}



bool Buddha::_is_deployer(const string& id) {
    string deployer;
    if (!ctx->get_object("deployer", &deployer)) 
        return false;

    if (deployer != id )
        return false;

    return true ;
}

bool Buddha::_is_founder(const string& id) {
    founder ent;
    if (!_is_founder_exist(id, ent))
        return false;
    
    return ent.approved();
}

bool Buddha::_is_temple(const string& id) {
    temple ent;
    if (!_is_temple_exist(id, ent))
        return false;
    
    return ent.approved();
}

bool Buddha::_is_master(const string& id) {
    master ent;
    if (!_is_master_exist(id, ent))
        return false;

    return ent.approved();
}

bool Buddha::_is_in_temple(const string& templeid,
                           const string& masterid,
                           templemaster& ent){
    if (!get_templemaster_table().find({{"templeid", templeid},{"masterid", masterid}}, &ent))
        return false;

    return ent.approved();
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


bool Buddha::_delete_founder_record(const string& id) {
    founder ent;
    if (!_is_founder_exist(id, ent)){
        mycout << "founder " << id << " is not exist ." << endl ;
        return false;
    }

    if( !get_founder_table().del(ent) ) {
        mycout << "delete founder " << ent.to_string() << " failure ." << endl ;
        return false;
    }

    mycout << "delete founder " << ent.to_string() << " success ." << endl ;
    return true;
}

bool Buddha::_delete_temple_record(const string& id) {
    temple ent;
    if (!_is_temple_exist(id, ent)){
        mycout << "temple " << id << " is not exist ." << endl ;
        return false;
    }

    if( !get_temple_table().del(ent) ) {
        mycout << "delete temple " << ent.to_string() << " failure ." << endl ;
        return false;
    }

    mycout << "delete temple " << ent.to_string() << " success ." << endl ;
    return true;
}

bool Buddha::_delete_master_record(const string& id) {
    master ent;
    if (!_is_master_exist(id, ent)){
        mycout << "master " << id << " is not exist ." << endl ;
        return false;
    }

    if( !get_master_table().del(ent) ) {
        mycout << "delete master " << ent.to_string() << " failure ." << endl ;
        return false;
    }

    mycout << "delete master " << ent.to_string() << " success ." << endl ;
    return true;
}

bool Buddha::_delete_templemaster_record(const string& templeid,
                                         const string& masterid) {
    templemaster ent;
    if (!_is_templemaster_exist(templeid, masterid, ent)){
        mycout << "temple " << templeid << ", master " << masterid << " is not exist ." << endl ;
        return false;
    }

    if( !get_templemaster_table().del(ent) ) {
        mycout << "delete templemaster " << ent.to_string() << " failure ." << endl ;
        return false;
    }

    mycout << "delete templemaster " << ent.to_string() << " success ." << endl ;
    return true;
}

bool Buddha::_delete_kinddeedtype_record(const string& id) {
    kinddeedtype ent;
    if (!_is_kinddeedtype_exist(id, ent)){
        mycout << "kinddeedtype " << id << " is not exist ." << endl ;
        return false;
    }

    if( !get_kinddeedtype_table().del(ent) ) {
        mycout << "delete kinddeedtype " << ent.to_string() << " failure ." << endl ;
        return false;
    }

    mycout << "delete kinddeedtype " << ent.to_string() << " success ." << endl ;
    return true;
}


bool Buddha::_delete_kinddeed_record(const string& id) {
    kinddeed ent;
    if (!_is_kinddeed_exist(id, ent)){
        mycout << "kinddeed " << id << " is not exist ." << endl ;
        return false;
    }

    if( !get_kinddeed_table().del(ent) ) {
        mycout << "delete kinddeed " << ent.to_string() << " failure ." << endl ;
        return false;
    }

    if( !_delete_kinddeeddetail_records(id) ) {
        mycout << "delete kinddeeddetail " << id << " failure ." << endl ;
        return false;
    }

    if( !_delete_kinddeedspec_records(id) ) {
        mycout << "delete kinddeedspec " << id << " failure ." << endl ;
        return false;
    }

    mycout << "delete kinddeed " << ent.to_string() << " success ." << endl ;
    return true;
}

bool Buddha::_delete_kinddeeddetail_records(const string& id) {

    while(true) {
        kinddeeddetail ent;
        if (!get_kinddeeddetail_table().find({{"kdid", id}}, &ent))
            break;

        if( !get_kinddeeddetail_table().del(ent) ) {
            mycout << "delete kinddeeddetail " << ent.to_string() << " failure ." << endl ;
            return false;
        }
    }

    mycout << "delete kinddeeddetails success ." << endl ;
    return true;
}

bool Buddha::_delete_kinddeeddetail_record(const string& id, const string& sequence ) {
    kinddeeddetail ent;
    if (!get_kinddeeddetail_table().find({{"kdid", id},{"sequence",sequence}}, &ent)) {
        mycout << "not found kinddeeddetail " << id << "," << sequence << " failure ." << endl ;
        return false;
    }

    if( !get_kinddeeddetail_table().del(ent) ) {
        mycout << "delete kinddeeddetail " << ent.to_string() << " failure ." << endl ;
        return false;
    }

    mycout << "delete kinddeeddetail success ." << endl ;
    return true;
}

bool Buddha::_delete_kinddeedspec_records(const string& id) {
    while(true) {
        kinddeedspec ent;
        if (!get_kinddeedspec_table().find({{"kdid", id}}, &ent))
            break;

        if( !get_kinddeedspec_table().del(ent) ) {
            mycout << "delete kinddeedspec " << ent.to_string() << " failure ." << endl ;
            return false;
        }
    }

    mycout << "delete kinddeedspecs success ." << endl ;
    return true;
}

bool Buddha::_delete_kinddeedspec_record(const string& id, const string& sequence ) {
    kinddeedspec ent;
    if (!get_kinddeedspec_table().find({{"kdid", id},{"sequence",sequence}}, &ent)) {
        mycout << "not found kinddeedspec " << id << "," << sequence << " failure ." << endl ;
        return false;
    }

    if( !get_kinddeedspec_table().del(ent) ) {
        mycout << "delete kinddeedspec " << ent.to_string() << " failure ." << endl ;
        return false;
    }

    mycout << "delete kinddeedspec success ." << endl ;
    return true;
}

bool Buddha::_delete_commentlabel_record(const string& id) {
    commentlabel ent;
    if (!_is_commentlabel_exist(id, ent)){
        mycout << "commentlabel " << id << " is not exist ." << endl ;
        return false;
    }

    if( !get_commentlabel_table().del(ent) ) {
        mycout << "delete commentlabel " << ent.to_string() << " failure ." << endl ;
        return false;
    }

    mycout << "delete commentlabel " << ent.to_string() << " success ." << endl ;
    return true;
}

bool Buddha::_delete_beforecomment_record(const string& kdid, const string& owner) {
    beforecomment ent;
    if (!_is_beforecomment_exist(kdid, owner, ent)){
        mycout << "beforecomment  " << owner << "," << kdid << " is not exist ." << endl ;
        return false;
    }

    if( !get_beforecomment_table().del(ent) ) {
        mycout << "delete beforecomment " << ent.to_string() << " failure ." << endl ;
        return false;
    }

    mycout << "delete beforecomment " << ent.to_string() << " success ." << endl ;
    return true;
}


bool Buddha::_delete_order_record(const string& id) {
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

bool Buddha::_delete_aftercomment_record(const string& orderid, const string& owner) {
    aftercomment ent;
    if (!_is_aftercomment_exist(orderid,owner,ent)){
        mycout << "aftercomment " << orderid << " is not exist ." << endl ;
        return false;
    }

    if( !get_aftercomment_table().del(ent) ) {
        mycout << "delete aftercomment " << ent.to_string() << " failure ." << endl ;
        return false;
    }

    mycout << "delete aftercomment " << ent.to_string() << " success ." << endl ;
    return true;
}

bool Buddha::_add_kinddeeddetail(const string& kdid,
                                 const string& sequence,
                                 const string& hash) {

    if( kdid.empty()) {
        _log_error(__FUNCTION__, __LINE__,"kdid is empty .");
        return false;
    }

    if( sequence.empty()) {
        _log_error(__FUNCTION__, __LINE__,"sequence is empty .");
        return false;
    }

    if( hash.empty()) {
        _log_error(__FUNCTION__, __LINE__,"hash is empty .");
        return false;
    }

    kinddeeddetail ent;
    if(_is_kinddeeddetail_exist(kdid, sequence, ent))
        if(!_delete_kinddeeddetail_record(kdid, sequence)) 
            return false;

    ent.set_kdid(kdid);
    ent.set_sequence(stoll(sequence));
    ent.set_hash(hash);

    mycout << ent.to_string() << endl;

    if (!get_kinddeeddetail_table().put(ent)) {
        mycout << "kinddeeddetail table put " << ent.to_string() << " failure ." << endl;
        return false;
    }

    return true ;
}

bool Buddha::_add_kinddeedspec(const string& kdid,
                               const string& sequence,
                               const string& desc,
                               const string& price) {

    if( kdid.empty()) {
        _log_error(__FUNCTION__, __LINE__,"kdid is empty .");
        return false;
    }

    if( sequence.empty()) {
        _log_error(__FUNCTION__, __LINE__,"sequence is empty .");
        return false;
    }

    if( desc.empty()) {
        _log_error(__FUNCTION__, __LINE__,"desc is empty .");
        return false;
    }

    if( price.empty()) {
        _log_error(__FUNCTION__, __LINE__,"price is empty .");
        return false;
    }

    kinddeedspec ent;
    if(_is_kinddeedspec_exist(kdid, sequence, ent))
        if(!_delete_kinddeedspec_record(kdid, sequence)) 
            return false;

    ent.set_kdid(kdid);
    ent.set_sequence(stoll(sequence));
    ent.set_desc(desc);
    ent.set_price(stoll(price));

    mycout << ent.to_string() << endl;

    if (!get_kinddeedspec_table().put(ent)) {
        mycout << "kinddeedspec table put " << ent.to_string() << " failure ." << endl;
        return false;
    }

    return true ;
}


bool Buddha::_transfer(const string& toid,
                    const string& toamount){
    //将抵押退还
    xchain::Account account = xchain::Account(toid);
    if( !account.transfer(toamount)) 
        return false;

    return true ;
}


namespace 合约部署者{}

void Buddha::initialize() {
    ctx->put_object("deployer", ctx->initiator());
    ctx->emit_event("initialize", ctx->initiator());
    ctx->ok("deployer=" + ctx->initiator() + " success");
}

void Buddha::get_deployer() {
    string deployer;
    if (!ctx->get_object("deployer", &deployer)) {
        _log_error(__FUNCTION__, __LINE__,"unknown deployer .");
        return ;
    }

    if( !_is_deployer(ctx->initiator()) &&
        !_is_founder(ctx->initiator()) ) {
        _log_error(__FUNCTION__, __LINE__,ctx->initiator() + " is not deployer nor founder, have no authority to get deployer .");
        return ;
    }

    ctx->ok("deployer=" + deployer);
}

bool Buddha::is_deployer() {
    bool ret = _is_deployer(ctx->initiator());
    if (ret) {
        ctx->ok(ctx->initiator() + " is deployer .") ;
        return true;
    }
    
    ctx->ok(ctx->initiator() + " is not deployer .") ;
    return false;
}



namespace 申请成为基金会成员{}

void Buddha::apply_founder(){
    const string& desc = ctx->arg("desc");
    if( desc.empty()) {
        _log_error(__FUNCTION__, __LINE__,"desc is empty .");
        return ;
    }

    const string& address = ctx->arg("address");
    if( address.empty()) {
        _log_error(__FUNCTION__, __LINE__,"address is empty .");
        return ;
    }

    const string& timestamp = ctx->arg("timestamp");
    if( timestamp.empty()) {
        _log_error(__FUNCTION__, __LINE__,"timestamp is empty .");
        return ;
    }

    const string& guaranty = ctx->transfer_amount();
    if( guaranty.empty()) {
        _log_error(__FUNCTION__, __LINE__,"guaranty is empty .");
        return ;
    }

    if( is_founder()) {
        _log_error(__FUNCTION__, __LINE__,ctx->initiator() + " is already founder .");
        return ;
    }

    _delete_founder_record(ctx->initiator());

    founder ent;
    ent.set_id(ctx->initiator());
    ent.set_desc(desc);
    ent.set_address(address);
    ent.set_timestamp(timestamp);
    ent.set_guaranty(ent.guaranty() + stoll(guaranty));
    ent.set_approved(false);
    if (!get_founder_table().put(ent)) {
        _log_error(__FUNCTION__, __LINE__,"founder table put " + ent.to_string() + " failure .");
        return;
    }

    ctx->ok(ent.to_string() + " apply tobe founder over, please wait for approve .");
}

void Buddha::approve_founder() {
    const string& id = ctx->arg("id");
    if( id.empty()) {
        _log_error(__FUNCTION__, __LINE__,"founder id is empty .");
        return ;
    }

    if( !is_deployer()) {
        _log_error(__FUNCTION__, __LINE__,ctx->initiator() + " is not deployer, have no authority to approve founder .");
        return ;
    }

    founder ent;
    if( !_is_founder_exist(id,ent)) {
        _log_error(__FUNCTION__, __LINE__,"founder " + id + " is not exist .");
        return ;
    }

    if( _is_founder(id)) {
        _log_error(__FUNCTION__, __LINE__,ent.to_string() + " is already founder .");
        return ;
    }

    if( !_delete_founder_record(id) ) {
        _log_error(__FUNCTION__, __LINE__,"delete founder " + ent.to_string() + " failure .");
        return;
    }

    ent.set_approved(true);
    if (!get_founder_table().put(ent)) {
        _log_error(__FUNCTION__, __LINE__,"founder table put " + ent.to_string() + " failure .");
        return;
    }

    ctx->ok("audit " + ent.to_string() + " to be founder .");
}

void Buddha::recusal_founder() {
    const string& id = ctx->arg("id");
    if( id.empty()) {
        _log_error(__FUNCTION__, __LINE__,"founder id is empty .");
        return ;
    }

    if( !is_deployer()) {
        _log_error(__FUNCTION__, __LINE__,ctx->initiator() + " is not deployer, have no authority recusal founder .");
        return ;
    }

    founder ent;
    if( !_is_founder_exist(id,ent)) {
        _log_error(__FUNCTION__, __LINE__,"founder " + id + " is not exist .");
        return ;
    }

    if( !_delete_founder_record(id) ) {
        _log_error(__FUNCTION__, __LINE__,"delete founder " + ent.to_string() + " failure .");
        return;
    }

    //将抵押退还
    string guaranty = to_string(ent.guaranty());
    if( !_transfer(id, guaranty)) {
        _log_error(__FUNCTION__, __LINE__,"refund transfer " + guaranty + " to " + id + " failure .");
        return ;
    }

    ctx->ok("recusal founder "+ id + " success , guaranty " + guaranty + " has refund, please check balance .");
}

bool Buddha::is_founder() {
    if (!_is_founder(ctx->initiator())) {
        ctx->ok(ctx->initiator() + " is not founder .") ;
        return false;
    }
    
    ctx->ok(ctx->initiator() + " is founder .") ;
    return true;
}

void Buddha::list_founder() {
    if( !is_deployer() &&
        !is_founder()) {
        _log_error(__FUNCTION__, __LINE__,ctx->initiator() + " is not deployer nor founder, have no authority to list founder .");
        return ;
    }

    auto it = get_founder_table().scan({{"id",ctx->arg("id")}});
    int i = 0;
    string ret;
    while(it->next()) {
        founder ent;
        if (!it->get(&ent)) {
            _log_error(__FUNCTION__, __LINE__, "founder table get failure : " + it->error(true));
            return;
        }

        i++;
        ret += ent.to_string();
    }
    ctx->ok("size=" + to_string(i) + " " + ret);
}

namespace 申请成为寺院{}

void Buddha::apply_temple(){
    const string& unit = ctx->arg("unit");
    if( unit.empty()) {
        _log_error(__FUNCTION__, __LINE__,"unit is empty .");
        return ;
    }
    
    const string& creditcode = ctx->arg("creditcode");
    if( creditcode.empty()) {
        _log_error(__FUNCTION__, __LINE__,"creditcode is empty .");
        return ;
    }
    
    const string& address = ctx->arg("address");
    if( address.empty()) {
        _log_error(__FUNCTION__, __LINE__,"address is empty .");
        return ;
    }
    
    const string& proof = ctx->arg("proof");
    if( proof.empty()) {
        _log_error(__FUNCTION__, __LINE__,"proof is empty .");
        return ;
    }

    if( !is_user() &&
        !is_master()) {
        _log_error(__FUNCTION__, __LINE__,ctx->initiator() + " is not user or master, have no authority to apply tobe temple .");
        return ;
    }

    if( is_temple()) {
        _log_error(__FUNCTION__, __LINE__,ctx->initiator() + " is already temple .");
        return ;
    }

    _delete_temple_record(ctx->initiator());

    temple ent;
    ent.set_id(ctx->initiator());
    ent.set_unit(unit);
    ent.set_creditcode(creditcode);
    ent.set_address(address);
    ent.set_proof(proof);
    ent.set_approved(false);
    if (!get_temple_table().put(ent)) {
        _log_error(__FUNCTION__, __LINE__,"temple table put " + ent.to_string() + " failure .");
        return;
    }

    ctx->ok(ent.to_string() + " apply tobe temple over, please wait for approve .");
}

void Buddha::approve_temple() {
    const string& id = ctx->arg("id");
    if( id.empty()) {
        _log_error(__FUNCTION__, __LINE__,"temple id is empty .");
        return ;
    }

    if( !is_founder()) {
        _log_error(__FUNCTION__, __LINE__,ctx->initiator() + " is not founder, have no authority to approve temple .");
        return ;
    }

    temple ent;
    if( !_is_temple_exist(id,ent)) {
        _log_error(__FUNCTION__, __LINE__,"temple " + id + " is not exist .");
        return ;
    }

    if( _is_temple(id)) {
        _log_error(__FUNCTION__, __LINE__,ent.to_string() + " is already temple .");
        return ;
    }

    if( !_delete_temple_record(id) ) {
        _log_error(__FUNCTION__, __LINE__,"delete temple " + ent.to_string() + " failure .");
        return;
    }

    ent.set_approved(true);
    if (!get_temple_table().put(ent)) {
        _log_error(__FUNCTION__, __LINE__,"temple table put " + ent.to_string() + " failure .");
        return;
    }

    ctx->ok("approve temple " + ent.to_string() + " success .");
}

void Buddha::recusal_temple() {
    const string& id = ctx->arg("id");
    if( id.empty()) {
        _log_error(__FUNCTION__, __LINE__,"temple id is empty .");
        return ;
    }
    
    if( !is_founder()) {
        _log_error(__FUNCTION__, __LINE__,ctx->initiator() + " is not founder, have no authority to recusal temple .");
        return ;
    }

    temple ent;
    if( !_is_temple_exist(id,ent)) {
        _log_error(__FUNCTION__, __LINE__,"temple " + id + " is not exist .");
        return ;
    }

    if( !_delete_temple_record(id) ) {
        _log_error(__FUNCTION__, __LINE__,"delete temple " + ent.to_string() + " failure .");
        return;
    }

    ctx->ok("recusal temple " + ent.to_string() + " success .");
}

bool Buddha::is_temple() {
    if (!_is_temple(ctx->initiator())) {
        ctx->ok(ctx->initiator() + " is not temple .") ;
        return false;
    }
    
    ctx->ok(ctx->initiator() + " is temple .") ;
    return true;
}

void Buddha::list_temple() {
    if( !is_deployer() &&
        !is_founder()) {
        _log_error(__FUNCTION__, __LINE__,ctx->initiator() + " is not deployer nor founder, have no authority to list temple .");
        return ;
    }

    auto it = get_temple_table().scan({{"id",ctx->arg("id")}});
    int i = 0;
    string ret;
    while(it->next()) {
        temple ent;
        if (!it->get(&ent)) {
            _log_error(__FUNCTION__, __LINE__, "temple table get failure : " + it->error(true));
            return ;
        }

        i++;
        ret += ent.to_string();
    }

    ctx->ok("size=" + to_string(i) + " " + ret);
}

namespace 申请成为法师{}

void Buddha::apply_master(){
    const string& creditcode = ctx->arg("creditcode");
    if( creditcode.empty()) {
        _log_error(__FUNCTION__, __LINE__,"creditcode is empty .");
        return ;
    }

    const string& proof = ctx->arg("proof");
    if( proof.empty()) {
        _log_error(__FUNCTION__, __LINE__,"proof is empty .");
        return ;
    }

    if( !is_user()) {
        _log_error(__FUNCTION__, __LINE__,ctx->initiator() + " is not user, have no authority to apply tobe master .");
        return ;
    }

    if( is_master()) {
        _log_error(__FUNCTION__, __LINE__,ctx->initiator() + " is already master .");
        return ;
    }

    _delete_master_record(ctx->initiator());

    master ent;
    ent.set_id(ctx->initiator());
    ent.set_creditcode(creditcode);
    ent.set_proof(proof);
    ent.set_approved(false);
    if (!get_master_table().put(ent)) {
        _log_error(__FUNCTION__, __LINE__,"master table put " + ent.to_string() + " failure .");
        return;
    }

    ctx->ok(ent.to_string() + " apply tobe master over, please wait for approve .");
}

void Buddha::approve_master() {
    const string& id = ctx->arg("id");
    if( id.empty()) {
        _log_error(__FUNCTION__, __LINE__,"master id is empty .");
        return ;
    }

    if( !is_founder()) {
        _log_error(__FUNCTION__, __LINE__,ctx->initiator() + " is not founder, have no authority to approve master .");
        return ;
    }

    master ent;
    if( !_is_master_exist(id,ent)) {
        _log_error(__FUNCTION__, __LINE__,"master " + id + " is not exist .");
        return ;
    }

    if( _is_master(id)) {
        _log_error(__FUNCTION__, __LINE__,ent.to_string() + " is already master .");
        return ;
    }

    if( !_delete_master_record(id) ) {
        _log_error(__FUNCTION__, __LINE__,"delete master " + ent.to_string() + " failure .");
        return;
    }

    ent.set_approved(true);
    if (!get_master_table().put(ent)) {
        _log_error(__FUNCTION__, __LINE__,"master table put " + ent.to_string() + " failure .");
        return;
    }

    ctx->ok("approve master " + ent.to_string() + " success .");
}

void Buddha::recusal_master() {
    const string& id = ctx->arg("id");
    if( id.empty()) {
        _log_error(__FUNCTION__, __LINE__,"master id is empty .");
        return ;
    }
    
    if( !is_founder()) {
        _log_error(__FUNCTION__, __LINE__,ctx->initiator() + " is not founder, have no authority to recusal master .");
        return ;
    }

    master ent;
    if( !_is_master_exist(id,ent)) {
        _log_error(__FUNCTION__, __LINE__,"master " + id + " is not exist .");
        return ;
    }

    if( !_delete_master_record(id) ) {
        _log_error(__FUNCTION__, __LINE__,"delete master " + ent.to_string() + " failure .");
        return;
    }

    ctx->ok("recusal master " + ent.to_string() + " success .");
}

bool Buddha::is_master() {
    if (!_is_master(ctx->initiator())) {
        ctx->ok(ctx->initiator() + " is not master .") ;
        return false;
    }
    
    ctx->ok(ctx->initiator() + " is master .") ;
    return true;
}

void Buddha::list_master() {
    if( !is_deployer() &&
        !is_founder()) {
        _log_error(__FUNCTION__, __LINE__,ctx->initiator() + " is not deployer nor founder, have no authority to list master .");
        return ;
    }

    auto it = get_master_table().scan({{"id",ctx->arg("id")}});
    int i = 0;
    string ret;
    while(it->next()) {
        master ent;
        if (!it->get(&ent)) {
            _log_error(__FUNCTION__, __LINE__, "master table get failure : " + it->error(true));
            return;
        }

        i++;
        ret += ent.to_string();
    }
    ctx->ok("size=" + to_string(i) + " " + ret);
}

namespace 申请加入寺院{}

void Buddha::apply_join_temple(){
    // const string& id = ctx->arg("id");
    // if( id.empty()) {
    //     _log_error(__FUNCTION__, __LINE__,"id is empty .");
    //     return ;
    // }

    const string& templeid = ctx->arg("templeid");
    if( templeid.empty()) {
        _log_error(__FUNCTION__, __LINE__,"temple id is empty .");
        return ;
    }

    const string& masterid = ctx->initiator() ;

    if( !is_master()) {
        _log_error(__FUNCTION__, __LINE__, masterid + " is not master, have no authority to apply join temple .");
        return ;
    }

    if( !_is_temple(templeid)) {
        _log_error(__FUNCTION__, __LINE__, templeid + " is not a temple .");
        return ;
    }

    templemaster ent;
    if( _is_in_temple(templeid, masterid, ent )) {
        _log_error(__FUNCTION__, __LINE__,masterid + " is already join temple .");
        return;
    }
    
    _delete_templemaster_record(templeid, masterid);
    
    // ent.set_id(id);
    ent.set_templeid(templeid);
    ent.set_masterid(masterid);
    ent.set_approved(false);
    if (!get_templemaster_table().put(ent)) {
        _log_error(__FUNCTION__, __LINE__,"templemaster table put " + ent.to_string() + " failure .");
        return;
    }

    ctx->ok(ent.to_string() + " apply join templemaster over, please wait for approve .");
}

void Buddha::approve_join_temple() {
    const string& templeid = ctx->arg("templeid");
    if( templeid.empty()) {
        _log_error(__FUNCTION__, __LINE__,"temple id is empty .");
        return ;
    }

    const string& masterid = ctx->arg("masterid");
    if( masterid.empty()) {
        _log_error(__FUNCTION__, __LINE__,"master id is empty .");
        return ;
    }

    if( !is_founder()) {
        _log_error(__FUNCTION__, __LINE__,ctx->initiator() + " is not founder, have no authority to approve master .");
        return ;
    }

    if( !_is_master(masterid)) {
        _log_error(__FUNCTION__, __LINE__, masterid + " is not a master .");
        return ;
    }

    if( !_is_temple(templeid)) {
        _log_error(__FUNCTION__, __LINE__, templeid + " is not a temple .");
        return ;
    }

    templemaster ent;
    if( _is_in_temple(templeid, masterid,ent)) {
        _log_error(__FUNCTION__, __LINE__,ent.to_string() + " is already join temple .");
        return ;
    }

    if( !_delete_templemaster_record(templeid, masterid) ) {
        _log_error(__FUNCTION__, __LINE__,"delete templemaster " + ent.to_string() + " failure .");
        return;
    }

    ent.set_approved(true);
    if (!get_templemaster_table().put(ent)) {
        _log_error(__FUNCTION__, __LINE__,"templemaster table put " + ent.to_string() + " failure .");
        return;
    }

    ctx->ok("approve templemaster " + ent.to_string() + " success .");
}

void Buddha::recusal_join_temple() {
    const string& templeid = ctx->arg("templeid");
    if( templeid.empty()) {
        _log_error(__FUNCTION__, __LINE__,"temple id is empty .");
        return ;
    }

    const string& masterid = ctx->arg("masterid");
    if( masterid.empty()) {
        _log_error(__FUNCTION__, __LINE__,"master id is empty .");
        return ;
    }
    
    if( !is_founder()) {
        _log_error(__FUNCTION__, __LINE__,ctx->initiator() + " is not founder, have no authority to recusal master .");
        return ;
    }

    templemaster ent;
    if( !_is_templemaster_exist(templeid, masterid,ent)) {
        _log_error(__FUNCTION__, __LINE__,"temple " + templeid + ", master " + masterid + " is not exist .");
        return ;
    }

    if( !_delete_templemaster_record(templeid, masterid) ) {
        _log_error(__FUNCTION__, __LINE__,"delete templemaster " + ent.to_string() + " failure .");
        return;
    }

    ctx->ok("recusal templemaster " + ent.to_string() + " success .");
}

bool Buddha::is_in_temple() {
    const string& templeid = ctx->arg("templeid");
    if( templeid.empty()) {
        _log_error(__FUNCTION__, __LINE__,"temple id is empty .");
        return false;
    }

    const string& masterid = ctx->initiator();

    if( !_is_master(masterid)) {
        _log_error(__FUNCTION__, __LINE__, masterid + " is not a master, have no authority to query in some temple .");
        return false;
    }

    if( !_is_temple(templeid)) {
        _log_error(__FUNCTION__, __LINE__,templeid + " is not a temple .");
        return false;
    }

    templemaster ent;
    if (!_is_in_temple(templeid, masterid, ent)) {
        ctx->ok(masterid + " is not join temple .") ;
        return false;
    }

    ctx->ok(masterid + " is join temple .") ;
    return true;
}

void Buddha::list_temple_master() {
    const string& templeid = ctx->arg("templeid");

    if( is_deployer() ||
        is_founder()) {
        auto it = get_templemaster_table().scan({{"templeid",templeid}});
        int i = 0;
        string ret;
        while(it->next()) {
            templemaster ent;
            if (!it->get(&ent)) {
                _log_error(__FUNCTION__, __LINE__, "templemaster table get failure : " + it->error(true));
                return;
            }

            i++;
            ret += ent.to_string();
        }
        ctx->ok("size=" + to_string(i) + " " + ret);

        return ;
    }

    if( is_temple() ) {

        auto it = get_templemaster_table().scan({{"templeid",ctx->initiator()}});
        int i = 0;
        string ret;
        while(it->next()) {
            templemaster ent;
            if (!it->get(&ent)) {
                _log_error(__FUNCTION__, __LINE__, "templemaster table get failure : " + it->error(true));
                return;
            }

            i++;
            ret += ent.to_string();
        }
        ctx->ok("size=" + to_string(i) + " " + ret);
        return ;
    }

    _log_error(__FUNCTION__, __LINE__,ctx->initiator() + " have no authority to list temple master .");
    return ;
}

namespace 添加删除修改善举类型{}

void Buddha::add_kinddeedtype() {
    const string& id = ctx->arg("id");
    if( id.empty()) {
        _log_error(__FUNCTION__, __LINE__,"kinddeedtype id is empty .");
        return ;
    }

    const string& desc = ctx->arg("desc");
    if( desc.empty()) {
        _log_error(__FUNCTION__, __LINE__,"kinddeedtype desc is empty .");
        return ;
    }

    if( !is_founder() ) {
        _log_error(__FUNCTION__, __LINE__,ctx->initiator() + " is not founder, have no authority to add kinddeedtype .");
        return ;
    }

    kinddeedtype ent;
    if( _is_kinddeedtype_exist(id,ent)) {
        _log_error(__FUNCTION__, __LINE__,"kinddeedtype " + id + " is exist .");
        return ;
    }

    ent.set_id(stoll(id));
    ent.set_desc(desc);
    if (!get_kinddeedtype_table().put(ent)) {
        _log_error(__FUNCTION__, __LINE__,"kinddeedtype table put " + ent.to_string() + " failure .");
        return;
    }

    ctx->ok("add kinddeedtype " + ent.to_string() + " success .");
}

void Buddha::delete_kinddeedtype() {
    const string& id = ctx->arg("id");
    if( id.empty()) {
        _log_error(__FUNCTION__, __LINE__,"kinddeedtype id is empty .");
        return ;
    }

    if( !is_founder() ) {
        _log_error(__FUNCTION__, __LINE__,ctx->initiator() + " is not founder, have no authority to delete kinddeedtype .");
        return ;
    }

    kinddeedtype ent;
    if( !_is_kinddeedtype_exist(id,ent)) {
        _log_error(__FUNCTION__, __LINE__,"kindeed type " + id + " is not exist .");
        return ;
    }

    if( !_delete_kinddeedtype_record(id) ) {
        _log_error(__FUNCTION__, __LINE__,"delete kinddeedtype " + ent.to_string() + " failure .");
        return;
    }

    ctx->ok("delete kinddeedtype " + ent.to_string() + " success .");
}

void Buddha::update_kinddeedtype() {
    const string& id = ctx->arg("id");
    if( id.empty()) {
        _log_error(__FUNCTION__, __LINE__,"kinddeedtype id is empty .");
        return ;
    }

    const string& desc = ctx->arg("desc");
    if( desc.empty()) {
        _log_error(__FUNCTION__, __LINE__,"kinddeedtype desc is empty .");
        return ;
    }

    if( !is_founder() ) {
        _log_error(__FUNCTION__, __LINE__,ctx->initiator() + " is not founder, have no authority to update kinddeedtype .");
        return ;
    }

    kinddeedtype ent;
    if( !_is_kinddeedtype_exist(id,ent)) {
        _log_error(__FUNCTION__, __LINE__,"kindeedtype " + id + " is not exist .");
        return ;
    }

    if( !_delete_kinddeedtype_record(id) ) {
        _log_error(__FUNCTION__, __LINE__,"delete kinddeedtype " + ent.to_string() + " failure .");
        return;
    }

    ent.set_id(stoll(id));
    ent.set_desc(desc);
    if (!get_kinddeedtype_table().put(ent)) {
        _log_error(__FUNCTION__, __LINE__,"kinddeedtype table put " + ent.to_string() + " failure .");
        return;
    }

    ctx->ok("update kinddeedtype " + ent.to_string() + " success .");
}

void Buddha::find_kinddeedtype() {
    const string& id = ctx->arg("id");
    if( id.empty()) {
        _log_error(__FUNCTION__, __LINE__,"kinddeedtype id is empty .");
        return ;
    }

    kinddeedtype ent;
    if (!_is_kinddeedtype_exist(id, ent))  {
        ctx->ok("kinddeedtype " + id + " is not exist .");
        return ;
    }

    ctx->ok(ent.to_string());
}

void Buddha::list_kinddeedtype() {
    auto it = get_kinddeedtype_table().scan({{"id",""}});
    int i = 0;
    string ret;
    while(it->next()) {
        kinddeedtype ent;
        if (!it->get(&ent)) {
            _log_error(__FUNCTION__, __LINE__, "kinddeedtype table get failure : " + it->error(true));
            return;
        }

        i++;
        ret += ent.to_string();
    }
    ctx->ok("size=" + to_string(i) + " " + ret);
}


namespace 添加删除修改善举{}

void Buddha::add_kinddeeddetail() {
    const string& id = ctx->arg("id");
    const string& sequence = ctx->arg("sequence");
    const string& hash = ctx->arg("hash");
    if (!_add_kinddeeddetail(id,sequence,hash)) {
        _log_error(__FUNCTION__, __LINE__,"_add_kinddeeddetail " + id + " failure .");
        return;
    }

    ctx->ok("ok");
}

void Buddha::add_kinddeedspec() {
    const string& id = ctx->arg("id");    
    const string& sequence = ctx->arg("sequence");
    const string& desc = ctx->arg("desc");
    const string& price = ctx->arg("price");
    if (!_add_kinddeedspec(id,sequence,desc,price)) {
        _log_error(__FUNCTION__, __LINE__,"_add_kinddeedspec " + id + " failure .");
        return;
    }

    ctx->ok("ok");
}

void Buddha::add_kinddeed() {
    const string& id = ctx->arg("id");
    const string& name = ctx->arg("name");
    const string& owner = ctx->initiator();
    const string& type = ctx->arg("type");
    const string& lasttime = ctx->arg("lasttime");
    const string& detail = ctx->arg("detail");
    const string& spec = ctx->arg("spec");

    if( id.empty()) {
        _log_error(__FUNCTION__, __LINE__,"kinddeed id is empty .");
        return ;
    }

    if( name.empty()) {
        _log_error(__FUNCTION__, __LINE__,"kinddeed name is empty .");
        return ;
    }

    if( type.empty()) {
        _log_error(__FUNCTION__, __LINE__,"kinddeed type is empty .");
        return ;
    }

    if( lasttime.empty()) {
        _log_error(__FUNCTION__, __LINE__,"kinddeed lasttime is empty .");
        return ;
    }
    
    auto detail_array = xchain::json::parse(detail);
    // mycout << detail_array.dump() << endl ;
    if (!detail_array.is_array()) {
        _log_error(__FUNCTION__, __LINE__,"field 'detail' need to be array .");
        return;
    }
    
    if ( detail_array.empty() || detail_array.size() == 0) {
        _log_error(__FUNCTION__, __LINE__,"filed 'detail' empty .");
        return;
    }

    auto spec_array = xchain::json::parse(spec);
    // mycout << spec_array.dump() << endl ;
    if (!spec_array.is_array()) {
        _log_error(__FUNCTION__, __LINE__,"field 'spec' need to be array .");
        return;
    }
    
    if ( spec_array.empty() || spec_array.size() == 0) {
        _log_error(__FUNCTION__, __LINE__,"filed 'spec' empty .");
        return;
    }

    if( !is_founder() &&
        !is_temple() &&
        !is_master() ) {
        _log_error(__FUNCTION__, __LINE__,ctx->initiator() + " is not founder,temple and master, have no authority to add kinddeed .");
        return ;
    }

    kinddeed ent;
    if (_is_kinddeed_exist(id, ent))  {
        _log_error(__FUNCTION__, __LINE__,"kinddeed " + ent.to_string() + " is exist .");
        return ;
    }

    kinddeedtype type_ent;
    if (!_is_kinddeedtype_exist(type, type_ent))  {
        _log_error(__FUNCTION__, __LINE__,"kinddeedtype " + type + " is not exist .");
        return ;
    }

    // vector<kinddeeddetail> v_kinddeeddetail_ent;
    // if (_is_kinddeeddetail_exist_by_kdid(id, v_kinddeeddetail_ent))  {
    //     _log_error(__FUNCTION__, __LINE__,"kinddeeddetail " + ent.to_string() + " is exist .");
    //     return ;
    // }

    // vector<kinddeedspec> v_kinddeedspec_ent;
    // if (_is_kinddeedspec_exist_by_kdid(id, v_kinddeedspec_ent))  {
    //     _log_error(__FUNCTION__, __LINE__,"kinddeedspec " + ent.to_string() + " is exist .");
    //     return ;
    // }


    if( !_delete_kinddeeddetail_records(id) ) {
        _log_error(__FUNCTION__, __LINE__, "delete kinddeeddetail " + id + " failure .");
        return;
    }

    if( !_delete_kinddeedspec_records(id) ) {
        _log_error(__FUNCTION__, __LINE__, "delete kinddeedspec " + id + " failure .") ;
        return;
    }

    for(int i = 0 ; i < detail_array.size() ; i++) {
        string sequence = detail_array.at(i)["sequence"].template get<string>();
        string hash = detail_array.at(i)["hash"].template get<string>();        
        if (!_add_kinddeeddetail(id,sequence,hash)) {
            _log_error(__FUNCTION__, __LINE__,"_add_kinddeeddetail " + id + " failure .");
            return;
        }
    }

    // mycout << spec_array.dump() << endl ;
    for(int i = 0 ; i < spec_array.size() ; i++) {
        string sequence = spec_array.at(i)["sequence"].template get<string>();
        string desc = spec_array.at(i)["desc"].template get<string>();
        string price = spec_array.at(i)["price"].template get<string>();

        if (!_add_kinddeedspec(id,sequence,desc,price)) {
            _log_error(__FUNCTION__, __LINE__,"_add_kinddeedspec " + id + " failure .");
            return;
        }
    }

    ent.set_id(id);
    ent.set_name(name);
    ent.set_owner(ctx->initiator());
    ent.set_type(stoll(type));
    ent.set_lasttime(lasttime);
    ent.set_applied(false);
    ent.set_online(false);

    if (!get_kinddeed_table().put(ent)) {
        _log_error(__FUNCTION__, __LINE__,"kinddeed table put " + ent.to_string() + " failure .");
        return;
    }

    ctx->ok("add kinddeed " + ent.to_string() + " success .");
}

void Buddha::delete_kinddeed() {

    const string& id = ctx->arg("id");
    if( id.empty()) {
        _log_error(__FUNCTION__, __LINE__,"kinddeed id is empty .");
        return ;
    }

    kinddeed ent;
    if (!_is_kinddeed_exist(id, ent))  {
        _log_error(__FUNCTION__, __LINE__,"kinddeed " + id + " is not exist .");
        return ;
    }

    if( !is_founder() &&
        !is_temple() &&
        !is_master() ) {
        _log_error(__FUNCTION__, __LINE__,ctx->initiator() + " is not founder and master, have no authority to delete kinddeed .");
        return ;
    }

    if( ent.owner() != ctx->initiator() ) {
        _log_error(__FUNCTION__, __LINE__,"kinddeed " + ent.to_string() + " is not belong to you .");
        return ;
    }

    if( !_delete_kinddeed_record(id) ) {
        _log_error(__FUNCTION__, __LINE__,"delete kinddeed " + ent.to_string() + " failure .");
        return;
    }

    ctx->ok("delete kinddeed " + ent.to_string() + " success .");
}

void Buddha::update_kinddeed() {
    const string& id = ctx->arg("id");
    const string& name = ctx->arg("name");
    const string& owner = ctx->initiator();
    const string& type = ctx->arg("type");
    const string& lasttime = ctx->arg("lasttime");
    const string& detail = ctx->arg("detail");
    const string& spec = ctx->arg("spec");

    if( id.empty()) {
        _log_error(__FUNCTION__, __LINE__,"kinddeed id is empty .");
        return ;
    }

    if( name.empty()) {
        _log_error(__FUNCTION__, __LINE__,"kinddeed name is empty .");
        return ;
    }

    if( type.empty()) {
        _log_error(__FUNCTION__, __LINE__,"kinddeed type is empty .");
        return ;
    }

    if( lasttime.empty()) {
        _log_error(__FUNCTION__, __LINE__,"kinddeed lasttime is empty .");
        return ;
    }

    auto detail_array = xchain::json::parse(detail);
    // mycout << detail_array.dump() << endl ;
    if (!detail_array.is_array()) {
        _log_error(__FUNCTION__, __LINE__,"field 'detail' need to be array .");
        return;
    }
    
    if ( detail_array.empty() || detail_array.size() == 0) {
        _log_error(__FUNCTION__, __LINE__,"filed 'detail' empty .");
        return;
    }

    auto spec_array = xchain::json::parse(spec);
    // mycout << spec_array.dump() << endl ;
    if (!spec_array.is_array()) {
        _log_error(__FUNCTION__, __LINE__,"field 'spec' need to be array .");
        return;
    }
    
    if ( spec_array.empty() || spec_array.size() == 0) {
        _log_error(__FUNCTION__, __LINE__,"filed 'spec' empty .");
        return;
    }

    if( !is_founder() &&
        !is_temple() &&
        !is_master() ) {
        _log_error(__FUNCTION__, __LINE__,ctx->initiator() + " is not founder and master, have no authority to update kinddeed .");
        return ;
    }

    kinddeed ent;
    if (_is_kinddeed_exist(id, ent))  {
        _log_error(__FUNCTION__, __LINE__,"kinddeed " + ent.to_string() + " is exist .");
        return ;
    }

    kinddeedtype type_ent;
    if (!_is_kinddeedtype_exist(type, type_ent))  {
        _log_error(__FUNCTION__, __LINE__,"kinddeedtype " + type + " is not exist .");
        return ;
    }

    vector<kinddeeddetail> v_kinddeeddetail_ent;
    if (_is_kinddeeddetail_exist_by_kdid(id, v_kinddeeddetail_ent))  {
        _log_error(__FUNCTION__, __LINE__,"kinddeeddetail " + ent.to_string() + " is exist .");
        return ;
    }

    vector<kinddeedspec> v_kinddeedspec_ent;
    if (_is_kinddeedspec_exist_by_kdid(id, v_kinddeedspec_ent))  {
        _log_error(__FUNCTION__, __LINE__,"kinddeedspec " + ent.to_string() + " is exist .");
        return ;
    }

    for(int i = 0 ; i < detail_array.size() ; i++) {
        int64_t sequence = stoll(detail_array.at(i)["sequence"].template get<string>());
        string hash = detail_array.at(i)["hash"].template get<string>();

        kinddeeddetail ent;
        ent.set_kdid(id);
        ent.set_sequence(sequence);
        ent.set_hash(hash);

        if (!get_kinddeeddetail_table().put(ent)) {
            _log_error(__FUNCTION__, __LINE__,"kinddeeddetail table put " + ent.to_string() + " failure .");
            return;
        }
    }
    
    for(int i = 0 ; i < spec_array.size() ; i++) {
        int64_t sequence = stoll(spec_array.at(i)["sequence"].template get<string>());
        string desc = spec_array.at(i)["desc"].template get<string>();
        int64_t price = stoll(spec_array.at(i)["price"].template get<string>());

        kinddeedspec ent;
        ent.set_kdid(id);
        ent.set_sequence(sequence);
        ent.set_desc(desc);
        ent.set_price(price);

        if (!get_kinddeedspec_table().put(ent)) {
            _log_error(__FUNCTION__, __LINE__,"kinddeedspec table put " + ent.to_string() + " failure .");
            return;
        }
    }

    ent.set_id(id);
    ent.set_name(name);
    ent.set_owner(ctx->initiator());
    ent.set_type(stoll(type));
    ent.set_lasttime(lasttime);
    ent.set_applied(false);
    ent.set_online(false);

    if (!get_kinddeed_table().put(ent)) {
        _log_error(__FUNCTION__, __LINE__,"kinddeed table put " + ent.to_string() + " failure .");
        return;
    }

    ctx->ok("update kinddeed " + ent.to_string() + " success .");
}

void Buddha::find_kinddeed() {       

    const string& id = ctx->arg("id");
    if( id.empty()) {
        _log_error(__FUNCTION__, __LINE__,"kinddeed id is empty .");
        return ;
    }

    kinddeed kinddeed_ent;
    if (!_is_kinddeed_exist(id, kinddeed_ent))  {
        ctx->ok("kinddeed " + id + " is not exist .");
        return ;
    }

    vector<kinddeeddetail> v_kinddeeddetail_ent;
    _is_kinddeeddetail_exist_by_kdid(id, v_kinddeeddetail_ent);
    string detail_string ;
    for(int i = 0 ; i < v_kinddeeddetail_ent.size() ; i++ ) {
        detail_string += v_kinddeeddetail_ent[i].to_string();
    }

    vector<kinddeedspec> v_kinddeedspec_ent;
    _is_kinddeedspec_exist_by_kdid(id, v_kinddeedspec_ent);
    string spec_string ;
    for(int i = 0 ; i < v_kinddeedspec_ent.size() ; i++ ) {
        spec_string += v_kinddeedspec_ent[i].to_string();
    }

    ctx->ok(kinddeed_ent.to_string() + detail_string + spec_string);
}

void Buddha::list_kinddeed() {        
    if( is_deployer() ||
        is_founder() ) {    //善举过多时，此时不安全，尽可能少调用
        auto it = get_kinddeed_table().scan({{"id",ctx->arg("id")}});
        int i = 0;
        string ret;
        while(it->next()) {
            kinddeed ent;
            if (!it->get(&ent)) {
                _log_error(__FUNCTION__, __LINE__, "kinddeed table get failure : " + it->error(true));
                return;
            }
            i++;
            ret += ent.to_string();
        }
        ctx->ok("size=" + to_string(i) + " " + ret);
        return ;
    }

    if( is_temple() ||
        is_master() ) {    //善举过多时，此时不安全，不过一般不会太多。
        auto it = get_kinddeed_table().scan({{"owner",ctx->initiator()}});
        int i = 0;
        string ret;
        while(it->next()) {
            kinddeed ent;
            if (!it->get(&ent)) {
                _log_error(__FUNCTION__, __LINE__, "kinddeed table get failure : " + it->error(true));
                return;
            }

            i++;
            ret += ent.to_string();
        }
        ctx->ok("size=" + to_string(i) + " " + ret);
        return ;
    }

    _log_error(__FUNCTION__, __LINE__,ctx->initiator() + " have no authority to list kinddeed .");
}

void Buddha::list_kinddeeddetail() {        
    if( !is_deployer() &&
        !is_founder() &&
        !is_temple() &&
        !is_master() ) {
        _log_error(__FUNCTION__, __LINE__,ctx->initiator() + " have no authority to list kinddeeddetail .");
        return ;
    }

    auto it = get_kinddeeddetail_table().scan({{"kdid",ctx->arg("kdid")}});
    int i = 0;
    string ret;
    while(it->next()) {
        kinddeeddetail ent;
        if (!it->get(&ent)) {
            _log_error(__FUNCTION__, __LINE__, "kinddeeddetail table get failure : " + it->error(true));
            return;
        }
        i++;
        ret += ent.to_string();
    }
    ctx->ok("size=" + to_string(i) + " " + ret);
}

void Buddha::list_kinddeedspec() {        
    if( !is_deployer() &&
        !is_founder() &&
        !is_temple() &&
        !is_master() ) {
        _log_error(__FUNCTION__, __LINE__,ctx->initiator() + " have no authority to list kinddeedspec .");
        return ;
    }

    auto it = get_kinddeedspec_table().scan({{"kdid",ctx->arg("kdid")}});
    int i = 0;
    string ret;
    while(it->next()) {
        kinddeedspec ent;
        if (!it->get(&ent)) {
            _log_error(__FUNCTION__, __LINE__, "kinddeedspec table get failure : " + it->error(true));
            return;
        }
        i++;
        ret += ent.to_string();
    }
    ctx->ok("size=" + to_string(i) + " " + ret);
}



namespace 申请善举上架下架{}

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

    if( !_delete_kinddeed_record(id) ) {
        _log_error(__FUNCTION__, __LINE__,"delete kinddeed " + ent.to_string() + " failure .");
        return;
    }

    ent.set_applied(true);
    if (!get_kinddeed_table().put(ent)) {
        _log_error(__FUNCTION__, __LINE__,"kinddeed table put " + ent.to_string() + " failure .");
        return;
    }

    ctx->ok("kinddeed " + ent.to_string() + " apply online over, please wait for approve .");
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

    if( !_delete_kinddeed_record(id) ) {
        _log_error(__FUNCTION__, __LINE__,"delete kinddeed " + ent.to_string() + " failure .");
        return;
    }

    ent.set_applied(true);
    if (!get_kinddeed_table().put(ent)) {
        _log_error(__FUNCTION__, __LINE__,"kinddeed table put " + ent.to_string() + " failure .");
        return;
    }

    ctx->ok("kinddeed " + ent.to_string() + " apply offline over, please wait for approve .");
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

    ctx->ok("approve kinddeed " + ent.to_string() + " online success .");
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

    ctx->ok("approve kinddeed " + ent.to_string() + " offline success .");
}


namespace 添加删除修改点评标签 {}
void Buddha::add_commentlabel() {
    const string& id = ctx->arg("id");
    if( id.empty()) {
        _log_error(__FUNCTION__, __LINE__,"commentlabel id is empty .");
        return ;
    }

    const string& desc = ctx->arg("desc");
    if( desc.empty()) {
        _log_error(__FUNCTION__, __LINE__,"commentlabel desc is empty .");
        return ;
    }

    if( !is_founder() ) {
        _log_error(__FUNCTION__, __LINE__,ctx->initiator() + " is not founder, have no authority to add commentlabel .");
        return ;
    }

    commentlabel ent;
    if( _is_commentlabel_exist(id,ent)) {
        _log_error(__FUNCTION__, __LINE__,"commentlabel " + id + " is exist .");
        return ;
    }

    ent.set_id(stoll(id));
    ent.set_desc(desc);
    if (!get_commentlabel_table().put(ent)) {
        _log_error(__FUNCTION__, __LINE__,"commentlabel table put " + ent.to_string() + " failure .");
        return;
    }

    ctx->ok("add commentlabel " + ent.to_string() + " success .");
}

void Buddha::delete_commentlabel() {
    const string& id = ctx->arg("id");
    if( id.empty()) {
        _log_error(__FUNCTION__, __LINE__,"commentlabel id is empty .");
        return ;
    }

    if( !is_founder() ) {
        _log_error(__FUNCTION__, __LINE__,ctx->initiator() + " is not founder, have no authority to delete commentlabel .");
        return ;
    }

    commentlabel ent;
    if( !_is_commentlabel_exist(id,ent)) {
        _log_error(__FUNCTION__, __LINE__,"kindeed type " + id + " is not exist .");
        return ;
    }

    if( !_delete_commentlabel_record(id) ) {
        _log_error(__FUNCTION__, __LINE__,"delete commentlabel " + ent.to_string() + " failure .");
        return;
    }

    ctx->ok("delete commentlabel " + ent.to_string() + " success .");
}

void Buddha::update_commentlabel() {
    const string& id = ctx->arg("id");
    if( id.empty()) {
        _log_error(__FUNCTION__, __LINE__,"commentlabel id is empty .");
        return ;
    }

    const string& desc = ctx->arg("desc");
    if( desc.empty()) {
        _log_error(__FUNCTION__, __LINE__,"commentlabel desc is empty .");
        return ;
    }

    if( !is_founder() ) {
        _log_error(__FUNCTION__, __LINE__,ctx->initiator() + " is not founder, have no authority to update commentlabel .");
        return ;
    }

    commentlabel ent;
    if( !_is_commentlabel_exist(id,ent)) {
        _log_error(__FUNCTION__, __LINE__,"commentlabel " + id + " is not exist .");
        return ;
    }

    if( !_delete_commentlabel_record(id) ) {
        _log_error(__FUNCTION__, __LINE__,"delete commentlabel " + ent.to_string() + " failure .");
        return;
    }

    ent.set_id(stoll(id));
    ent.set_desc(desc);
    if (!get_commentlabel_table().put(ent)) {
        _log_error(__FUNCTION__, __LINE__,"commentlabel table put " + ent.to_string() + " failure .");
        return;
    }

    ctx->ok("update commentlabel " + ent.to_string() + " success .");
}

void Buddha::find_commentlabel() {
    const string& id = ctx->arg("id");
    if( id.empty()) {
        _log_error(__FUNCTION__, __LINE__,"commentlabel id is empty .");
        return ;
    }

    commentlabel ent;
    if (!_is_commentlabel_exist(id, ent))  {
        _log_error(__FUNCTION__, __LINE__,"commentlabel " + id + " is not exist .");
        return ;
    }

    ctx->ok(ent.to_string());
}

void Buddha::list_commentlabel() {
    auto it = get_commentlabel_table().scan({{"id",""}});
    int i = 0;
    string ret;
    while(it->next()) {
        commentlabel ent;
        if (!it->get(&ent)) {
            _log_error(__FUNCTION__, __LINE__, "commentlabel table get failure : " + it->error(true));
            return;
        }

        i++;
        ret += ent.to_string();
    }
    ctx->ok("size=" + to_string(i) + " " + ret);
}


namespace 添加删除修改祈求善举前点评 {}
void Buddha::add_beforecomment() {
    const string& kdid = ctx->arg("kdid");
    if( kdid.empty()) {
        _log_error(__FUNCTION__, __LINE__,"beforecomment kdid is empty .");
        return ;
    }

    const string& satisfaction = ctx->arg("satisfaction");
    if( satisfaction.empty()) {
        _log_error(__FUNCTION__, __LINE__,"beforecomment satisfaction is empty .");
        return ;
    }

    const string& labels = ctx->arg("labels");
    xchain::json label_array = xchain::json::parse(labels);
    // mycout << label_array.dump() << endl ;
    if (!label_array.is_array()) {
        _log_error(__FUNCTION__, __LINE__,"field 'labels' need to be array .");
        return;
    }
    
    if ( label_array.empty() || label_array.size() == 0) {
        _log_error(__FUNCTION__, __LINE__,"filed 'labels' empty .");
        return;
    }

    if( !_is_all_types_exist_in_commentlabel(label_array)) {
        _log_error(__FUNCTION__, __LINE__,"beforecomment type failure .");
        return ;
    }

    const string& comment = ctx->arg("comment");
    if( comment.empty()) {
        _log_error(__FUNCTION__, __LINE__,"beforecomment comment is empty .");
        return ;
    }

    const string& timestamp = ctx->arg("timestamp");
    if( timestamp.empty()) {
        _log_error(__FUNCTION__, __LINE__,"beforecomment timestamp is empty .");
        return ;
    }

    const string& owner = ctx->initiator() ;

    beforecomment ent;
    if( _is_beforecomment_exist(kdid,owner,ent)) {
        _log_error(__FUNCTION__, __LINE__,"beforecomment " + kdid + " is exist .");
        return ;
    }

    ent.set_owner(owner);
    ent.set_kdid(kdid);
    ent.set_satisfaction(stoll(satisfaction));
    ent.set_labels(labels);    
    ent.set_comment(comment);
    ent.set_timestamp(timestamp);
    if (!get_beforecomment_table().put(ent)) {
        _log_error(__FUNCTION__, __LINE__,"beforecomment table put " + ent.to_string() + " failure .");
        return;
    }

    ctx->ok("add beforecomment " + ent.to_string() + " success .");
}

void Buddha::delete_beforecomment() {
    const string& kdid = ctx->arg("kdid");
    if( kdid.empty()) {
        _log_error(__FUNCTION__, __LINE__,"beforecomment kdid is empty .");
        return ;
    }

    const string& owner = ctx->initiator();

    beforecomment ent;
    if( !_is_beforecomment_exist(kdid,owner,ent)) {
        _log_error(__FUNCTION__, __LINE__,"beforecomment " + kdid + " is not exist .");
        return ;
    }

    if( !is_founder() &&
        ent.owner() != owner) {
        _log_error(__FUNCTION__, __LINE__,ctx->initiator() + " is not founder nor owner, have no authority to delete the comment .");
        return ;
    }

    if( !_delete_beforecomment_record(kdid,owner) ) {
        _log_error(__FUNCTION__, __LINE__,"delete beforecomment " + ent.to_string() + " failure .");
        return;
    }

    ctx->ok("delete beforecomment " + ent.to_string() + " success .");
}

void Buddha::update_beforecomment() {
    const string& kdid = ctx->arg("kdid");
    if( kdid.empty()) {
        _log_error(__FUNCTION__, __LINE__,"beforecomment kdid is empty .");
        return ;
    }

    const string& satisfaction = ctx->arg("satisfaction");
    if( satisfaction.empty()) {
        _log_error(__FUNCTION__, __LINE__,"beforecomment satisfaction is empty .");
        return ;
    }

    const string& labels = ctx->arg("labels");
    auto label_array = xchain::json::parse(labels);
    // mycout << label_array.dump() << endl ;
    if (!label_array.is_array()) {
        _log_error(__FUNCTION__, __LINE__,"field 'labels' need to be array .");
        return;
    }
    
    if ( label_array.empty() || label_array.size() == 0) {
        _log_error(__FUNCTION__, __LINE__,"filed 'labels' empty .");
        return;
    }

    if( !_is_all_types_exist_in_commentlabel(label_array)) {
        _log_error(__FUNCTION__, __LINE__,"beforecomment type failure .");
        return ;
    }

    const string& comment = ctx->arg("comment");
    if( comment.empty()) {
        _log_error(__FUNCTION__, __LINE__,"beforecomment comment is empty .");
        return ;
    }

    const string& timestamp = ctx->arg("timestamp");
    if( timestamp.empty()) {
        _log_error(__FUNCTION__, __LINE__,"beforecomment timestamp is empty .");
        return ;
    }

    const string& owner = ctx->initiator() ;

    beforecomment ent;
    if( !_is_beforecomment_exist(kdid,owner,ent)) {
        _log_error(__FUNCTION__, __LINE__,"beforecomment " + kdid + " is not exist .");
        return ;
    }

    if( ent.owner() != owner) {
        _log_error(__FUNCTION__, __LINE__,ctx->initiator() + " is not owner, have no authority to update the comment .");
        return ;
    }

    if( !_delete_beforecomment_record(kdid,owner) ) {
        _log_error(__FUNCTION__, __LINE__,"delete beforecomment " + ent.to_string() + " failure .");
        return;
    }

    ent.set_owner(owner);
    ent.set_kdid(kdid);
    ent.set_satisfaction(stoll(satisfaction));
    ent.set_labels(labels);    
    ent.set_comment(comment);
    ent.set_timestamp(timestamp);
    if (!get_beforecomment_table().put(ent)) {
        _log_error(__FUNCTION__, __LINE__,"beforecomment table put " + ent.to_string() + " failure .");
        return;
    }

    ctx->ok("update beforecomment " + ent.to_string() + " success .");
}

void Buddha::find_beforecomment() {
    const string& kdid = ctx->arg("kdid");
    if( kdid.empty()) {
        _log_error(__FUNCTION__, __LINE__,"beforecomment kdid is empty .");
        return ;
    }

    kinddeed kd;
    if (!_is_kinddeed_exist(kdid, kd))  {
        _log_error(__FUNCTION__, __LINE__,"kinddeed " + kdid + " is not exist .");
        return ;
    }

    const string& owner = ctx->arg("owner");

    if( !owner.empty()) {
        beforecomment ent;
        if (!_is_beforecomment_exist(kdid,owner,ent))  {
            ctx->ok("beforecomment " + kdid + " is not exist .");
            return ;
        }

        if( is_founder() ||                      //基金会成员
            owner == ctx->initiator() ||        //点评的所有者
            kd.owner() == ctx->initiator() ) { //善举所有者
            ctx->ok(ent.to_string());
            return ;
        }

        _log_error(__FUNCTION__, __LINE__,ctx->initiator() + " is not founder nor owner, have no authority to delete the comment .");
        return ;

    }

    //owner字段为空的情况
    //此时如果是基金会成员和善举所有者调用，报错
    if( is_founder() ||                          //基金会成员
        kd.owner() == ctx->initiator() ) {      //善举所有者
        _log_error(__FUNCTION__, __LINE__,"beforecomment owner should be empty .");
        return ;
    }

    //点评所有者调用，直接查询
    beforecomment ent;
    if (!_is_beforecomment_exist(kdid,ctx->initiator(),ent))  {
        ctx->ok("beforecomment " + kdid + " is not exist .");
        return ;
    }
    ctx->ok(ent.to_string());
}

void Buddha::list_beforecomment() {
    const string& kdid = ctx->arg("kdid");
    if( kdid.empty()) {
        _log_error(__FUNCTION__, __LINE__,"beforecomment kdid is empty .");
        return ;
    }

    kinddeed kd;
    if (!_is_kinddeed_exist(kdid, kd))  {
        _log_error(__FUNCTION__, __LINE__,"kinddeed " + kdid + " is not exist .");
        return ;
    }

    auto it = get_beforecomment_table().scan({{"kdid",kdid}});
    int i = 0;
    string ret;
    while(it->next()) {
        beforecomment ent;
        if (!it->get(&ent)) {
            _log_error(__FUNCTION__, __LINE__, "beforecomment table get failure : " + it->error(true));
            return;
        }

        i++;
        ret += ent.to_string();
    }
    ctx->ok("size=" + to_string(i) + " " + ret);
}


namespace 用户祈求善举{}

void Buddha::pray_kinddeed() {

    const string& orderid = ctx->arg("id");
    if( orderid.empty()) {
        _log_error(__FUNCTION__, __LINE__,"orderid is empty .");
        return ;
    }

    const string& kdid = ctx->arg("kinddeed");
    if( kdid.empty()) {
        _log_error(__FUNCTION__, __LINE__,"kdid is empty .");
        return ;
    }

    const string& specid = ctx->arg("spec");
    if( specid.empty()) {
        _log_error(__FUNCTION__, __LINE__,"specid is empty .");
        return ;
    }

    const string& count = ctx->arg("count");
    if( count.empty()) {
        _log_error(__FUNCTION__, __LINE__,"count is empty .");
        return ;
    }

    const string& amount = ctx->transfer_amount();
    if( amount.empty()) {
        _log_error(__FUNCTION__, __LINE__,"amount is empty .");
        return ;
    }

    const string& timestamp = ctx->arg("timestamp");
    if( timestamp.empty()) {
        _log_error(__FUNCTION__, __LINE__,"timestamp is empty .");
        return ;
    }

    //判断订单是否存在
    order od;
    if (_is_order_exist(orderid,od))  {
        _log_error(__FUNCTION__, __LINE__,"order " + orderid + " is exist .");
        return ;
    }

    //判断善举是否存在
    kinddeed kd;
    if (!_is_kinddeed_exist(kdid, kd))  {
        _log_error(__FUNCTION__, __LINE__,"kinddeed " + kdid + " is not exist .");
        return ;
    }

    //判断善举是否已经上架
    if (!_is_kinddeed_online(kdid)) {
        _log_error(__FUNCTION__, __LINE__,"kinddeed " + kdid + " is not online .");
        return ;
    }

    //判断善举规格是否存在
    kinddeedspec spec;
    if (!_is_kinddeedspec_exist(kdid, specid, spec))  {
        _log_error(__FUNCTION__, __LINE__,"kinddeedspec " + kdid + "," + specid + " is not exist .");
        return ;
    }

    //计算总价格，要求转账过来的总价格跟订单计算出的总价格要求必须一直
    int64_t calced_amount = spec.price() * stoll(count);
    if( calced_amount != stoll(amount)){
        _log_error(__FUNCTION__, __LINE__,"delive amount " + amount
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
        _log_error(__FUNCTION__, __LINE__,"order table put " + od.to_string() + " failure .");
        return;
    }
    
    ctx->ok("pray kinddeed " + to_string(calced_amount) + " success .");
}

void Buddha::delete_pray_kinddeed() {

    const string& orderid = ctx->arg("id");
    if( orderid.empty()) {
        _log_error(__FUNCTION__, __LINE__,"orderid is empty .");
        return ;
    }

    //判断订单是否存在
    order ent;
    if (!_is_order_exist(orderid,ent))  {
        _log_error(__FUNCTION__, __LINE__,"order " + orderid + " is not exist .");
        return ;
    }

    //判断身份
    //判断是否是订单所有者，判断是否是善举所有者，判断是否是基金会成员或部署
    if( !is_deployer() &&
        !is_founder() &&
        ctx->initiator() != ent.kdowner() &&
        ctx->initiator() != ent.owner() ) {
        _log_error(__FUNCTION__, __LINE__,ctx->initiator() + " have no authority to delete the pray kinddeed .");
        return ;
    }

    if( !_delete_order_record(orderid) ) {
        _log_error(__FUNCTION__, __LINE__,"delete pray kinddeed " + ent.to_string() + " failure .");
        return;
    }

    ctx->ok("delete pray kinddeed " + ent.to_string() + " success .");
}

void Buddha::find_pray_kinddeed() {
    const string& id = ctx->arg("id");
    if( id.empty()) {
        _log_error(__FUNCTION__, __LINE__,"order id is empty .");
        return ;
    }

    order ent;       
    if (!_is_order_exist(id, ent)) {
        _log_error(__FUNCTION__, __LINE__,"order " + id + " is not exist .");
        return ;
    }

    if( !is_deployer() &&
        !is_founder() &&
        !is_temple() &&
        !is_master() &&
        ent.owner() != ctx->initiator()) {
        _log_error(__FUNCTION__, __LINE__,ctx->initiator() + " have no authority to find pray kinddeed .");
        return ;
    }

    ctx->ok(ent.to_string());
}

void Buddha::list_pray_kinddeed() {
    if( is_deployer() || 
        is_founder() ) {
        auto it = get_order_table().scan({{"id",ctx->arg("id")}});
        int i = 0;
        string ret;
        while(it->next()) {
            order ent;
            if (!it->get(&ent)) {
                _log_error(__FUNCTION__, __LINE__, "order table get failure : " + it->error(true));
                return;
            }

            i++;
            ret += ent.to_string();
        }
        ctx->ok("size=" + to_string(i) + " " + ret);
        return ;
    }

    if( is_temple() || 
        is_master()) {
        auto it = get_order_table().scan({{"kdowner", ctx->initiator()}});
        int i = 0;
        string ret;
        while(it->next()) {
            order ent;
            if (!it->get(&ent)) {
                _log_error(__FUNCTION__, __LINE__, "order table get failure : " + it->error(true));
                return;
            }

            i++;
            ret += ent.to_string();
        }
        ctx->ok("size=" + to_string(i) + " " + ret);
        return ;
    }

    _log_error(__FUNCTION__, __LINE__,ctx->initiator() + " have no authority to list order .");
}

bool Buddha::is_user() {
    if (!_is_user(ctx->initiator())) {
        ctx->ok(ctx->initiator() + " is not user .") ;
        return false;
    }

    ctx->ok(ctx->initiator() + " is user .") ;
    return true;
}

namespace 基金会成员授权法师或寺院上传的善举凭证{}

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

    kinddeedproof ent;
    if (_is_kinddeedproof_exist(orderid, ent))  {
        _log_error(__FUNCTION__, __LINE__,"kinddeedproof " + orderid + " is exist .");
        return ;
    }

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

    ctx->ok("apply kinddeed " + ent.to_string() + " proof over, please wait for approve .");
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

    kinddeedproof ent;
    if (!_is_kinddeedproof_exist(orderid, ent))  {
        _log_error(__FUNCTION__, __LINE__,"kinddeedproof " + orderid + " is not exist .");
        return ;
    }

    order od;
    if (!_is_order_exist(orderid, od)) {
        _delete_kinddeedproof_record(orderid);
        _log_error(__FUNCTION__, __LINE__,"order and suborder lost, kinddeedproof " + orderid + " be delete .");
        return ;
    }

    if (ent.approved())  {
        ctx->ok("kinddeedproof " + orderid + " has approved yet .");
        return ;
    }

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

    ctx->ok("approve kinddeed " + ent.to_string() + " proof success .");
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

    kinddeedproof ent;
    if (!_is_kinddeedproof_exist(orderid, ent))  {
        _log_error(__FUNCTION__, __LINE__,"kinddeedproof " + orderid + " is not exist .");
        return ;
    }

    order od;
    if (!_is_order_exist(orderid, od)) {
        _delete_kinddeedproof_record(orderid);
        _log_error(__FUNCTION__, __LINE__,"order lost, kinddeedproof " + orderid + " be delete .");
        return ;
    }

    if (ent.approved())  {
        ctx->ok("kinddeedproof " + orderid + " has approved yet .");
        return ;
    }

    if( !_delete_kinddeedproof_record(orderid) ) {
        _log_error(__FUNCTION__, __LINE__,"delete kinddeedproof " + ent.to_string() + " failure .");
        return;
    }

    ctx->ok("refuse kinddeed " + ent.to_string() + " proof success .");
}

void Buddha::find_kinddeedproof() {
    const string& orderid = ctx->arg("orderid");

    if( orderid.empty() ) {
        _log_error(__FUNCTION__, __LINE__,"kinddeedproof hash and orderid is empty .");
        return ;
    }

    order od;        
    if (!_is_order_exist(orderid, od))  {
        _log_error(__FUNCTION__, __LINE__,"order " + orderid + " is not exist .");
        return ;
    }

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

    ctx->ok(ent.to_string());
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
        ctx->ok("size=" + to_string(i) + " " + ret);
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
        ctx->ok("size=" + to_string(i) + " " + ret);
        return;
    }

    _log_error(__FUNCTION__, __LINE__,ctx->initiator() + " have no authority to list kinddeedproof .");
    return ;
}

namespace 添加删除修改祈求善举后点评 {}
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

    ctx->ok("add aftercomment " + ent.to_string() + " success .");
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

    ctx->ok("delete aftercomment " + ent.to_string() + " success .");
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

    ctx->ok("update aftercomment " + ent.to_string() + " success .");
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
        ctx->ok("aftercomment " + orderid + " is not exist .");
        return ;
    }

    ctx->ok(ent.to_string());
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
        ctx->ok("size=" + to_string(i) + " " + ret);
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
    ctx->ok("size=" + to_string(i) + " " + ret);

}

// ---------- 对外接口 -------------

DEFINE_METHOD(Buddha, initialize)               { self.initialize();                }
DEFINE_METHOD(Buddha, get_deployer)             { self.get_deployer();              }
DEFINE_METHOD(Buddha, is_deployer)              { self.is_deployer();               }

DEFINE_METHOD(Buddha, apply_founder)            { self.apply_founder();             }
DEFINE_METHOD(Buddha, approve_founder)          { self.approve_founder();           }
DEFINE_METHOD(Buddha, recusal_founder)          { self.recusal_founder();           }
DEFINE_METHOD(Buddha, is_founder)               { self.is_founder();                }
DEFINE_METHOD(Buddha, list_founder)             { self.list_founder();              }

DEFINE_METHOD(Buddha, apply_temple)             { self.apply_temple();              }
DEFINE_METHOD(Buddha, approve_temple)           { self.approve_temple();            }
DEFINE_METHOD(Buddha, recusal_temple)           { self.recusal_temple();            }
DEFINE_METHOD(Buddha, is_temple)                { self.is_temple();                 }
DEFINE_METHOD(Buddha, list_temple)              { self.list_temple();               }

DEFINE_METHOD(Buddha, apply_master)             { self.apply_master();              }
DEFINE_METHOD(Buddha, approve_master)           { self.approve_master();            }
DEFINE_METHOD(Buddha, recusal_master)           { self.recusal_master();            }
DEFINE_METHOD(Buddha, is_master)                { self.is_master();                 }
DEFINE_METHOD(Buddha, list_master)              { self.list_master();               }

DEFINE_METHOD(Buddha, apply_join_temple)        { self.apply_join_temple();         }
DEFINE_METHOD(Buddha, approve_join_temple)      { self.approve_join_temple();       }
DEFINE_METHOD(Buddha, recusal_join_temple)      { self.recusal_join_temple();       }
DEFINE_METHOD(Buddha, is_in_temple)             { self.is_in_temple();              }
DEFINE_METHOD(Buddha, list_temple_master)       { self.list_temple_master();        }

DEFINE_METHOD(Buddha, add_kinddeedtype)         { self.add_kinddeedtype();          }
DEFINE_METHOD(Buddha, delete_kinddeedtype)      { self.delete_kinddeedtype();       }
DEFINE_METHOD(Buddha, update_kinddeedtype)      { self.update_kinddeedtype();       }
DEFINE_METHOD(Buddha, find_kinddeedtype)        { self.find_kinddeedtype();         }
DEFINE_METHOD(Buddha, list_kinddeedtype)        { self.list_kinddeedtype();         }


DEFINE_METHOD(Buddha, add_kinddeeddetail)       { self.add_kinddeeddetail();        }
DEFINE_METHOD(Buddha, add_kinddeedspec)         { self.add_kinddeedspec();          }
DEFINE_METHOD(Buddha, add_kinddeed)             { self.add_kinddeed();              }
DEFINE_METHOD(Buddha, update_kinddeed)          { self.update_kinddeed();           }
DEFINE_METHOD(Buddha, delete_kinddeed)          { self.delete_kinddeed();           }
DEFINE_METHOD(Buddha, find_kinddeed)            { self.find_kinddeed();             }
DEFINE_METHOD(Buddha, list_kinddeed)            { self.list_kinddeed();             }
DEFINE_METHOD(Buddha, list_kinddeeddetail)      { self.list_kinddeeddetail();       }
DEFINE_METHOD(Buddha, list_kinddeedspec)        { self.list_kinddeedspec();         }


DEFINE_METHOD(Buddha, apply_online_kinddeed)    { self.apply_online_kinddeed();     }
DEFINE_METHOD(Buddha, apply_offline_kinddeed)   { self.apply_offline_kinddeed();    }
DEFINE_METHOD(Buddha, approve_online_kinddeed)  { self.approve_online_kinddeed();   }
DEFINE_METHOD(Buddha, approve_offline_kinddeed) { self.approve_offline_kinddeed();  }

DEFINE_METHOD(Buddha, add_commentlabel)         { self.add_commentlabel();          }
DEFINE_METHOD(Buddha, delete_commentlabel)      { self.delete_commentlabel();       }
DEFINE_METHOD(Buddha, update_commentlabel)      { self.update_commentlabel();       }
DEFINE_METHOD(Buddha, find_commentlabel)        { self.find_commentlabel();         }
DEFINE_METHOD(Buddha, list_commentlabel)        { self.list_commentlabel();         }

DEFINE_METHOD(Buddha, add_beforecomment)        { self.add_beforecomment();         }
DEFINE_METHOD(Buddha, delete_beforecomment)     { self.delete_beforecomment();      }
DEFINE_METHOD(Buddha, update_beforecomment)     { self.update_beforecomment();      }
DEFINE_METHOD(Buddha, find_beforecomment)       { self.find_beforecomment();        }
DEFINE_METHOD(Buddha, list_beforecomment)       { self.list_beforecomment();        }

DEFINE_METHOD(Buddha, pray_kinddeed)            { self.pray_kinddeed();             }
DEFINE_METHOD(Buddha, delete_pray_kinddeed)     { self.delete_pray_kinddeed();      }
DEFINE_METHOD(Buddha, find_pray_kinddeed)       { self.find_pray_kinddeed();        }
DEFINE_METHOD(Buddha, list_pray_kinddeed)       { self.list_pray_kinddeed();        }
DEFINE_METHOD(Buddha, is_user)                  { self.is_user();                   }

DEFINE_METHOD(Buddha, upload_kinddeedproof)     { self.upload_kinddeedproof();      }
DEFINE_METHOD(Buddha, approve_kinddeedproof)    { self.approve_kinddeedproof();     }
DEFINE_METHOD(Buddha, refuse_kinddeedproof)     { self.refuse_kinddeedproof();      }
DEFINE_METHOD(Buddha, find_kinddeedproof)       { self.find_kinddeedproof();        }
DEFINE_METHOD(Buddha, list_kinddeedproof)       { self.list_kinddeedproof();        }

DEFINE_METHOD(Buddha, add_aftercomment)         { self.add_aftercomment();          }
DEFINE_METHOD(Buddha, delete_aftercomment)      { self.delete_aftercomment();       }
DEFINE_METHOD(Buddha, update_aftercomment)      { self.update_aftercomment();       }
DEFINE_METHOD(Buddha, find_aftercomment)        { self.find_aftercomment();         }
DEFINE_METHOD(Buddha, list_aftercomment)        { self.list_aftercomment();         }

