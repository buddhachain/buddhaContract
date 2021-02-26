#include <inttypes.h>
#include "xchain/json/json.h"
#include "xchain/xchain.h"
#include "xchain/account.h"
#include "xchain/contract.pb.h"
#include "xchain/syscall.h"
#include "buddha.pb.h"
#include "founder.h"
#include "master.h"
#include "member.h"
#include "kinddeed.h"
#include "comment.h"
#include "order.h"
#include "kinddeedproof.h"
#include "buddha.h"

#include <iostream>
using namespace std;

#define mycout cout << __func__ << "[" << __LINE__ << "] " 

namespace pb = xchain::contract::sdk;

Buddha::Buddha() :
    _founder_table(         context(), "founder"                ),
    _master_table(          context(), "master"                 ),
    _member_table(          context(), "member"                 ),
    _kinddeed_table(        context(), "kinddeed"               ),
    _kinddeed_detail_table( context(), "kinddeed_detail_table"  ),
    _kinddeed_spec_table(   context(), "kinddeed_spec_table"    ),
    _comment_label_table(   context(), "comment_label_table"    ),
    _before_comment_table(  context(), "before_comment_table"   ),
    _order_table(           context(), "order"                  ),
    _kinddeed_proof_table(  context(), "kinddeed_proof"         ),
    _after_comment_table(   context(), "after_comment_table"    ),

    ctx(context())
{
}



decltype(_founder_table)& Buddha::get_founder_table() {
    return _founder_table;
}

decltype(_master_table)& Buddha::get_master_table() {
    return _master_table;
}

decltype(_member_table)& Buddha::get_member_table() {
    return _member_table;
}

decltype(_kinddeed_table)& Buddha::get_kinddeed_table() {
    return _kinddeed_table;
}

decltype(_kinddeed_detail_table)& Buddha::get_kinddeed_detail_table() {
    return _kinddeed_detail_table;
}

decltype(_kinddeed_spec_table)& Buddha::get_kinddeed_spec_table() {
    return _kinddeed_spec_table;
}

decltype(_comment_label_table)& Buddha::get_comment_label_table() {
    return _comment_label_table;
}

decltype(_before_comment_table)& Buddha::get_before_comment_table() {
    return _before_comment_table;
}

decltype(_order_table)& Buddha::get_order_table() {
    return _order_table;
}

decltype(_kinddeed_proof_table)& Buddha::get_kinddeed_proof_table() {
    return _kinddeed_proof_table;
}

decltype(_after_comment_table)& Buddha::get_after_comment_table() {
    return _after_comment_table;
}







bool Buddha::_is_founder_exist_by_id(const std::string& id,founder& ent) {
    if (!get_founder_table().find({{"id", id}}, &ent))
        return false;

    return true;
}

bool Buddha::_is_master_exist_by_id(const std::string& id,master& ent){
    if (!get_master_table().find({{"id", id}}, &ent))
        return false;

    return true;
}

bool Buddha::_is_master_exist_unit(const std::string& unit,master& ent){
    if (!get_master_table().find({{"unit", unit}}, &ent))
        return false;

    return true;
}

bool Buddha::_is_master_exist_creditcode(const std::string& creditcode,master& ent){
    if (!get_master_table().find({{"creditcode", creditcode}}, &ent))
        return false;

    return true;
}

bool Buddha::_is_master_exist_by_address(const std::string& address,master& ent){
    if (!get_master_table().find({{"address", address}}, &ent))
        return false;

    return true;
}

bool Buddha::_is_master_exist_by_deedplaceproof(const std::string& deedplaceproof,master& ent){
    if (!get_master_table().find({{"deedplaceproof", deedplaceproof}}, &ent))
        return false;

    return true;
}

bool Buddha::_is_member_exist_by_id(const std::string& id,master& ent){
    if (!get_member_table().find({{"id", id}}, &ent))
        return false;

    return true;
}

bool Buddha::_is_kinddeed_exist_by_id(const std::string& id,kinddeed& ent) {
    if (!get_kinddeed_table().find({{"id", id}}, &ent))
        return false;

    return true;
}

bool Buddha::_is_kinddeed_detail_exist_by_kdid(const std::string& kdid,kinddeeddetail& ent) {
    if (!get_kinddeed_detail_table().find({{"kdid", kdid}}, &ent))
        return false;

    return true;
}

bool Buddha::_is_kinddeed_spec_exist(const std::string& id,kinddeedspec& ent) {
    if (!get_kinddeed_spec_table().find({{"id", id}}, &ent))
        return false;

    return true;
}

bool Buddha::_is_comment_label_exist_by_id(const std::string& id,commentlabel& ent) {
    if (!get_comment_label_table().find({{"id", id}}, &ent))
        return false;

    return true;
}

bool Buddha::_is_before_comment_exist_by_id(const std::string& id,beforecomment& ent) {
    if (!get_before_comment_table().find({{"id", id}}, &ent))
        return false;

    return true;
}

bool Buddha::_is_order_exist_by_id(const std::string& id,order& ent) {
    if (!get_order_table().find({{"id", id}}, &ent))
        return false;

    return true;
}

bool Buddha::_is_kinddeed_proof_exist_by_orderid(const std::string& orderid,kinddeedproof& ent) {
    if (!get_kinddeed_proof_table().find({{"orderid", orderid}}, &ent))
        return false;

    return true;
}

bool Buddha::_is_after_comment_exist_by_orderid(const std::string& id,aftercomment& ent) {
    if (!get_after_comment_table().find({{"id", id}}, &ent))
        return false;

    return true;
}


void Buddha::_get_kinddeed(const std::string& id,kinddeed& ent) {
    get_kinddeed_table().find({{"id", id}}, &ent);
}

bool Buddha::_is_kinddeed_online(const std::string& id){
    kinddeed ent;
    if (!get_kinddeed_table().find({{"id", id}}, &ent)) {
        mycout << "kinddeed " << id << " is not exist ." << endl;
        return false;
    }

    if(ent.applied() == true) {
        mycout << "kinddeed " << id << " is apply status change ." << endl;
        return false;
    }

    if(ent.online() != true ) {
        mycout << "kinddeed " << id << " is not online ." << endl;
        return false;
    }

    return true;

}



bool Buddha::_is_deployer(const std::string& id) {
    std::string deployer;
    if (!ctx->get_object("deployer", &deployer)) 
        return false;

    if (deployer != name )
        return false;

    return true ;
}

bool Buddha::_is_founder(const std::string& id) {
    founder ent;
    if (!is_founder_exist(id, ent))
        return false;
    
    if( ent.approved() != true ) 
        return false;

    return true;
}

bool Buddha::_is_master(const std::string& id) {
    master ent;
    if (!_is_master_exist(id, ent))
        return false;
    
    if( ent.approved() != true ) 
        return false;

    return true ;
}

bool Buddha::_is_member(const std::string& id) {
    member ent;
    if (!_is_member_exist_by_id(id, ent))
        return false;

    return true ;
}


bool Buddha::_is_user(const std::string& id) {
    if(_is_deployer(id)) 
        return false;

    if(_is_founder(id)) 
        return false;

    if(_is_master(id)) 
        return false;

    if(_is_member(id)) 
        return false;

    return true ;
}


bool Buddha::_delete_founder_record(const std::string& id) {
    founder ent;
    if (!_is_founder_exist_by_id(id, ent)){
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

bool Buddha::_delete_master_record(const std::string& id) {
    master ent;
    if (!_is_master_exist_by_id(id, ent)){
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

bool Buddha::_delete_member_record(const std::string& id) {
    member ent;
    if (!_is_member_exist_by_id(id, ent)){
        mycout << "member " << id << " is not exist ." << endl ;
        return false;
    }

    if( !get_member_table().del(ent) ) {
        mycout << "delete member " << ent.to_string() << " failure ." << endl ;
        return false;
    }

    mycout << "delete member " << ent.to_string() << " success ." << endl ;
    return true;
}

bool Buddha::_delete_kinddeed_record(const std::string& id) {
    kinddeed ent;
    if (!_is_kinddeed_exist_by_id(id, ent)){
        mycout << "kinddeed " << id << " is not exist ." << endl ;
        return false;
    }

    if( !get_kinddeed_table().del(ent) ) {
        mycout << "delete kinddeed " << ent.to_string() << " failure ." << endl ;
        return false;
    }

    if( !_delete_kinddeed_detail_record(id) ) {
        mycout << "delete kinddeed detail " << id << " failure ." << endl ;
        return false;
    }

    if( !_delete_kinddeed_spec_record(id) ) {
        mycout << "delete kinddeed spec " << id << " failure ." << endl ;
        return false;
    }

    mycout << "delete kinddeed " << ent.to_string() << " success ." << endl ;
    return true;
}

bool Buddha::_delete_kinddeed_detail_record(const std::string& id) {
    while(true) {
        kinddeeddetail ent;
        if (!_is_kinddeed_detail_exist_by_id(id, ent))
            break;

        if( !get_kinddeed_detail_table().del(ent) ) {
            mycout << "delete kinddeed detail " << ent.to_string() << " failure ." << endl ;
            return false;
        }
    }

    mycout << "delete kinddeed detail" << ent.to_string() << " success ." << endl ;
    return true;
}

bool Buddha::_delete_kinddeed_spec_record(const std::string& id) {
    while(true) {
        kinddeedspec ent;
        if (!_is_kinddeed_spec_exist_by_id(id, ent))
            break;

        if( !get_kinddeed_spec_table().del(ent) ) {
            mycout << "delete kinddeed spec " << ent.to_string() << " failure ." << endl ;
            return false;
        }
    }

    mycout << "delete kinddeed spec" << ent.to_string() << " success ." << endl ;
    return true;
}

bool Buddha::_delete_comment_label_record(const std::string& id) {
    commentlabel ent;
    if (!_is_comment_label_exist_by_id(id, ent)){
        mycout << "comment label " << id << " is not exist ." << endl ;
        return false;
    }

    if( !get_comment_label_table().del(ent) ) {
        mycout << "delete comment label " << ent.to_string() << " failure ." << endl ;
        return false;
    }

    mycout << "delete comment label " << ent.to_string() << " success ." << endl ;
    return true;
}

bool Buddha::_delete_before_comment_record(const std::string& id) {
    beforecomment ent;
    if (!_is_before_comment_exist_by_id(id, ent)){
        mycout << "comment label " << id << " is not exist ." << endl ;
        return false;
    }

    if( !get_before_comment_table().del(ent) ) {
        mycout << "delete comment label " << ent.to_string() << " failure ." << endl ;
        return false;
    }

    mycout << "delete comment label " << ent.to_string() << " success ." << endl ;
    return true;
}


bool Buddha::_delete_order_record(const std::string& id) {
    order ent;
    if(!_is_order_exist_by_id(id, ent)){
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

bool Buddha::_delete_kinddeed_proof_record(const std::string& orderid) {
    kinddeedproof ent;
    if (!_is_kinddeed_proof_exist_by_orderid(orderid, ent)){
        mycout << "kinddeed proof " << orderid << " is not exist ." << endl ;
        return false;
    }

    if( !get_kinddeed_proof_table().del(ent) ) {
        mycout << "delete kinddeed proof " << ent.to_string() << " failure ." << endl ;
        return false;
    }

    mycout << "delete kinddeed proof " << ent.to_string() << " success ." << endl ;
    return true;
}

bool Buddha::_delete_after_comment_record(const std::string& orderid) {
    aftercomment ent;
    if (!_is_after_comment_exist_by_orderid(orderid, ent)){
        mycout << "after comment " << orderid << " is not exist ." << endl ;
        return false;
    }

    if( !get_after_comment_table().del(ent) ) {
        mycout << "delete after comment " << ent.to_string() << " failure ." << endl ;
        return false;
    }

    mycout << "delete after comment " << ent.to_string() << " success ." << endl ;
    return true;
}

bool Buddha::_transfer(const std::string& id,
                    const std::string& amount){
    //将抵押退还
    xchain::Account account = xchain::Account(name);
    if(!account.transfer(amount)) 
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
    std::string deployer;
    if (!ctx->get_object("deployer", &deployer)) {
        ctx->ok("deployer unknown");
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
    const std::string& desc = ctx->arg("desc");
    if(desc.empty()) {
        ctx->error("desc is empty");
        return ;
    }
    
    if(!is_user() && !is_master() ) {
        ctx->error(ctx->initiator() + " is not user and master, has no authority to apply tobe founder .");
        return ;
    }

    const std::string& guaranty = ctx->transfer_amount();
    if(guaranty.empty()) {
        ctx->error("guaranty is empty");
        return ;
    }

    if(is_founder()) {
        ctx->error(ctx->initiator() + " is already founder .");
        return ;
    }

    if( !delete_founder_record(ctx->initiator()) ) {
        ctx->error("delete founder "+ ctx->initiator() + " failure .");
        return;
    }

    founder ent;
    ent.set_name(ctx->initiator().c_str());
    ent.set_desc(desc.c_str());
    ent.set_guaranty(ent.guaranty() + std::stoll(guaranty));
    ent.set_approved(false);
    if (!get_founder_table().put(ent)) {
        ctx->error("founder table put "+ ent.to_string() + " error .");
        return;
    }

    ctx->ok(ent.to_string() + " apply tobe founder over, please wait for approve .");
}

void Buddha::approve_founder() {
    const std::string& id = ctx->arg("name");
    if(name.empty()) {
        ctx->error("founder name is empty");
        return ;
    }

    if(!is_deployer()) {
        ctx->error(ctx->initiator() + " is not deployer, has no authority to approve founder .");
        return ;
    }

    founder ent;
    if(!is_founder_exist(name,ent)) {
        ctx->error("founder " + name + " is not exist .");
        return ;
    }

    if(is_founder(id)) {
        ctx->error(ent.to_string() + " is already founder .");
        return ;
    }

    if( !delete_founder_record(name) ) {
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
    const std::string& id = ctx->arg("name");
    if(name.empty()) {
        ctx->error("founder name is empty .");
        return ;
    }

    if(!is_deployer()) {
        ctx->error(ctx->initiator() + " is not deployer, has no authority recusal founder .");
        return ;
    }

    founder ent;
    if(!is_founder_exist(name,ent)) {
        ctx->error("founder " + name + " is not exist .");
        return ;
    }

    //将抵押退还
    std::string guaranty = std::to_string(ent.guaranty());
    if(!transfer(name, guaranty)) {
        ctx->error("refund transfer " + guaranty + " to " + name + " failure .");
        return ;
    }

    if( !delete_founder_record(name) ) {
        ctx->error("delete founder "+ ent.to_string() + " failure .");
        return;
    }

    ctx->ok("recusal founder "+ name + " success , guaranty " + guaranty + " has refund, please check balance.");
}

bool Buddha::is_founder() {
    bool ret = _is_founder(ctx->initiator());
    if (ret) {
        ctx->ok(ctx->initiator() + " is founder .") ;
        return true;
    }
    
    ctx->ok(ctx->initiator() + " is not founder .") ;
    return false;
}

void Buddha::list_founder() {
    if(!is_deployer()&&!is_founder()) {
        ctx->error(ctx->initiator() + " is not deployer nor founder, has no authority to list founder .");
        return ;
    }

    auto it = get_founder_table().scan({{"name",""}});
    int i = 0;
    std::string ret;
    while(it->next()) {
        founder ent;
        if (it->get(&ent)) {
            i++;
            ret += ent.to_string();
        }
        else
            std::cout << __LINE__ << " get error : " << it->error(true) << std::endl;
    }
    ctx->ok("size=" + std::to_string(i) + " " + ret);
}

namespace 申请成为法师或寺院{}

void Buddha::apply_master(){
    if(!is_user()) {
        ctx->error(ctx->initiator() + " is not common user, has no authority to apply tobe master .");
        return ;
    }

    if(is_master()) {
        ctx->error(ctx->initiator() + " is already master .");
        return ;
    }
    
    const std::string& desc = ctx->arg("desc");
    if(desc.empty()) {
        ctx->error("desc is empty");
        return ;
    }

    master ent;
    ent.set_name(ctx->initiator().c_str());
    ent.set_desc(desc.c_str());
    ent.set_approved(false);
    if (!get_master_table().put(ent)) {
        ctx->error("master table put "+ ent.to_string() + " error .");
        return;
    }

    ctx->ok(ent.to_string() + " apply tobe master over, please wait for approve .");
}

void Buddha::approve_master() {
    const std::string& id = ctx->arg("name");
    if(name.empty()) {
        ctx->error("master name is empty");
        return ;
    }

    if(!is_founder()) {
        ctx->error(ctx->initiator() + " is not founder, has no authority to approve master .");
        return ;
    }

    master ent;
    if(!is_master_exist(name,ent)) {
        ctx->error("master " + name + " is not exist .");
        return ;
    }

    if(is_master(id)) {
        ctx->error(ent.to_string() + " is already master .");
        return ;
    }

    if( !delete_master_record(name) ) {
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
    const std::string& id = ctx->arg("name");
    if(name.empty()) {
        ctx->error("master name is empty");
        return ;
    }
    
    if(!is_founder()) {
        ctx->error(ctx->initiator() + " is not founder, has no authority to recusal master .");
        return ;
    }

    master ent;
    if(!is_master_exist(name,ent)) {
        ctx->error("master " + name + " is not exist .");
        return ;
    }

    if( !delete_master_record(name) ) {
        ctx->error("delete master "+ ent.to_string() + " failure .");
        return;
    }

    ctx->ok("recusal master "+ ent.to_string() + " success .");
}

bool Buddha::is_master() {
    bool ret = _is_master(ctx->initiator());
    if (ret) {
        ctx->ok(ctx->initiator() + " is master .") ;
        return true;
    }
    
    ctx->ok(ctx->initiator() + " is not master .") ;
    return false;
}

void Buddha::list_master() {
    if(!is_deployer()&&!is_founder()) {
        ctx->error(ctx->initiator() + " is not deployer nor founder, has no authority to list master .");
        return ;
    }

    auto it = get_master_table().scan({{"name",""}});
    int i = 0;
    std::string ret;
    while(it->next()) {
        master ent;
        if (it->get(&ent)) {
            i++;
            ret += ent.to_string();
        }
        else
            std::cout << __LINE__ << " get error : " << it->error(true) << std::endl;
    }
    ctx->ok("size=" + std::to_string(i) + " " + ret);
}

namespace 添加删除修改善举{}

void Buddha::add_kinddeed() {
    if(!is_master() && !is_founder()) {
        ctx->error(ctx->initiator() + " is not founder and master, has no authority to add kinddeed .");
        return ;
    }

    const std::string& id = ctx->arg("id");
    const std::string& id = ctx->arg("name");
    const std::string& desc = ctx->arg("desc");
    const std::string& price = ctx->arg("price");
    const std::string& count = ctx->arg("count");
    const std::string& lasttime = ctx->arg("lasttime");
    if(id.empty()) {
        ctx->error("kinddeed id is empty");
        return ;
    }

    if(name.empty()) {
        ctx->error("kinddeed name is empty");
        return ;
    }

    if(desc.empty()) {
        ctx->error("kinddeed desc is empty");
        return ;
    }

    if(price.empty()) {
        ctx->error("kinddeed price is empty");
        return ;
    }

    if(count.empty()) {
        ctx->error("kinddeed count is empty");
        return ;
    }

    if(lasttime.empty()) {
        ctx->error("kinddeed lasttime is empty");
        return ;
    }

    kinddeed ent;
    if (is_kinddeed_exist(id, ent))  {
        ctx->error("kinddeed " + ent.to_string() + " is exist .");
        return ;
    }

    ent.set_id(id.c_str());
    ent.set_name(name.c_str());
    ent.set_owner(ctx->initiator().c_str());
    ent.set_desc(desc.c_str());
    ent.set_price(std::stod(price));
    ent.set_count(std::stoll(count));
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
    if(!is_master() && !is_founder()) {
        ctx->error(ctx->initiator() + " is not founder and master, has no authority to delete kinddeed .");
        return ;
    }

    const std::string& id = ctx->arg("id");
    if(id.empty()) {
        ctx->error("kinddeed id is empty");
        return ;
    }

    kinddeed ent;
    if (!is_kinddeed_exist(id, ent))  {
        ctx->error("kinddeed " + id + " is not exist .");
        return ;
    }

    if(ent.owner() != ctx->initiator() ) {
        ctx->error("kinddeed " + ent.to_string() + " is not belong to you.");
        return ;
    }

    if( !delete_kinddeed_record(id) ) {
        ctx->error("delete kinddeed "+ ent.to_string() + " failure .");
        return;
    }

    ctx->ok("delete kinddeed " + ent.to_string() + " success .");
}

void Buddha::update_kinddeed() {
    if(!is_master() && !is_founder()) {
        ctx->error(ctx->initiator() + " is not founder and master, has no authority to update kinddeed .");
        return ;
    }

    const std::string& id = ctx->arg("id");
    const std::string& id = ctx->arg("name");
    const std::string& desc = ctx->arg("desc");
    const std::string& price = ctx->arg("price");
    const std::string& count = ctx->arg("count");
    const std::string& lasttime = ctx->arg("lasttime");
    if(id.empty()) {
        ctx->error("kinddeed id is empty");
        return ;
    }

    if(name.empty()) {
        ctx->error("kinddeed name is empty");
        return ;
    }

    if(desc.empty()) {
        ctx->error("kinddeed desc is empty");
        return ;
    }

    if(price.empty()) {
        ctx->error("kinddeed price is empty");
        return ;
    }

    if(count.empty()) {
        ctx->error("kinddeed count is empty");
        return ;
    }

    if(lasttime.empty()) {
        ctx->error("kinddeed lasttime is empty");
        return ;
    }

    kinddeed ent;
    if (!is_kinddeed_exist(id, ent))  {
        ctx->error("kinddeed " + id + " is not exist .");
        return ;
    }

    if(ent.owner() != ctx->initiator() ) {
        ctx->error("kinddeed " + ent.to_string() + " is not belong to you.");
        return ;
    }

    if( !delete_kinddeed_record(id) ) {
        ctx->error("delete kinddeed "+ ent.to_string() + " failure .");
        return;
    }

    ent.set_id(id.c_str());
    ent.set_name(name.c_str());
    // ent.set_owner(ctx->initiator().c_str());
    ent.set_desc(desc.c_str());
    ent.set_price(std::stod(price));
    ent.set_count(std::stoll(count));
    ent.set_lasttime(lasttime.c_str());
    // ent.set_applied(false);
    // ent.set_online(false);
    if (!get_kinddeed_table().put(ent)) {
        ctx->error("kinddeed table put "+ ent.to_string() + " error .");
        return;
    }

    ctx->ok("update kinddeed " + ent.to_string() + " success .");
}

void Buddha::find_kinddeed() {       

    const std::string& id = ctx->arg("id");
    if(id.empty()) {
        ctx->error("kinddeed id is empty");
        return ;
    }

    kinddeed ent;
    if (!is_kinddeed_exist(id, ent))  {
        ctx->ok("kinddeed " + id + " is not exist .");
        return ;
    }

    ctx->ok("found kinddeed " + ent.to_string());
}

void Buddha::list_kinddeed() {
    if(!is_deployer() && !is_founder() && !is_master()) {
        ctx->error(ctx->initiator() + " is not deployer nor founder, has no authority to list kinddeed .");
        return ;
    }

    auto it = get_kinddeed_table().scan({{"id",""}});
    int i = 0;
    std::string ret;
    while(it->next()) {
        kinddeed ent;
        if (it->get(&ent)) {
            i++;
            ret += ent.to_string();
        }
        else
            std::cout << __LINE__ << " get error : " << it->error(true) << std::endl;
    }
    ctx->ok("size=" + std::to_string(i) + " " + ret);
}

namespace 申请善举上架下架{}

void Buddha::apply_online_kinddeed() {
    const std::string& id = ctx->arg("id");
    if(id.empty()) {
        ctx->error("kinddeed id is empty");
        return ;
    }

    if(!is_master() && !is_founder()) {
        ctx->error(ctx->initiator() + " is not master, has no authority to apply online kinddeed .");
        return ;
    }
    
    kinddeed ent;
    if (!is_kinddeed_exist(id, ent))  {
        ctx->error("kinddeed " + id + " is not exist .");
        return ;
    }

    if (ent.online()==true){
        ctx->error("kinddeed " + ent.to_string() + " is already online .");
        return ;
    }

    if(ent.owner() != ctx->initiator() ) {
        ctx->error("kinddeed " + ent.to_string() + " is not belong to you.");
        return ;
    }

    if( !delete_kinddeed_record(id) ) {
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
    const std::string& id = ctx->arg("id");
    if(id.empty()) {
        ctx->error("kinddeed id is empty");
        return ;
    }

    if(!is_master() && !is_founder()) {
        ctx->error(ctx->initiator() + " is not master, has no authority to apply online kinddeed .");
        return ;
    }
    
    kinddeed ent;
    if (!is_kinddeed_exist(id, ent))  {
        ctx->error("kinddeed " + id + " is not exist .");
        return ;
    }

    if (ent.online()==false){
        ctx->error("kinddeed " + ent.to_string() + " is already offline .");
        return ;
    }

    if(ent.owner() != ctx->initiator() ) {
        ctx->error("kinddeed " + ent.to_string() + " is not belong to you.");
        return ;
    }

    if( !delete_kinddeed_record(id) ) {
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
    const std::string& id = ctx->arg("id");
    if(id.empty()) {
        ctx->error("kinddeed id is empty");
        return ;
    }

    if(!is_founder()) {
        ctx->error(ctx->initiator() + " is not founder, has no authority to approve online kinddeed .");
        return ;
    }

    kinddeed ent;
    if (!is_kinddeed_exist(id, ent))  {
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

    if( !delete_kinddeed_record(id) ) {
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
    const std::string& id = ctx->arg("id");
    if(id.empty()) {
        ctx->error("kinddeed id is empty");
        return ;
    }

    if(!is_founder()) {
        ctx->error(ctx->initiator() + " is not founder, has no authority to approve offline kinddeed .");
        return ;
    }

    kinddeed ent;
    if (!is_kinddeed_exist(id, ent))  {
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

    if( !delete_kinddeed_record(id) ) {
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

namespace 注册会员{}

void Buddha::apply_member() {
}

bool Buddha::is_member() {
    bool ret = _is_member(ctx->initiator());
    if (ret) {
        ctx->ok(ctx->initiator() + " is member .") ;
        return true;
    }
    
    ctx->ok(ctx->initiator() + " is not member .") ;
    return false;
}

namespace 会员祈求善举{}


void Buddha::pray_kinddeed() {

    cout << endl ;
    
    const std::string& orderid = ctx->arg("id");
    if(orderid.empty()) {
        ctx->error("orderid is empty");
        return ;
    }

    const std::string& kdid = ctx->arg("kdid");
    if(kdid.empty()) {
        ctx->error("kdid is empty");
        return ;
    }

    const std::string& kdseqid = ctx->arg("kdseqid");
    if(kdseqid.empty()) {
        ctx->error("kdseqid is empty");
        return ;
    }

    const std::string& count = ctx->arg("count");
    if(count.empty()) {
        ctx->error("count is empty");
        return ;
    }

    const std::string& amount = ctx->transfer_amount();
    if(amount.empty()) {
        ctx->error("amount is empty");
        return ;
    }

    const std::string& timestamp = ctx->arg("timestamp");
    if(timestamp.empty()) {
        ctx->error("timestamp is empty");
        return ;
    }

    order od;
    if (_is_order_exist_by_id(orderid,od))  {
        ctx->error("order " + orderid + " is exist .");
        return ;
    }

    //判断子订单表是否已经存在子订单id
    //获取所有的子订单id，存如数组，方便后面写入大订单表时使用
    //判断子订单id在数组中是否重复
    //判断善举表中对于当前订单的善举是否都存在
    //判断善举表中对于当前订单的善举是否已经上架
    //判断善举表中对于当前订单的数量是否够
    //计算总价格，要求转账过来的总价格跟订单计算出的总价格要求必须一直
    //判断法师是否存在
    int64_t calced_amount = 0;
    xchain::json sodidArray = xchain::json::array();
    std::string mastername;
    mycout << "suborders.size()=" << suborders.size() << endl;
    for(int i = 0 ; i < suborders.size() ; i++) {
        std::string sodid = suborders.at(i)["id"].template get<std::string>();
        std::string kdid = suborders.at(i)["kdid"].template get<std::string>();
        int64_t count = std::stoll(suborders.at(i)["count"].template get<std::string>());


        //判断善举表中对于当前订单的善举是否都存在
        kinddeed kd;
        if (!is_kinddeed_exist(kdid, kd))  {
            ctx->error("kinddeed " + kdid + " is not exist .");
            return ;
        }

        //判断善举表中对于当前订单的善举是否已经上架
        if (!is_kinddeed_online(kdid)) {
            ctx->error("kinddeed " + kdid + " is not online .");
            return ;
        }

        //判断善举表中对于当前订单的数量是否够
        if(kd.count() < count) {
            ctx->error("kinddeed " + kdid + " is not enough .");
            return ;
        }

        //讲各个子订单中的商品数量和商品价格进行总价格计算
        calced_amount += kd.price() * count ;

        //判断法师是否存在
        master mt;
        if (!is_master_exist(kd.owner(), mt))  {
            ctx->error("master " + kd.owner() + " is not exist .");
            return ;
        }
        mastername = kd.owner();
    }

    //由于可能存在善举价格浮动，实际价格可能高于或低于开始制作订单的总价格。
    if(calced_amount != std::stoll(amount)){
        ctx->error("delive amount " + amount
                   + ", real amount=" + std::to_string(calced_amount));
        return;
    }
    


    //存储大订单表
    order ent;
    ent.set_id(orderid.c_str());
    ent.set_owner(ctx->initiator());
    ent.set_mastername(mastername);
    ent.set_suborderids(sodidArray.dump().c_str());
    ent.set_amount(calced_amount);
    ent.set_timestamp(timestamp.c_str());
    if (!get_order_table().put(ent)) {
        ctx->error("order table put "+ ent.to_string() + " error .");
        return;
    }
    
    ctx->ok("pray kinddeed " + std::to_string(calced_amount) + " success .");
}

void Buddha::find_pray_kinddeed() {
    cout << endl ;

    const std::string& id = ctx->arg("id");
    if(id.empty()) {
        ctx->error("order id is empty");
        return ;
    }

    mycout << endl ;

    order ent;       
    if (!get_order_table().find({{"id", id}}, &ent)) {
        ctx->error("not found pray_kinddeed " + id);
        return ;
    }

    std::string ret = ent.to_string() + "," ;
    mycout << ret << endl ;

    //删除子订单表中的子订单
    xchain::json suborderids = xchain::json::parse(ent.suborderids());
    mycout << suborderids.dump().c_str() << endl ;

    if (!suborderids.is_array()) {
        ctx->error("field 'suborderids' need to be array .");
        return;
    }
    mycout << endl ;
    
    if ( suborderids.empty() || suborderids.size() == 0) {
        ctx->error("filed 'suborderids' empty .");
        return;
    }

    mycout << suborderids.size() << endl ;

    for(int i = 0 ; i < suborderids.size() ; i++) {
        std::string sodid = suborderids.at(i).template get<std::string>();
        mycout << sodid << endl ;

        suborder sod;
        if( !is_suborder_exist(sodid, sod) ) {
            ctx->error("order("+id+") sodid("+sodid+") not exist .");
            return;
        }

        ret += sod.to_string() + ",";
    }
    mycout << endl ;

    ctx->ok(ret);
}

void Buddha::list_pray_kinddeed() {
    if(!is_deployer() && !is_founder() && !is_master()) {
        ctx->error(ctx->initiator() + " is not deployer nor founder, has no authority to list order .");
        return ;
    }

    auto it = get_order_table().scan({{"id",""}});
    int i = 0;
    std::string ret;
    while(it->next()) {
        order ent;
        if (it->get(&ent)) {
            i++;
            ret += ent.to_string();
        }
        else
            std::cout << __LINE__ << " get error : " << it->error(true) << std::endl;
    }
    ctx->ok("size=" + std::to_string(i) + " " + ret);
}

namespace 基金会成员授权法师或寺院上传的善举凭证{}

void Buddha::upload_kinddeed_proof() {
    const std::string& orderid = ctx->arg("orderid");
    if(orderid.empty()) {
        ctx->error("kinddeed proof orderid is empty");
        return ;
    }

    const std::string& proof = ctx->arg("proof");
    if(proof.empty()) {
        ctx->error("kinddeed proof hash is empty");
        return ;
    }

    const std::string& timestamp = ctx->arg("timestamp");
    if(timestamp.empty()) {
        ctx->error("kinddeed proof timestamp is empty");
        return ;
    }


    order od;
    if (!_is_order_exist_by_id(orderid, od)) {
        delete_kinddeed_proof_record(orderid);
        ctx->error("order and suborder lost, kinddeed proof " + orderid + " be delete .");
        return ;
    }

    if( od.mastername() != ctx->initiator() ) {
        ctx->error(ctx->initiator() + " is not the right master, it should be " + od.mastername());
        return ;
    }

    kinddeedproof ent;
    if (_is_kinddeed_proof_exist_by_orderid(orderid, ent))  {
        ctx->error("kinddeed proof " + orderid + " is exist .");
        return ;
    }

    ent.set_orderid(orderid.c_str());
    ent.set_proof(proof.c_str());
    ent.set_timestamp(timestamp.c_str());
    ent.set_approved(false);
    if (!get_kinddeed_proof_table().put(ent)) {
        ctx->error("kinddeed proof table put "+ ent.to_string() + " error .");
        return;
    }

    ctx->ok("apply kinddeed "+ ent.to_string() + " proof over, please wait for approve .");
}

void Buddha::approve_kinddeed_proof() {
    const std::string& orderid = ctx->arg("orderid");
    if(orderid.empty()) {
        ctx->error("kinddeed proof orderid is empty");
        return ;
    }

    if(!is_founder()) {
        ctx->error(ctx->initiator() + " is not founder, has no authority to approve kinddeed proof .");
        return ;
    }

    order od;
    if (!_is_order_exist_by_id(orderid, od)) {
        delete_kinddeed_proof_record(orderid);
        ctx->error("order and suborder lost, kinddeed proof " + orderid + " be delete .");
        return ;
    }

    kinddeedproof ent;
    if (!_is_kinddeed_proof_exist_by_orderid(orderid, ent))  {
        ctx->error("kinddeed proof " + orderid + " is not exist .");
        return ;
    }

    if (ent.approved())  {
        ctx->ok("kinddeed proof " + orderid + " has approved yet .");
        return ;
    }

    if(!transfer(od.mastername(), std::to_string(od.amount()))) {
        ctx->error("transfer to " + od.mastername() + " " +  std::to_string(od.amount()) + " failure .");
        return ;
    }

    if( !delete_kinddeed_proof_record(orderid) ) {
        ctx->error("delete kinddeed proof "+ ent.to_string() + " failure .");
        return;
    }

    ent.set_approved(true);
    if (!get_kinddeed_proof_table().put(ent)) {
        ctx->error("kinddeed proof table put "+ ent.to_string() + " error .");
        return;
    }

    ctx->ok("approve kinddeed "+ ent.to_string() + " proof success .");
}

void Buddha::refuse_kinddeed_proof() {
    const std::string& orderid = ctx->arg("orderid");
    if(orderid.empty()) {
        ctx->error("kinddeed proof orderid is empty");
        return ;
    }

    if(!is_founder()) {
        ctx->error(ctx->initiator() + " is not founder, has no authority to approve kinddeed proof .");
        return ;
    }

    order od;
    if (!_is_order_exist_by_id(orderid, od)) {
        delete_kinddeed_proof_record(orderid);
        ctx->error("order lost, kinddeed proof " + orderid + " be delete .");
        return ;
    }

    kinddeedproof ent;
    if (!_is_kinddeed_proof_exist_by_orderid(orderid, ent))  {
        ctx->error("kinddeed proof " + orderid + " is not exist .");
        return ;
    }

    if (ent.approved())  {
        ctx->ok("kinddeed proof " + orderid + " has approved yet .");
        return ;
    }

    if( !delete_kinddeed_proof_record(orderid) ) {
        ctx->error("delete kinddeed proof "+ ent.to_string() + " failure .");
        return;
    }

    ctx->ok("refuse kinddeed "+ ent.to_string() + " proof success .");
}


void Buddha::list_kinddeed_proof() {
    if(!is_deployer()&&!is_founder()) {
        ctx->error(ctx->initiator() + " is not deployer nor founder, has no authority to list kinddeed proof .");
        return ;
    }

    auto it = get_kinddeed_proof_table().scan({{"orderid",""}});
    int i = 0;
    std::string ret;
    while(it->next()) {
        kinddeedproof ent;
        if (it->get(&ent)) {
            i++;
            ret += ent.to_string();
        }
        else
            std::cout << __LINE__ << " get error : " << it->error(true) << std::endl;
    }
    ctx->ok("size=" + std::to_string(i) + " " + ret);
}

bool Buddha::is_user() {
    bool ret = _is_user(ctx->initiator());
    if (ret) {
        ctx->ok(ctx->initiator() + " is user .") ;
        return true;
    }
    
    ctx->ok(ctx->initiator() + " is not user .") ;
    return false;
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

DEFINE_METHOD(Buddha, apply_master)             { self.apply_master();              }
DEFINE_METHOD(Buddha, approve_master)           { self.approve_master();            }
DEFINE_METHOD(Buddha, recusal_master)           { self.recusal_master();            }
DEFINE_METHOD(Buddha, is_master)                { self.is_master();                 }
DEFINE_METHOD(Buddha, list_master)              { self.list_master();               }

DEFINE_METHOD(Buddha, add_kinddeed)             { self.add_kinddeed();              }
DEFINE_METHOD(Buddha, delete_kinddeed)          { self.delete_kinddeed();           }
DEFINE_METHOD(Buddha, update_kinddeed)          { self.update_kinddeed();           }
DEFINE_METHOD(Buddha, find_kinddeed)            { self.find_kinddeed();             }
DEFINE_METHOD(Buddha, list_kinddeed)            { self.list_kinddeed();             }

DEFINE_METHOD(Buddha, apply_online_kinddeed)    { self.apply_online_kinddeed();     }
DEFINE_METHOD(Buddha, apply_offline_kinddeed)   { self.apply_offline_kinddeed();    }
DEFINE_METHOD(Buddha, approve_online_kinddeed)  { self.approve_online_kinddeed();   }
DEFINE_METHOD(Buddha, approve_offline_kinddeed) { self.approve_offline_kinddeed();  }

DEFINE_METHOD(Buddha, apply_member)             { self.apply_member();              }
DEFINE_METHOD(Buddha, is_member)                { self.is_member();                 }

DEFINE_METHOD(Buddha, pray_kinddeed)            { self.pray_kinddeed();             }
DEFINE_METHOD(Buddha, find_pray_kinddeed)       { self.find_pray_kinddeed();        }
DEFINE_METHOD(Buddha, list_pray_kinddeed)       { self.list_pray_kinddeed();        }

DEFINE_METHOD(Buddha, upload_kinddeed_proof)    { self.upload_kinddeed_proof();     }
DEFINE_METHOD(Buddha, approve_kinddeed_proof)   { self.approve_kinddeed_proof();    }
DEFINE_METHOD(Buddha, refuse_kinddeed_proof)    { self.refuse_kinddeed_proof();     }
DEFINE_METHOD(Buddha, list_kinddeed_proof)      { self.list_kinddeed_proof();       }

DEFINE_METHOD(Buddha, is_user)                  { self.is_user();                   }
