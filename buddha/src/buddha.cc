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
        if (it->get(&ent)) {
            vent.push_back(ent);
        }
        else {
            mycout << "get error : " << it->error(true) << endl;
            return false;
        }            
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
        if (it->get(&ent)) {
            vent.push_back(ent);
        }
        else {
            mycout << "get error : " << it->error(true) << endl;
            return false;
        }            
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
            mycout << "type " << id << " not exist in comment label table ." << endl;
            return false;
        }            
    }

    return true;
}

bool Buddha::_is_beforecomment_exist(const string& owner, const string& kdid,beforecomment& ent) {
    if (!get_beforecomment_table().find({{"owner", owner},{"kdid", kdid}}, &ent))
        return false;

    return true;
}

bool Buddha::_is_order_exist(const string& id,order& ent) {
    if (!get_order_table().find({{"id", id}}, &ent))
        return false;

    return true;
}

bool Buddha::_is_kinddeedproof_exist_by_order(const string& orderid,kinddeedproof& ent) {
    if (!get_kinddeedproof_table().find({{"orderid", orderid}}, &ent))
        return false;

    return true;
}

bool Buddha::_is_kinddeedproof_exist_by_proof(const string& proof,kinddeedproof& ent) {
    if (!get_kinddeedproof_table().find({{"proof", proof}}, &ent))
        return false;

    return true;
}

bool Buddha::_is_aftercomment_exist(const string& orderid,aftercomment& ent) {
    if (!get_aftercomment_table().find({{"orderid", orderid}}, &ent))
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
        mycout << "delete kinddeed type " << ent.to_string() << " failure ." << endl ;
        return false;
    }

    mycout << "delete kinddeed type " << ent.to_string() << " success ." << endl ;
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

    if( !_delete_kinddeeddetail_record(id) ) {
        mycout << "delete kinddeed detail " << id << " failure ." << endl ;
        return false;
    }

    if( !_delete_kinddeedspec_record(id) ) {
        mycout << "delete kinddeed spec " << id << " failure ." << endl ;
        return false;
    }

    mycout << "delete kinddeed " << ent.to_string() << " success ." << endl ;
    return true;
}

bool Buddha::_delete_kinddeeddetail_record(const string& id) {

    while(true) {
        kinddeeddetail ent;
        if (!get_kinddeeddetail_table().find({{"kdid", id}}, &ent))
            break;

        if( !get_kinddeeddetail_table().del(ent) ) {
            mycout << "delete kinddeed detail " << ent.to_string() << " failure ." << endl ;
            return false;
        }
    }

    mycout << "delete kinddeed details success ." << endl ;
    return true;
}

bool Buddha::_delete_kinddeedspec_record(const string& id) {
    while(true) {
        kinddeedspec ent;
        if (!get_kinddeedspec_table().find({{"kdid", id}}, &ent))
            break;

        if( !get_kinddeedspec_table().del(ent) ) {
            mycout << "delete kinddeed spec " << ent.to_string() << " failure ." << endl ;
            return false;
        }
    }

    mycout << "delete kinddeed specs success ." << endl ;
    return true;
}

bool Buddha::_delete_commentlabel_record(const string& id) {
    commentlabel ent;
    if (!_is_commentlabel_exist(id, ent)){
        mycout << "comment label " << id << " is not exist ." << endl ;
        return false;
    }

    if( !get_commentlabel_table().del(ent) ) {
        mycout << "delete comment label " << ent.to_string() << " failure ." << endl ;
        return false;
    }

    mycout << "delete comment label " << ent.to_string() << " success ." << endl ;
    return true;
}

bool Buddha::_delete_beforecomment_record(const string& owner, const string& kdid) {
    beforecomment ent;
    if (!_is_beforecomment_exist(owner, kdid, ent)){
        mycout << "before comment  " << owner << "," << kdid << " is not exist ." << endl ;
        return false;
    }

    if( !get_beforecomment_table().del(ent) ) {
        mycout << "delete before comment " << ent.to_string() << " failure ." << endl ;
        return false;
    }

    mycout << "delete before comment " << ent.to_string() << " success ." << endl ;
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
    if (!_is_kinddeedproof_exist_by_order(orderid, ent)){
        mycout << "kinddeed proof " << orderid << " is not exist ." << endl ;
        return false;
    }

    if( !get_kinddeedproof_table().del(ent) ) {
        mycout << "delete kinddeed proof " << ent.to_string() << " failure ." << endl ;
        return false;
    }

    mycout << "delete kinddeed proof " << ent.to_string() << " success ." << endl ;
    return true;
}

bool Buddha::_delete_aftercomment_record(const string& orderid) {
    aftercomment ent;
    if (!_is_aftercomment_exist(orderid, ent)){
        mycout << "after comment " << orderid << " is not exist ." << endl ;
        return false;
    }

    if( !get_aftercomment_table().del(ent) ) {
        mycout << "delete after comment " << ent.to_string() << " failure ." << endl ;
        return false;
    }

    mycout << "delete after comment " << ent.to_string() << " success ." << endl ;
    return true;
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
        ctx->error("unknown deployer .");
        return ;
    }

    if( !_is_deployer(ctx->initiator()) &&
        !_is_founder(ctx->initiator()) ) {
        ctx->error(ctx->initiator() + " is not deployer nor founder, have no authority to get deployer .");
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
        ctx->error("desc is empty");
        return ;
    }
    
    const string& guaranty = ctx->transfer_amount();
    if( guaranty.empty()) {
        ctx->error("guaranty is empty");
        return ;
    }

    if( is_founder()) {
        ctx->error(ctx->initiator() + " is already founder .");
        return ;
    }

    _delete_founder_record(ctx->initiator());

    founder ent;
    ent.set_id(ctx->initiator().c_str());
    ent.set_desc(desc.c_str());
    ent.set_guaranty(ent.guaranty() + stoll(guaranty));
    ent.set_approved(false);
    if (!get_founder_table().put(ent)) {
        ctx->error("founder table put "+ ent.to_string() + " error .");
        return;
    }

    ctx->ok(ent.to_string() + " apply tobe founder over, please wait for approve .");
}

void Buddha::approve_founder() {
    const string& id = ctx->arg("id");
    if( id.empty()) {
        ctx->error("founder id is empty");
        return ;
    }

    if( !is_deployer()) {
        ctx->error(ctx->initiator() + " is not deployer, have no authority to approve founder .");
        return ;
    }

    founder ent;
    if( !_is_founder_exist(id,ent)) {
        ctx->error("founder " + id + " is not exist .");
        return ;
    }

    if( _is_founder(id)) {
        ctx->error(ent.to_string() + " is already founder .");
        return ;
    }

    if( !_delete_founder_record(id) ) {
        ctx->error("delete founder "+ ent.to_string() + " failure .");
        return;
    }

    ent.set_approved(true);
    if (!get_founder_table().put(ent)) {
        ctx->error("founder table put "+ ent.to_string() + " error .");
        return;
    }

    ctx->ok("audit "+ ent.to_string() + " to be founder .");
}

void Buddha::recusal_founder() {
    const string& id = ctx->arg("id");
    if( id.empty()) {
        ctx->error("founder id is empty .");
        return ;
    }

    if( !is_deployer()) {
        ctx->error(ctx->initiator() + " is not deployer, have no authority recusal founder .");
        return ;
    }

    founder ent;
    if( !_is_founder_exist(id,ent)) {
        ctx->error("founder " + id + " is not exist .");
        return ;
    }

    if( !_delete_founder_record(id) ) {
        ctx->error("delete founder "+ ent.to_string() + " failure .");
        return;
    }

    //将抵押退还
    string guaranty = to_string(ent.guaranty());
    if( !_transfer(id, guaranty)) {
        ctx->error("refund transfer " + guaranty + " to " + id + " failure .");
        return ;
    }

    ctx->ok("recusal founder "+ id + " success , guaranty " + guaranty + " has refund, please check balance.");
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
        ctx->error(ctx->initiator() + " is not deployer nor founder, have no authority to list founder .");
        return ;
    }

    auto it = get_founder_table().scan({{"id",ctx->arg("id")}});
    int i = 0;
    string ret;
    while(it->next()) {
        founder ent;
        if (it->get(&ent)) {
            i++;
            ret += ent.to_string();
        }
        else
            cout << __LINE__ << " get error : " << it->error(true) << endl;
    }
    ctx->ok("size=" + to_string(i) + " " + ret);
}

namespace 申请成为寺院{}

void Buddha::apply_temple(){
    const string& unit = ctx->arg("unit");
    if( unit.empty()) {
        ctx->error("unit is empty");
        return ;
    }
    
    const string& creditcode = ctx->arg("creditcode");
    if( creditcode.empty()) {
        ctx->error("creditcode is empty");
        return ;
    }
    
    const string& address = ctx->arg("address");
    if( address.empty()) {
        ctx->error("address is empty");
        return ;
    }
    
    const string& proof = ctx->arg("proof");
    if( proof.empty()) {
        ctx->error("proof is empty");
        return ;
    }

    if( !is_user() &&
        !is_master()) {
        ctx->error(ctx->initiator() + " is not user or master, have no authority to apply tobe temple .");
        return ;
    }

    if( is_temple()) {
        ctx->error(ctx->initiator() + " is already temple .");
        return ;
    }

    _delete_temple_record(ctx->initiator());

    temple ent;
    ent.set_id(ctx->initiator().c_str());
    ent.set_unit(unit.c_str());
    ent.set_creditcode(creditcode.c_str());
    ent.set_address(address.c_str());
    ent.set_proof(proof.c_str());
    ent.set_approved(false);
    if (!get_temple_table().put(ent)) {
        ctx->error("temple table put "+ ent.to_string() + " error .");
        return;
    }

    ctx->ok(ent.to_string() + " apply tobe temple over, please wait for approve .");
}

void Buddha::approve_temple() {
    const string& id = ctx->arg("id");
    if( id.empty()) {
        ctx->error("temple id is empty");
        return ;
    }

    if( !is_founder()) {
        ctx->error(ctx->initiator() + " is not founder, have no authority to approve temple .");
        return ;
    }

    temple ent;
    if( !_is_temple_exist(id,ent)) {
        ctx->error("temple " + id + " is not exist .");
        return ;
    }

    if( _is_temple(id)) {
        ctx->error(ent.to_string() + " is already temple .");
        return ;
    }

    if( !_delete_temple_record(id) ) {
        ctx->error("delete temple "+ ent.to_string() + " failure .");
        return;
    }

    ent.set_approved(true);
    if (!get_temple_table().put(ent)) {
        ctx->error("temple table put "+ ent.to_string() + " error .");
        return;
    }

    ctx->ok("approve temple "+ ent.to_string() + " success .");
}

void Buddha::recusal_temple() {
    const string& id = ctx->arg("id");
    if( id.empty()) {
        ctx->error("temple id is empty");
        return ;
    }
    
    if( !is_founder()) {
        ctx->error(ctx->initiator() + " is not founder, have no authority to recusal temple .");
        return ;
    }

    temple ent;
    if( !_is_temple_exist(id,ent)) {
        ctx->error("temple " + id + " is not exist .");
        return ;
    }

    if( !_delete_temple_record(id) ) {
        ctx->error("delete temple "+ ent.to_string() + " failure .");
        return;
    }

    ctx->ok("recusal temple "+ ent.to_string() + " success .");
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
        ctx->error(ctx->initiator() + " is not deployer nor founder, have no authority to list temple .");
        return ;
    }

    auto it = get_temple_table().scan({{"id",ctx->arg("id")}});
    int i = 0;
    string ret;
    while(it->next()) {
        temple ent;
        if (it->get(&ent)) {
            i++;
            ret += ent.to_string();
        }
        else
            cout << __LINE__ << " get error : " << it->error(true) << endl;
    }
    ctx->ok("size=" + to_string(i) + " " + ret);
}

namespace 申请成为法师{}

void Buddha::apply_master(){
    const string& creditcode = ctx->arg("creditcode");
    if( creditcode.empty()) {
        ctx->error("creditcode is empty");
        return ;
    }

    const string& proof = ctx->arg("proof");
    if( proof.empty()) {
        ctx->error("proof is empty");
        return ;
    }

    if( !is_user()) {
        ctx->error(ctx->initiator() + " is not user, have no authority to apply tobe master .");
        return ;
    }

    if( is_master()) {
        ctx->error(ctx->initiator() + " is already master .");
        return ;
    }

    _delete_master_record(ctx->initiator());

    master ent;
    ent.set_id(ctx->initiator().c_str());
    ent.set_creditcode(creditcode.c_str());
    ent.set_proof(proof.c_str());
    ent.set_approved(false);
    if (!get_master_table().put(ent)) {
        ctx->error("master table put "+ ent.to_string() + " error .");
        return;
    }

    ctx->ok(ent.to_string() + " apply tobe master over, please wait for approve .");
}

void Buddha::approve_master() {
    const string& id = ctx->arg("id");
    if( id.empty()) {
        ctx->error("master id is empty");
        return ;
    }

    if( !is_founder()) {
        ctx->error(ctx->initiator() + " is not founder, have no authority to approve master .");
        return ;
    }

    master ent;
    if( !_is_master_exist(id,ent)) {
        ctx->error("master " + id + " is not exist .");
        return ;
    }

    if( _is_master(id)) {
        ctx->error(ent.to_string() + " is already master .");
        return ;
    }

    if( !_delete_master_record(id) ) {
        ctx->error("delete master "+ ent.to_string() + " failure .");
        return;
    }

    ent.set_approved(true);
    if (!get_master_table().put(ent)) {
        ctx->error("master table put "+ ent.to_string() + " error .");
        return;
    }

    ctx->ok("approve master "+ ent.to_string() + " success .");
}

void Buddha::recusal_master() {
    const string& id = ctx->arg("id");
    if( id.empty()) {
        ctx->error("master id is empty");
        return ;
    }
    
    if( !is_founder()) {
        ctx->error(ctx->initiator() + " is not founder, have no authority to recusal master .");
        return ;
    }

    master ent;
    if( !_is_master_exist(id,ent)) {
        ctx->error("master " + id + " is not exist .");
        return ;
    }

    if( !_delete_master_record(id) ) {
        ctx->error("delete master "+ ent.to_string() + " failure .");
        return;
    }

    ctx->ok("recusal master "+ ent.to_string() + " success .");
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
        ctx->error(ctx->initiator() + " is not deployer nor founder, have no authority to list master .");
        return ;
    }

    auto it = get_master_table().scan({{"id",ctx->arg("id")}});
    int i = 0;
    string ret;
    while(it->next()) {
        master ent;
        if (it->get(&ent)) {
            i++;
            ret += ent.to_string();
        }
        else
            cout << __LINE__ << " get error : " << it->error(true) << endl;
    }
    ctx->ok("size=" + to_string(i) + " " + ret);
}

namespace 申请加入寺院{}

void Buddha::apply_join_temple(){
    const string& templeid = ctx->arg("templeid");
    if( templeid.empty()) {
        ctx->error("templeid is empty");
        return ;
    }

    if( !is_master()) {
        ctx->error(ctx->initiator() + " is not master, have no authority to apply join temple .");
        return ;
    }

    if( !_is_temple(templeid)) {
        ctx->error( templeid + " is not a temple .");
        return ;
    }

    templemaster ent;
    if( _is_in_temple(templeid, ctx->initiator(), ent )) {
        ctx->ok(ctx->initiator() + " is already join temple .");
        return;
    }
    
    _delete_templemaster_record(templeid, ctx->initiator());
    
    ent.set_templeid(templeid.c_str());
    ent.set_masterid(ctx->initiator().c_str());
    ent.set_approved(false);
    if (!get_templemaster_table().put(ent)) {
        ctx->error("templemaster table put "+ ent.to_string() + " error .");
        return;
    }

    ctx->ok(ent.to_string() + " apply join templemaster over, please wait for approve .");
}

void Buddha::approve_join_temple() {
    const string& templeid = ctx->arg("templeid");
    if( templeid.empty()) {
        ctx->error("temple id is empty");
        return ;
    }

    const string& masterid = ctx->arg("masterid");
    if( masterid.empty()) {
        ctx->error("master id is empty");
        return ;
    }

    if( !is_founder()) {
        ctx->error(ctx->initiator() + " is not founder, have no authority to approve master .");
        return ;
    }

    if( !_is_master(masterid)) {
        ctx->error( masterid + " is not a master .");
        return ;
    }

    if( !_is_temple(templeid)) {
        ctx->error( templeid + " is not a temple .");
        return ;
    }

    templemaster ent;
    if( _is_in_temple(masterid, templeid, ent)) {
        ctx->error(ent.to_string() + " is already join temple .");
        return ;
    }

    if( !_delete_templemaster_record(templeid, masterid) ) {
        ctx->error("delete templemaster "+ ent.to_string() + " failure .");
        return;
    }

    ent.set_approved(true);
    if (!get_templemaster_table().put(ent)) {
        ctx->error("templemaster table put "+ ent.to_string() + " error .");
        return;
    }

    ctx->ok("approve templemaster "+ ent.to_string() + " success .");
}

void Buddha::recusal_join_temple() {
    const string& templeid = ctx->arg("templeid");
    if( templeid.empty()) {
        ctx->error("temple id is empty");
        return ;
    }

    const string& masterid = ctx->arg("masterid");
    if( masterid.empty()) {
        ctx->error("master id is empty");
        return ;
    }
    
    if( !is_founder()) {
        ctx->error(ctx->initiator() + " is not founder, have no authority to recusal master .");
        return ;
    }

    templemaster ent;
    if( !_is_templemaster_exist(templeid, masterid,ent)) {
        ctx->error("temple " + templeid + ", master " + masterid + " is not exist .");
        return ;
    }

    if( !_delete_templemaster_record(templeid, masterid) ) {
        ctx->error("delete templemaster "+ ent.to_string() + " failure .");
        return;
    }

    ctx->ok("recusal templemaster "+ ent.to_string() + " success .");
}

bool Buddha::is_in_temple() {
    const string& templeid = ctx->arg("templeid");
    if( templeid.empty()) {
        ctx->error("temple id is empty");
        return false;
    }

    if( !_is_master(ctx->initiator())) {
        ctx->error( ctx->initiator() + " is not a master, have no authority to query in some temple .");
        return false;
    }

    if( !_is_temple(templeid)) {
        ctx->error(templeid + " is not a temple .");
        return false;
    }

    templemaster ent;
    if (_is_in_temple(templeid, ctx->initiator(), ent)) {
        ctx->ok(ctx->initiator() + " is join temple .") ;
        return true;
    }
    
    ctx->ok(ctx->initiator() + " is not join temple .") ;
    return false;
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
            if (it->get(&ent)) {
                i++;
                ret += ent.to_string();
            }
            else
                cout << __LINE__ << " get error : " << it->error(true) << endl;
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
            if (it->get(&ent)) {
                i++;
                ret += ent.to_string();
            }
            else
                cout << __LINE__ << " get error : " << it->error(true) << endl;
        }
        ctx->ok("size=" + to_string(i) + " " + ret);
        return ;
    }

    ctx->error(ctx->initiator() + " have no authority to list temple master .");
    return ;
}

namespace 添加删除修改善举类型{}

void Buddha::add_kinddeedtype() {
    const string& id = ctx->arg("id");
    if( id.empty()) {
        ctx->error("kinddeed type id is empty");
        return ;
    }

    const string& desc = ctx->arg("desc");
    if( desc.empty()) {
        ctx->error("kinddeed type desc is empty");
        return ;
    }

    if( !is_founder() ) {
        ctx->error(ctx->initiator() + " is not founder, have no authority to add kinddeed type .");
        return ;
    }

    kinddeedtype ent;
    if( _is_kinddeedtype_exist(id,ent)) {
        ctx->error("kinddeedtype " + id + " is exist .");
        return ;
    }

    ent.set_id(stoll(id.c_str()));
    ent.set_desc(desc.c_str());
    if (!get_kinddeedtype_table().put(ent)) {
        ctx->error("kinddeedtype table put "+ ent.to_string() + " error .");
        return;
    }

    ctx->ok("add kinddeed type " + ent.to_string() + " success .");
}

void Buddha::delete_kinddeedtype() {
    const string& id = ctx->arg("id");
    if( id.empty()) {
        ctx->error("kinddeed type id is empty");
        return ;
    }

    if( !is_founder() ) {
        ctx->error(ctx->initiator() + " is not founder, have no authority to delete kinddeed type .");
        return ;
    }

    kinddeedtype ent;
    if( !_is_kinddeedtype_exist(id,ent)) {
        ctx->error("kindeed type " + id + " is not exist .");
        return ;
    }

    if( !_delete_kinddeedtype_record(id) ) {
        ctx->error("delete kinddeed type "+ ent.to_string() + " failure .");
        return;
    }

    ctx->ok("delete kinddeed type " + ent.to_string() + " success .");
}

void Buddha::update_kinddeedtype() {
    const string& id = ctx->arg("id");
    if( id.empty()) {
        ctx->error("kinddeed type id is empty");
        return ;
    }

    const string& desc = ctx->arg("desc");
    if( desc.empty()) {
        ctx->error("kinddeed type desc is empty");
        return ;
    }

    if( !is_founder() ) {
        ctx->error(ctx->initiator() + " is not founder, have no authority to update kinddeed type .");
        return ;
    }

    kinddeedtype ent;
    if( !_is_kinddeedtype_exist(id,ent)) {
        ctx->error("kindeed type " + id + " is not exist .");
        return ;
    }

    if( !_delete_kinddeedtype_record(id) ) {
        ctx->error("delete kinddeed type "+ ent.to_string() + " failure .");
        return;
    }

    ent.set_id(stoll(id.c_str()));
    ent.set_desc(desc.c_str());
    if (!get_kinddeedtype_table().put(ent)) {
        ctx->error("kinddeedtype table put "+ ent.to_string() + " error .");
        return;
    }

    ctx->ok("update kinddeed type " + ent.to_string() + " success .");
}

void Buddha::find_kinddeedtype() {
    const string& id = ctx->arg("id");
    if( id.empty()) {
        ctx->error("kinddeed type id is empty");
        return ;
    }

    kinddeedtype ent;
    if (!_is_kinddeedtype_exist(id, ent))  {
        ctx->ok("kinddeed type " + id + " is not exist .");
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
        if (it->get(&ent)) {
            i++;
            ret += ent.to_string();
        }
        else
            cout << __LINE__ << " get error : " << it->error(true) << endl;
    }
    ctx->ok("size=" + to_string(i) + " " + ret);
}


namespace 添加删除修改善举{}

void Buddha::add_kinddeed() {
    const string& id = ctx->arg("id");
    const string& name = ctx->arg("name");
    const string& owner = ctx->initiator();
    const string& type = ctx->arg("type");
    const string& lasttime = ctx->arg("lasttime");
    const string& detail = ctx->arg("detail");
    const string& spec = ctx->arg("spec");

    if( id.empty()) {
        ctx->error("kinddeed id is empty");
        return ;
    }

    if( name.empty()) {
        ctx->error("kinddeed name is empty");
        return ;
    }

    if( type.empty()) {
        ctx->error("kinddeed type is empty");
        return ;
    }

    if( lasttime.empty()) {
        ctx->error("kinddeed lasttime is empty");
        return ;
    }
    
    auto detail_array = xchain::json::parse(detail);
    // mycout << detail_array.dump().c_str() << endl ;
    if (!detail_array.is_array()) {
        ctx->error("field 'detail' need to be array .");
        return;
    }
    
    if ( detail_array.empty() || detail_array.size() == 0) {
        ctx->error("filed 'detail' empty .");
        return;
    }

    auto spec_array = xchain::json::parse(spec);
    // mycout << spec_array.dump().c_str() << endl ;
    if (!spec_array.is_array()) {
        ctx->error("field 'spec' need to be array .");
        return;
    }
    
    if ( spec_array.empty() || spec_array.size() == 0) {
        ctx->error("filed 'spec' empty .");
        return;
    }

    if( !is_founder() &&
        !is_temple() &&
        !is_master() ) {
        ctx->error(ctx->initiator() + " is not founder,temple and master, have no authority to add kinddeed .");
        return ;
    }

    kinddeed ent;
    if (_is_kinddeed_exist(id, ent))  {
        ctx->error("kinddeed " + ent.to_string() + " is exist .");
        return ;
    }

    kinddeedtype type_ent;
    if (!_is_kinddeedtype_exist(type, type_ent))  {
        ctx->error("kinddeed type " + type + " is not exist .");
        return ;
    }

    vector<kinddeeddetail> v_kinddeeddetail_ent;
    if (_is_kinddeeddetail_exist_by_kdid(id, v_kinddeeddetail_ent))  {
        ctx->error("kinddeed detail " + ent.to_string() + " is exist .");
        return ;
    }

    vector<kinddeedspec> v_kinddeedspec_ent;
    if (_is_kinddeedspec_exist_by_kdid(id, v_kinddeedspec_ent))  {
        ctx->error("kinddeed spec " + ent.to_string() + " is exist .");
        return ;
    }

    for(int i = 0 ; i < detail_array.size() ; i++) {
        int64_t sequence = stoll(detail_array.at(i)["sequence"].template get<string>());
        string hash = detail_array.at(i)["hash"].template get<string>();

        kinddeeddetail ent;
        ent.set_kdid(id.c_str());
        ent.set_sequence(sequence);
        ent.set_hash(hash.c_str());

        if (!get_kinddeeddetail_table().put(ent)) {
            ctx->error("kinddeed detail table put "+ ent.to_string() + " error .");
            return;
        }
    }

    // mycout << spec_array.dump().c_str() << endl ;
    for(int i = 0 ; i < spec_array.size() ; i++) {
        int64_t sequence = stoll(spec_array.at(i)["sequence"].template get<string>());
        string desc = spec_array.at(i)["desc"].template get<string>();
        int64_t price = stoll(spec_array.at(i)["price"].template get<string>());

        kinddeedspec ent;
        ent.set_kdid(id.c_str());
        ent.set_sequence(sequence);
        ent.set_desc(desc.c_str());
        ent.set_price(price);

        if (!get_kinddeedspec_table().put(ent)) {
            ctx->error("kinddeed spec table put "+ ent.to_string() + " error .");
            return;
        }
    }

    ent.set_id(id.c_str());
    ent.set_name(name.c_str());
    ent.set_owner(ctx->initiator().c_str());
    ent.set_type(stoll(type.c_str()));
    ent.set_lasttime(lasttime.c_str());
    ent.set_applied(false);
    ent.set_online(false);

    if (!get_kinddeed_table().put(ent)) {
        ctx->error("kinddeed table put "+ ent.to_string() + " error .");
        return;
    }

    ctx->ok("add kinddeed " + ent.to_string() + " success .");
}

void Buddha::delete_kinddeed() {

    const string& id = ctx->arg("id");
    if( id.empty()) {
        ctx->error("kinddeed id is empty");
        return ;
    }

    kinddeed ent;
    if (!_is_kinddeed_exist(id, ent))  {
        ctx->error("kinddeed " + id + " is not exist .");
        return ;
    }

    if( !is_founder() &&
        !is_temple() &&
        !is_master() ) {
        ctx->error(ctx->initiator() + " is not founder and master, have no authority to delete kinddeed .");
        return ;
    }

    if( ent.owner() != ctx->initiator() ) {
        ctx->error("kinddeed " + ent.to_string() + " is not belong to you.");
        return ;
    }

    if( !_delete_kinddeed_record(id) ) {
        ctx->error("delete kinddeed "+ ent.to_string() + " failure .");
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
        ctx->error("kinddeed id is empty");
        return ;
    }

    if( name.empty()) {
        ctx->error("kinddeed name is empty");
        return ;
    }

    if( type.empty()) {
        ctx->error("kinddeed type is empty");
        return ;
    }

    if( lasttime.empty()) {
        ctx->error("kinddeed lasttime is empty");
        return ;
    }

    auto detail_array = xchain::json::parse(detail);
    // mycout << detail_array.dump().c_str() << endl ;
    if (!detail_array.is_array()) {
        ctx->error("field 'detail' need to be array .");
        return;
    }
    
    if ( detail_array.empty() || detail_array.size() == 0) {
        ctx->error("filed 'detail' empty .");
        return;
    }

    auto spec_array = xchain::json::parse(spec);
    // mycout << spec_array.dump().c_str() << endl ;
    if (!spec_array.is_array()) {
        ctx->error("field 'spec' need to be array .");
        return;
    }
    
    if ( spec_array.empty() || spec_array.size() == 0) {
        ctx->error("filed 'spec' empty .");
        return;
    }

    if( !is_founder() &&
        !is_temple() &&
        !is_master() ) {
        ctx->error(ctx->initiator() + " is not founder and master, have no authority to update kinddeed .");
        return ;
    }

    kinddeed ent;
    if (_is_kinddeed_exist(id, ent))  {
        ctx->error("kinddeed " + ent.to_string() + " is exist .");
        return ;
    }

    kinddeedtype type_ent;
    if (!_is_kinddeedtype_exist(type, type_ent))  {
        ctx->error("kinddeed type " + type + " is not exist .");
        return ;
    }

    vector<kinddeeddetail> v_kinddeeddetail_ent;
    if (_is_kinddeeddetail_exist_by_kdid(id, v_kinddeeddetail_ent))  {
        ctx->error("kinddeed detail " + ent.to_string() + " is exist .");
        return ;
    }

    vector<kinddeedspec> v_kinddeedspec_ent;
    if (_is_kinddeedspec_exist_by_kdid(id, v_kinddeedspec_ent))  {
        ctx->error("kinddeed spec " + ent.to_string() + " is exist .");
        return ;
    }

    for(int i = 0 ; i < detail_array.size() ; i++) {
        int64_t sequence = stoll(detail_array.at(i)["sequence"].template get<string>());
        string hash = detail_array.at(i)["hash"].template get<string>();

        kinddeeddetail ent;
        ent.set_kdid(id.c_str());
        ent.set_sequence(sequence);
        ent.set_hash(hash.c_str());

        if (!get_kinddeeddetail_table().put(ent)) {
            ctx->error("kinddeed detail table put "+ ent.to_string() + " error .");
            return;
        }
    }
    
    for(int i = 0 ; i < spec_array.size() ; i++) {
        int64_t sequence = stoll(spec_array.at(i)["sequence"].template get<string>());
        string desc = spec_array.at(i)["desc"].template get<string>();
        int64_t price = stoll(spec_array.at(i)["price"].template get<string>());

        kinddeedspec ent;
        ent.set_kdid(id.c_str());
        ent.set_sequence(sequence);
        ent.set_desc(desc.c_str());
        ent.set_price(price);

        if (!get_kinddeedspec_table().put(ent)) {
            ctx->error("kinddeed spec table put "+ ent.to_string() + " error .");
            return;
        }
    }

    ent.set_id(id.c_str());
    ent.set_name(name.c_str());
    ent.set_owner(ctx->initiator().c_str());
    ent.set_type(stoll(type.c_str()));
    ent.set_lasttime(lasttime.c_str());
    ent.set_applied(false);
    ent.set_online(false);

    if (!get_kinddeed_table().put(ent)) {
        ctx->error("kinddeed table put "+ ent.to_string() + " error .");
        return;
    }

    ctx->ok("update kinddeed " + ent.to_string() + " success .");
}

void Buddha::find_kinddeed() {       

    const string& id = ctx->arg("id");
    if( id.empty()) {
        ctx->error("kinddeed id is empty");
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
            if (it->get(&ent)) {
                i++;
                ret += ent.to_string();
            }
            else
                cout << __LINE__ << " get error : " << it->error(true) << endl;
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
            if (it->get(&ent)) {
                i++;
                ret += ent.to_string();
            }
            else
                cout << __LINE__ << " get error : " << it->error(true) << endl;
        }
        ctx->ok("size=" + to_string(i) + " " + ret);
        return ;
    }

    ctx->error(ctx->initiator() + " have no authority to list kinddeed .");
}

namespace 申请善举上架下架{}

void Buddha::apply_online_kinddeed() {
    const string& id = ctx->arg("id");
    if( id.empty()) {
        ctx->error("kinddeed id is empty");
        return ;
    }

    if( !is_temple() &&
        !is_master() ) {
        ctx->error(ctx->initiator() + " is not temple nor master, have no authority to apply online kinddeed .");
        return ;
    }

    kinddeed ent;
    if (!_is_kinddeed_exist(id, ent))  {
        ctx->error("kinddeed " + id + " is not exist .");
        return ;
    }

    if (ent.online()==true){
        ctx->error("kinddeed " + ent.to_string() + " is already online .");
        return ;
    }

    if( ent.owner() != ctx->initiator() ) {
        ctx->error("kinddeed " + ent.to_string() + " is not belong to you.");
        return ;
    }

    if( !_delete_kinddeed_record(id) ) {
        ctx->error("delete kinddeed "+ ent.to_string() + " failure .");
        return;
    }

    ent.set_applied(true);
    if (!get_kinddeed_table().put(ent)) {
        ctx->error("kinddeed table put "+ ent.to_string() + " error .");
        return;
    }

    ctx->ok("kinddeed " + ent.to_string() + " apply online over, please wait for approve .");
}

void Buddha::apply_offline_kinddeed() {
    const string& id = ctx->arg("id");
    if( id.empty()) {
        ctx->error("kinddeed id is empty");
        return ;
    }

    if( !is_temple() &&
        !is_master() ) {
        ctx->error(ctx->initiator() + " is not temple nor master, have no authority to apply offline kinddeed .");
        return ;
    }

    kinddeed ent;
    if (!_is_kinddeed_exist(id, ent))  {
        ctx->error("kinddeed " + id + " is not exist .");
        return ;
    }

    if (ent.online()==false){
        ctx->error("kinddeed " + ent.to_string() + " is already offline .");
        return ;
    }

    if( ent.owner() != ctx->initiator() ) {
        ctx->error("kinddeed " + ent.to_string() + " is not belong to you.");
        return ;
    }

    if( !_delete_kinddeed_record(id) ) {
        ctx->error("delete kinddeed "+ ent.to_string() + " failure .");
        return;
    }

    ent.set_applied(true);
    if (!get_kinddeed_table().put(ent)) {
        ctx->error("kinddeed table put "+ ent.to_string() + " error .");
        return;
    }

    ctx->ok("kinddeed " + ent.to_string() + " apply offline over, please wait for approve .");
}

void Buddha::approve_online_kinddeed() {
    const string& id = ctx->arg("id");
    if( id.empty()) {
        ctx->error("kinddeed id is empty");
        return ;
    }

    if( !is_founder()) {
        ctx->error(ctx->initiator() + " is not founder, have no authority to approve online kinddeed .");
        return ;
    }

    kinddeed ent;
    if (!_is_kinddeed_exist(id, ent))  {
        ctx->error("kinddeed " + id + " is not exist .");
        return ;
    }

    if (ent.online()==true){
        ctx->error("kinddeed " + ent.to_string() + " is already online .");
        return ;
    }

    if (ent.applied()==false)  {
        ctx->error("kinddeed " + ent.to_string() + " is not apply online.");
        return ;
    }

    if( !_delete_kinddeed_record(id) ) {
        ctx->error("delete kinddeed "+ ent.to_string() + " failure .");
        return;
    }

    ent.set_applied(false);
    ent.set_online(true);
    if (!get_kinddeed_table().put(ent)) {
        ctx->error("kinddeed table put "+ ent.to_string() + " error .");
        return;
    }

    ctx->ok("approve kinddeed "+ ent.to_string() + " online success .");
}

void Buddha::approve_offline_kinddeed() {
    const string& id = ctx->arg("id");
    if( id.empty()) {
        ctx->error("kinddeed id is empty");
        return ;
    }

    if( !is_founder()) {
        ctx->error(ctx->initiator() + " is not founder, have no authority to approve offline kinddeed .");
        return ;
    }

    kinddeed ent;
    if (!_is_kinddeed_exist(id, ent))  {
        ctx->error("kinddeed " + id + " is not exist .");
        return ;
    }

    if (ent.online()==false){
        ctx->error("kinddeed " + ent.to_string() + " is already offline .");
        return ;
    }

    if (ent.applied()==false)  {
        ctx->error("kinddeed " + ent.to_string() + " is not apply offline.");
        return ;
    }

    if( !_delete_kinddeed_record(id) ) {
        ctx->error("delete kinddeed "+ ent.to_string() + " failure .");
        return;
    }

    ent.set_applied(false);
    ent.set_online(false);
    if (!get_kinddeed_table().put(ent)) {
        ctx->error("kinddeed table put "+ ent.to_string() + " error .");
        return;
    }

    ctx->ok("approve kinddeed "+ ent.to_string() + " offline success .");
}


namespace 添加删除修改点评标签 {}
void Buddha::add_commentlabel() {
    const string& id = ctx->arg("id");
    if( id.empty()) {
        ctx->error("comment label id is empty");
        return ;
    }

    const string& desc = ctx->arg("desc");
    if( desc.empty()) {
        ctx->error("comment label desc is empty");
        return ;
    }

    if( !is_founder() ) {
        ctx->error(ctx->initiator() + " is not founder, have no authority to add comment label .");
        return ;
    }

    commentlabel ent;
    if( _is_commentlabel_exist(id,ent)) {
        ctx->error("commentlabel " + id + " is exist .");
        return ;
    }

    ent.set_id(stoll(id.c_str()));
    ent.set_desc(desc.c_str());
    if (!get_commentlabel_table().put(ent)) {
        ctx->error("commentlabel table put "+ ent.to_string() + " error .");
        return;
    }

    ctx->ok("add comment label " + ent.to_string() + " success .");
}

void Buddha::delete_commentlabel() {
    const string& id = ctx->arg("id");
    if( id.empty()) {
        ctx->error("comment label id is empty");
        return ;
    }

    if( !is_founder() ) {
        ctx->error(ctx->initiator() + " is not founder, have no authority to delete comment label .");
        return ;
    }

    commentlabel ent;
    if( !_is_commentlabel_exist(id,ent)) {
        ctx->error("kindeed type " + id + " is not exist .");
        return ;
    }

    if( !_delete_commentlabel_record(id) ) {
        ctx->error("delete comment label "+ ent.to_string() + " failure .");
        return;
    }

    ctx->ok("delete comment label " + ent.to_string() + " success .");
}

void Buddha::update_commentlabel() {
    const string& id = ctx->arg("id");
    if( id.empty()) {
        ctx->error("comment label id is empty");
        return ;
    }

    const string& desc = ctx->arg("desc");
    if( desc.empty()) {
        ctx->error("comment label desc is empty");
        return ;
    }

    if( !is_founder() ) {
        ctx->error(ctx->initiator() + " is not founder, have no authority to update comment label .");
        return ;
    }

    commentlabel ent;
    if( !_is_commentlabel_exist(id,ent)) {
        ctx->error("kindeed type " + id + " is not exist .");
        return ;
    }

    if( !_delete_commentlabel_record(id) ) {
        ctx->error("delete comment label "+ ent.to_string() + " failure .");
        return;
    }

    ent.set_id(stoll(id.c_str()));
    ent.set_desc(desc.c_str());
    if (!get_commentlabel_table().put(ent)) {
        ctx->error("commentlabel table put "+ ent.to_string() + " error .");
        return;
    }

    ctx->ok("update comment label " + ent.to_string() + " success .");
}

void Buddha::find_commentlabel() {
    const string& id = ctx->arg("id");
    if( id.empty()) {
        ctx->error("comment label id is empty");
        return ;
    }

    commentlabel ent;
    if (!_is_commentlabel_exist(id, ent))  {
        ctx->ok("comment label " + id + " is not exist .");
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
        if (it->get(&ent)) {
            i++;
            ret += ent.to_string();
        }
        else
            cout << __LINE__ << " get error : " << it->error(true) << endl;
    }
    ctx->ok("size=" + to_string(i) + " " + ret);
}


namespace 添加删除修改祈求善举前点评 {}
void Buddha::add_beforecomment() {
    const string& kdid = ctx->arg("kdid");
    if( kdid.empty()) {
        ctx->error("beforecomment kdid is empty");
        return ;
    }

    const string& satisfaction = ctx->arg("satisfaction");
    if( satisfaction.empty()) {
        ctx->error("beforecomment satisfaction is empty");
        return ;
    }

    const string& labels = ctx->arg("labels");
    xchain::json label_array = xchain::json::parse(labels);
    // mycout << label_array.dump().c_str() << endl ;
    if (!label_array.is_array()) {
        ctx->error("field 'labels' need to be array .");
        return;
    }
    
    if ( label_array.empty() || label_array.size() == 0) {
        ctx->error("filed 'labels' empty .");
        return;
    }

    if( !_is_all_types_exist_in_commentlabel(label_array)) {
        ctx->error("beforecomment type error .");
        return ;
    }

    const string& comment = ctx->arg("comment");
    if( comment.empty()) {
        ctx->error("beforecomment comment is empty");
        return ;
    }

    const string& timestamp = ctx->arg("timestamp");
    if( timestamp.empty()) {
        ctx->error("beforecomment timestamp is empty");
        return ;
    }

    const string& owner = ctx->initiator() ;

    beforecomment ent;
    if( _is_beforecomment_exist(owner,kdid,ent)) {
        ctx->error("beforecomment " + kdid + " is exist .");
        return ;
    }

    ent.set_owner(owner.c_str());
    ent.set_kdid(kdid.c_str());
    ent.set_satisfaction(stoll(satisfaction.c_str()));
    ent.set_labels(labels.c_str());    
    ent.set_comment(comment.c_str());
    ent.set_timestamp(timestamp.c_str());
    if (!get_beforecomment_table().put(ent)) {
        ctx->error("beforecomment table put "+ ent.to_string() + " error .");
        return;
    }

    ctx->ok("add beforecomment " + ent.to_string() + " success .");
}

void Buddha::delete_beforecomment() {
    const string& kdid = ctx->arg("kdid");
    if( kdid.empty()) {
        ctx->error("beforecomment kdid is empty");
        return ;
    }

    const string& owner = ctx->initiator();

    beforecomment ent;
    if( !_is_beforecomment_exist(owner,kdid,ent)) {
        ctx->error("kindeed type " + kdid + " is not exist .");
        return ;
    }

    if( !is_founder() &&
        ent.owner() != owner) {
        ctx->error(ctx->initiator() + " is not founder nor owner, have no authority to delete the comment .");
        return ;
    }

    if( !_delete_beforecomment_record(owner, kdid) ) {
        ctx->error("delete beforecomment "+ ent.to_string() + " failure .");
        return;
    }

    ctx->ok("delete beforecomment " + ent.to_string() + " success .");
}

void Buddha::update_beforecomment() {
    const string& kdid = ctx->arg("kdid");
    if( kdid.empty()) {
        ctx->error("beforecomment kdid is empty");
        return ;
    }

    const string& satisfaction = ctx->arg("satisfaction");
    if( satisfaction.empty()) {
        ctx->error("beforecomment satisfaction is empty");
        return ;
    }

    const string& labels = ctx->arg("labels");
    auto label_array = xchain::json::parse(labels);
    // mycout << label_array.dump().c_str() << endl ;
    if (!label_array.is_array()) {
        ctx->error("field 'labels' need to be array .");
        return;
    }
    
    if ( label_array.empty() || label_array.size() == 0) {
        ctx->error("filed 'labels' empty .");
        return;
    }

    if( !_is_all_types_exist_in_commentlabel(label_array)) {
        ctx->error("beforecomment type error .");
        return ;
    }

    const string& comment = ctx->arg("comment");
    if( comment.empty()) {
        ctx->error("beforecomment comment is empty");
        return ;
    }

    const string& timestamp = ctx->arg("timestamp");
    if( timestamp.empty()) {
        ctx->error("beforecomment timestamp is empty");
        return ;
    }

    const string& owner = ctx->initiator() ;

    beforecomment ent;
    if( !_is_beforecomment_exist(owner,kdid,ent)) {
        ctx->error("kindeed type " + kdid + " is not exist .");
        return ;
    }

    if( ent.owner() != owner) {
        ctx->error(ctx->initiator() + " is not owner, have no authority to update the comment .");
        return ;
    }

    if( !_delete_beforecomment_record(owner, kdid) ) {
        ctx->error("delete beforecomment "+ ent.to_string() + " failure .");
        return;
    }

    ent.set_owner(owner.c_str());
    ent.set_kdid(kdid.c_str());
    ent.set_satisfaction(stoll(satisfaction.c_str()));
    ent.set_labels(labels.c_str());    
    ent.set_comment(comment.c_str());
    ent.set_timestamp(timestamp.c_str());
    if (!get_beforecomment_table().put(ent)) {
        ctx->error("beforecomment table put "+ ent.to_string() + " error .");
        return;
    }

    ctx->ok("update beforecomment " + ent.to_string() + " success .");
}

void Buddha::find_beforecomment() {
    const string& kdid = ctx->arg("kdid");
    if( kdid.empty()) {
        ctx->error("beforecomment kdid is empty");
        return ;
    }

    kinddeed kd;
    if (!_is_kinddeed_exist(kdid, kd))  {
        ctx->error("kinddeed " + kdid + " is not exist .");
        return ;
    }

    const string& owner = ctx->arg("owner");

    if( !owner.empty()) {
        beforecomment ent;
        if (!_is_beforecomment_exist(owner,kdid, ent))  {
            ctx->ok("beforecomment " + kdid + " is not exist .");
            return ;
        }

        if( is_founder() ||                      //基金会成员
            owner == ctx->initiator() ||        //点评的所有者
            kd.owner() == ctx->initiator() ) { //善举所有者
            ctx->ok(ent.to_string());
            return ;
        }

        ctx->error(ctx->initiator() + " is not founder nor owner, have no authority to delete the comment .");
        return ;

    }

    //owner字段为空的情况
    //此时如果是基金会成员和善举所有者调用，报错
    if( is_founder() ||                          //基金会成员
        kd.owner() == ctx->initiator() ) {      //善举所有者
        ctx->error("beforecomment owner should be empty .");
        return ;
    }

    //点评所有者调用，直接查询
    beforecomment ent;
    if (!_is_beforecomment_exist(ctx->initiator(),kdid, ent))  {
        ctx->ok("beforecomment " + kdid + " is not exist .");
        return ;
    }
    ctx->ok(ent.to_string());
}

void Buddha::list_beforecomment() {
    const string& kdid = ctx->arg("kdid");
    if( kdid.empty()) {
        ctx->error("beforecomment kdid is empty");
        return ;
    }

    kinddeed kd;
    if (!_is_kinddeed_exist(kdid, kd))  {
        ctx->error("kinddeed " + kdid + " is not exist .");
        return ;
    }

    auto it = get_beforecomment_table().scan({{"kdid",kdid}});
    int i = 0;
    string ret;
    while(it->next()) {
        beforecomment ent;
        if (it->get(&ent)) {
            i++;
            ret += ent.to_string();
        }
        else
            cout << __LINE__ << " get error : " << it->error(true) << endl;
    }
    ctx->ok("size=" + to_string(i) + " " + ret);
}


namespace 会员祈求善举{}

void Buddha::pray_kinddeed() {

    cout << endl ;
    
    const string& orderid = ctx->arg("id");
    if( orderid.empty()) {
        ctx->error("orderid is empty");
        return ;
    }

    const string& kdid = ctx->arg("kinddeed");
    if( kdid.empty()) {
        ctx->error("kdid is empty");
        return ;
    }

    const string& specid = ctx->arg("spec");
    if( specid.empty()) {
        ctx->error("specid is empty");
        return ;
    }

    const string& count = ctx->arg("count");
    if( count.empty()) {
        ctx->error("count is empty");
        return ;
    }

    const string& amount = ctx->transfer_amount();
    if( amount.empty()) {
        ctx->error("amount is empty");
        return ;
    }

    const string& timestamp = ctx->arg("timestamp");
    if( timestamp.empty()) {
        ctx->error("timestamp is empty");
        return ;
    }

    //判断订单是否存在
    order od;
    if (_is_order_exist(orderid,od))  {
        ctx->error("order " + orderid + " is exist .");
        return ;
    }

    //判断善举是否存在
    kinddeed kd;
    if (!_is_kinddeed_exist(kdid, kd))  {
        ctx->error("kinddeed " + kdid + " is not exist .");
        return ;
    }

    //判断善举是否已经上架
    if (!_is_kinddeed_online(kdid)) {
        ctx->error("kinddeed " + kdid + " is not online .");
        return ;
    }

    //判断善举规格是否存在
    kinddeedspec spec;
    if (!_is_kinddeedspec_exist(kdid, specid, spec))  {
        ctx->error("kinddeedspec " + kdid + "," + specid + " is not exist .");
        return ;
    }

    //计算总价格，要求转账过来的总价格跟订单计算出的总价格要求必须一直
    int64_t calced_amount = spec.price() * stoll(count);
    if( calced_amount != stoll(amount)){
        ctx->error("delive amount " + amount
                   + ", real amount=" + to_string(calced_amount));
        return;
    }
    
    od.set_id(orderid.c_str());
    od.set_owner(ctx->initiator());
    od.set_kdid(kdid);
    od.set_specid(stoll(specid));
    od.set_count(stoll(count));
    od.set_amount(calced_amount);
    od.set_timestamp(timestamp.c_str());
    if (!get_order_table().put(od)) {
        ctx->error("order table put "+ od.to_string() + " error .");
        return;
    }
    
    ctx->ok("pray kinddeed " + to_string(calced_amount) + " success .");
}

void Buddha::find_pray_kinddeed() {
    mycout << endl ;

    const string& id = ctx->arg("id");
    if( id.empty()) {
        ctx->error("order id is empty");
        return ;
    }

    mycout << endl ;

    order ent;       
    if (!_is_order_exist(id, ent)) {
        ctx->error("order " + id + " is not exist .");
        return ;
    }

    if( !is_deployer() &&
        !is_founder() &&
        !is_temple() &&
        !is_master() &&
        ent.owner() != ctx->initiator()) {
        ctx->error(ctx->initiator() + " have no authority to find pray kinddeed .");
        return ;
    }

    mycout << ent.to_string() << endl ;
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
            if (it->get(&ent)) {
                i++;
                ret += ent.to_string();
            }
            else
                cout << __LINE__ << " get error : " << it->error(true) << endl;
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
            if (it->get(&ent)) {
                i++;
                ret += ent.to_string();
            }
            else
                cout << __LINE__ << " get error : " << it->error(true) << endl;
        }
        ctx->ok("size=" + to_string(i) + " " + ret);
        return ;
    }

    ctx->error(ctx->initiator() + " have no authority to list order .");
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
        ctx->error("kinddeed proof orderid is empty");
        return ;
    }

    const string& proof = ctx->arg("proof");
    if( proof.empty()) {
        ctx->error("kinddeed proof hash is empty");
        return ;
    }

    const string& timestamp = ctx->arg("timestamp");
    if( timestamp.empty()) {
        ctx->error("kinddeed proof timestamp is empty");
        return ;
    }

    kinddeedproof ent;
    if (_is_kinddeedproof_exist_by_order(orderid, ent))  {
        ctx->error("kinddeed proof " + orderid + " is exist .");
        return ;
    }

    order od;
    if (!_is_order_exist(orderid, od)) {
        ctx->error("order and suborder lost, kinddeed proof " + orderid + " be delete .");
        return ;
    }
    
    if( od.kdowner() != ctx->initiator() ) {
        ctx->error(ctx->initiator() + " is not the right kinddeed owner, it should be " + od.kdowner());
        return ;
    }

    ent.set_orderid(orderid.c_str());
    ent.set_owner(ctx->initiator());
    ent.set_proof(proof.c_str());
    ent.set_timestamp(timestamp.c_str());
    ent.set_approved(false);
    if (!get_kinddeedproof_table().put(ent)) {
        ctx->error("kinddeed proof table put "+ ent.to_string() + " error .");
        return;
    }

    ctx->ok("apply kinddeed "+ ent.to_string() + " proof over, please wait for approve .");
}

void Buddha::approve_kinddeedproof() {
    const string& orderid = ctx->arg("orderid");
    if( orderid.empty()) {
        ctx->error("kinddeed proof orderid is empty");
        return ;
    }

    if( !is_founder()) {
        ctx->error(ctx->initiator() + " is not founder, have no authority to approve kinddeed proof .");
        return ;
    }

    kinddeedproof ent;
    if (!_is_kinddeedproof_exist_by_order(orderid, ent))  {
        ctx->error("kinddeed proof " + orderid + " is not exist .");
        return ;
    }

    order od;
    if (!_is_order_exist(orderid, od)) {
        _delete_kinddeedproof_record(orderid);
        ctx->error("order and suborder lost, kinddeed proof " + orderid + " be delete .");
        return ;
    }

    if (ent.approved())  {
        ctx->ok("kinddeed proof " + orderid + " has approved yet .");
        return ;
    }

    kinddeed kd;
    if( !_is_kinddeed_exist(od.kdid(), kd)) {
        ctx->error("kinddeed " + od.kdid() + " is not exist .");
        return ;
    }

    if( ent.owner() != od.kdowner() &&
        ent.owner() != kd.owner()) {
        ctx->error(ent.owner() +","+ od.kdowner() + "," + kd.owner() + " error .");
        return ;
    }

    if( !_delete_kinddeedproof_record(orderid) ) {
        ctx->error("delete kinddeed proof "+ ent.to_string() + " failure .");
        return;
    }

    ent.set_approved(true);
    if (!get_kinddeedproof_table().put(ent)) {
        ctx->error("kinddeed proof table put "+ ent.to_string() + " error .");
        return;
    }

    if( !_transfer(ent.owner(), to_string(od.amount()))) {
        ctx->error("transfer to " + ent.owner() + " " +  to_string(od.amount()) + " failure .");
        return ;
    }

    ctx->ok("approve kinddeed "+ ent.to_string() + " proof success .");
}

void Buddha::refuse_kinddeedproof() {
    const string& orderid = ctx->arg("orderid");
    if( orderid.empty()) {
        ctx->error("kinddeed proof orderid is empty");
        return ;
    }

    if( !is_founder()) {
        ctx->error(ctx->initiator() + " is not founder, have no authority to approve kinddeed proof .");
        return ;
    }

    kinddeedproof ent;
    if (!_is_kinddeedproof_exist_by_order(orderid, ent))  {
        ctx->error("kinddeed proof " + orderid + " is not exist .");
        return ;
    }

    order od;
    if (!_is_order_exist(orderid, od)) {
        _delete_kinddeedproof_record(orderid);
        ctx->error("order lost, kinddeed proof " + orderid + " be delete .");
        return ;
    }

    if (ent.approved())  {
        ctx->ok("kinddeed proof " + orderid + " has approved yet .");
        return ;
    }

    if( !_delete_kinddeedproof_record(orderid) ) {
        ctx->error("delete kinddeed proof "+ ent.to_string() + " failure .");
        return;
    }

    ctx->ok("refuse kinddeed "+ ent.to_string() + " proof success .");
}

void Buddha::find_kinddeedproof() {
    const string& orderid = ctx->arg("orderid");
    const string& proof = ctx->arg("proof");

    if( orderid.empty() &&
        proof.empty()) {
        ctx->error("kinddeed proof hash and orderid is empty .");
        return ;
    }

    if( !orderid.empty() &&
        !proof.empty()) {
        ctx->error("kinddeed proof hash and orderid should not all exist .");
        return ;
    }

    kinddeedproof ent;

    if( !orderid.empty()) {
        order od;        
        if (!_is_order_exist(orderid, od))  {
            ctx->error("order " + orderid + " is not exist .");
            return ;
        }

        if (!_is_kinddeedproof_exist_by_order(orderid, ent))  {
            ctx->error("kinddeed proof " + orderid + " is not exist .");
            return ;
        }
    }

    if( !proof.empty()) 
        if (!_is_kinddeedproof_exist_by_proof(proof, ent))  {
            ctx->error("kinddeed proof " + proof + " is not exist .");
            return ;
        }

    if( is_deployer() ||
        is_founder()) {
        ctx->ok(ent.to_string());
        return ;
    }
    
    if( !is_temple() &&
        !is_master() ) {
        ctx->error(ctx->initiator() + " have no authority to find kinddeed proof .");
        return ;
    }

    if( ent.owner() != ctx->initiator() ) {
        ctx->error(ctx->initiator() + " is not the right kinddeed proof owner, it should be " + ent.owner());
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
            if (it->get(&ent)) {
                i++;
                ret += ent.to_string();
            }
            else
                cout << __LINE__ << " get error : " << it->error(true) << endl;
        }
        ctx->ok("size=" + to_string(i) + " " + ret);
    }

    if( is_temple() || 
        is_master()) {
        auto it = get_kinddeedproof_table().scan({{"owner",ctx->initiator()},{"orderid",ctx->arg("orderid")}});
        int i = 0;
        string ret;
        while(it->next()) {
            kinddeedproof ent;
            if (it->get(&ent)) {
                i++;
                ret += ent.to_string();
            }
            else
                cout << __LINE__ << " get error : " << it->error(true) << endl;
        }
        ctx->ok("size=" + to_string(i) + " " + ret);
        return;
    }

    ctx->error(ctx->initiator() + " have no authority to list kinddeed proof .");
    return ;
}

namespace 添加删除修改祈求善举后点评 {}
void Buddha::add_aftercomment() {
    const string& orderid = ctx->arg("orderid");
    if( orderid.empty()) {
        ctx->error("aftercomment orderid is empty");
        return ;
    }

    const string& comment = ctx->arg("comment");
    if( comment.empty()) {
        ctx->error("aftercomment comment is empty");
        return ;
    }

    const string& timestamp = ctx->arg("timestamp");
    if( timestamp.empty()) {
        ctx->error("aftercomment timestamp is empty");
        return ;
    }

    const string& owner = ctx->initiator() ;

    aftercomment ent;
    if( _is_aftercomment_exist(orderid,ent)) {
        ctx->error("aftercomment " + orderid + " is exist .");
        return ;
    }

    order od;        
    if (!_is_order_exist(orderid, od))  {
        ctx->error("order " + orderid + " is not exist .");
        return ;
    }

    if( od.owner() != owner ) {
        ctx->error("order " + orderid + " is not belong to you .");
        return ;
    }

    ent.set_orderid(orderid.c_str());
    ent.set_owner(owner.c_str());
    ent.set_comment(comment.c_str());
    ent.set_timestamp(timestamp.c_str());
    if (!get_aftercomment_table().put(ent)) {
        ctx->error("aftercomment table put "+ ent.to_string() + " error .");
        return;
    }

    ctx->ok("add aftercomment " + ent.to_string() + " success .");
}

void Buddha::delete_aftercomment() {
    const string& orderid = ctx->arg("orderid");
    if( orderid.empty()) {
        ctx->error("aftercomment orderid is empty");
        return ;
    }

    const string& owner = ctx->initiator();

    aftercomment ent;
    if( !_is_aftercomment_exist(orderid,ent)) {
        ctx->error("aftercomment " + orderid + " is not exist .");
        return ;
    }

    order od;        
    if (!_is_order_exist(orderid, od))  {
        ctx->error("order " + orderid + " is not exist .");
        return ;
    }

    if( !is_founder() &&
        ent.owner() != owner) {
        ctx->error(ctx->initiator() + " is not founder nor owner, have no authority to delete the comment .");
        return ;
    }

    if( !_delete_aftercomment_record(orderid) ) {
        ctx->error("delete aftercomment "+ ent.to_string() + " failure .");
        return;
    }

    ctx->ok("delete aftercomment " + ent.to_string() + " success .");
}

void Buddha::update_aftercomment() {
    const string& orderid = ctx->arg("orderid");
    if( orderid.empty()) {
        ctx->error("aftercomment orderid is empty");
        return ;
    }

    const string& comment = ctx->arg("comment");
    if( comment.empty()) {
        ctx->error("aftercomment comment is empty");
        return ;
    }

    const string& timestamp = ctx->arg("timestamp");
    if( timestamp.empty()) {
        ctx->error("aftercomment timestamp is empty");
        return ;
    }

    const string& owner = ctx->initiator() ;

    aftercomment ent;
    if( !_is_aftercomment_exist(orderid,ent)) {
        ctx->error("kindeed type " + orderid + " is not exist .");
        return ;
    }

    order od;        
    if (!_is_order_exist(orderid, od))  {
        ctx->error("order " + orderid + " is not exist .");
        return ;
    }

    if( ent.owner() != owner) {
        ctx->error(ctx->initiator() + " is not owner, have no authority to update the comment .");
        return ;
    }

    if( !_delete_aftercomment_record(orderid) ) {
        ctx->error("delete aftercomment "+ ent.to_string() + " failure .");
        return;
    }

    ent.set_orderid(orderid.c_str());
    ent.set_owner(owner.c_str());
    ent.set_comment(comment.c_str());
    ent.set_timestamp(timestamp.c_str());
    if (!get_aftercomment_table().put(ent)) {
        ctx->error("aftercomment table put "+ ent.to_string() + " error .");
        return;
    }

    ctx->ok("update aftercomment " + ent.to_string() + " success .");
}

void Buddha::find_aftercomment() {
    const string& orderid = ctx->arg("orderid");
    if( orderid.empty()) {
        ctx->error("aftercomment orderid is empty");
        return ;
    }

    aftercomment ent;
    if (!_is_aftercomment_exist(orderid, ent))  {
        ctx->ok("aftercomment " + orderid + " is not exist .");
        return ;
    }

    order od;        
    if (!_is_order_exist(orderid, od))  {
        ctx->error("order " + orderid + " is not exist .");
        return ;
    }

    if( !is_founder() &&
        ent.owner() != ctx->initiator() &&
        od.kdowner() != ctx->initiator()) {
        ctx->error(ctx->initiator() + " is not owner, have no authority to update the comment .");
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
            if (it->get(&ent)) {
                i++;
                ret += ent.to_string();
            }
            else
                cout << __LINE__ << " get error : " << it->error(true) << endl;
        }
        ctx->ok("size=" + to_string(i) + " " + ret);
        return;
    }
    
    if( orderid.empty()) {
        ctx->error("aftercomment orderid is empty");
        return ;
    }

    order od;        
    if (!_is_order_exist(orderid, od))  {
        ctx->error("order " + orderid + " is not exist .");
        return ;
    }

    auto it = get_aftercomment_table().scan({{"orderid",orderid}});
    int i = 0;
    string ret;
    while(it->next()) {
        aftercomment ent;
        if (it->get(&ent)) {
            i++;
            ret += ent.to_string();
        }
        else
            cout << __LINE__ << " get error : " << it->error(true) << endl;
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

DEFINE_METHOD(Buddha, add_kinddeed)             { self.add_kinddeed();              }
DEFINE_METHOD(Buddha, update_kinddeed)          { self.update_kinddeed();           }
DEFINE_METHOD(Buddha, delete_kinddeed)          { self.delete_kinddeed();           }
DEFINE_METHOD(Buddha, find_kinddeed)            { self.find_kinddeed();             }
DEFINE_METHOD(Buddha, list_kinddeed)            { self.list_kinddeed();             }

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

