#include <inttypes.h>
#include "xchain/json/json.h"
#include "xchain/xchain.h"
#include "xchain/account.h"
#include "xchain/table/types.h"
#include "xchain/table/table.tpl.h"
#include "xchain/contract.pb.h"
#include "xchain/syscall.h"
#include "buddha.pb.h"
#include <iostream>
using namespace std;

#define mycout cout << __func__ << "[" << __LINE__ << "] " 

namespace pb = xchain::contract::sdk;

class founder: public buddha::Founder {
    DEFINE_ROWKEY(name);
    DEFINE_INDEX_BEGIN(1)
        DEFINE_INDEX_ADD(0, name)
    DEFINE_INDEX_END();

    std::string to_string() {
        std::string str ;
        str += "{" ;
        str += name() + ",";
        str += desc() + ",";
        str += std::to_string(guaranty()) + ",";
        str += std::to_string(is());
        str += "}";
        return str;
    }
};

class master: public buddha::Master {
    DEFINE_ROWKEY(name);
    DEFINE_INDEX_BEGIN(1)
        DEFINE_INDEX_ADD(0, name)
    DEFINE_INDEX_END();

    std::string to_string() {
        std::string str ;
        str += "{" ;
        str += name() + ",";
        str += desc() + ",";
        str += std::to_string(is());
        str += "}";
        return str;
    }
};

class kinddeedproof: public buddha::KinddeedProof {
    DEFINE_ROWKEY(orderid);
    DEFINE_INDEX_BEGIN(1)
        DEFINE_INDEX_ADD(0, orderid)
    DEFINE_INDEX_END();

    std::string to_string() {
        std::string str ;
        str += "{" ;
        str += orderid() + ",";
        str += proof() + ",";
        str += timestamp() + ",";
        str += std::to_string(approved());
        str += "}";
        return str;
    }
};

// 1. rowkey can not be same with index
class kinddeed: public buddha::Kinddeed {
    DEFINE_ROWKEY(id);
    DEFINE_INDEX_BEGIN(1)
        DEFINE_INDEX_ADD(0, id)
    DEFINE_INDEX_END();

    std::string to_string() {
        std::string str ;
        str += "{" ;
        str += id() + ",";
        str += name() + ",";
        str += owner() + ",";
        str += desc() + ",";
        str += std::to_string(price()) + ",";
        str += std::to_string(count()) + ",";
        str += lasttime() + ",";
        str += std::to_string(applied()) + ",";
        str += std::to_string(online()); 
        str += "}";
        return str;
    }
};

class suborder: public buddha::SubOrder {
    DEFINE_ROWKEY(id);
    DEFINE_INDEX_BEGIN(1)
        DEFINE_INDEX_ADD(0, id)
    DEFINE_INDEX_END();

    std::string to_string() {
        std::string str ;
        str += "{" ;
        str += id() + ",";
        str += orderid() + ",";        
        str += kdid() + ",";
        str += kdname() + ",";
        str += kddesc() + ",";
        str += std::to_string(kdprice()) + ",";
        str += std::to_string(kdcount()) ;
        str += "}";
        return str;
    }
};

class order: public buddha::Order {
    DEFINE_ROWKEY(id);
    DEFINE_INDEX_BEGIN(1)
        DEFINE_INDEX_ADD(0, id)
    DEFINE_INDEX_END();

    std::string to_string() {
        std::string str ;
        str += "{" ;
        str += id() + ",";
        str += owner() + ",";
        str += mastername() + ",";
        str += suborderids() + ",";
        str += std::to_string(amount()) + ",";
        str += timestamp() ;
        str += "}";
        return str;
    }
};


class Buddha : public xchain::Contract {
public:
    Buddha();

private:
    xchain::cdt::Table<founder>  _founder_table;
    xchain::cdt::Table<master>  _master_table;
    xchain::cdt::Table<kinddeedproof>  _kinddeed_proof_table;
    xchain::cdt::Table<kinddeed>  _kinddeed_table;
    xchain::cdt::Table<suborder>    _suborder_table;
    xchain::cdt::Table<order> _order_table;
    xchain::Context* ctx;

public:
    decltype(_founder_table)& get_founder_table() {
        return _founder_table;
    }

    decltype(_master_table)& get_master_table() {
        return _master_table;
    }

    decltype(_kinddeed_proof_table)& get_kinddeed_proof_table() {
        return _kinddeed_proof_table;
    }

    decltype(_kinddeed_table)& get_kinddeed_table() {
        return _kinddeed_table;
    }

    decltype(_suborder_table)& get_suborder_table() {
        return _suborder_table;
    }

    decltype(_order_table)& get_order_table() {
        return _order_table;
    }

private:
    //辅助函数
    bool is_founder_exist(const std::string& name,founder& ent);
    bool is_master_exist(const std::string& name,master& ent);

    bool is_kinddeed_proof_exist(const std::string& id,kinddeedproof& ent);
    bool is_kinddeed_exist(const std::string& id,kinddeed& ent);
    void find_kinddeed(const std::string& id,kinddeed& ent);
    bool is_kinddeed_online(const std::string& kdid) ;
    bool is_suborder_exist(const std::string& id,suborder& ent);
    bool is_order_exist(const std::string& id,order& ent);

    bool is_deployer(const std::string& name);
    bool is_founder(const std::string& name);
    bool is_master(const std::string& name);
    bool is_user(const std::string& name);

    void delete_founder_record(const std::string& name);
    void delete_master_record(const std::string& name);
    void delete_kinddeed_proof_record(const std::string& orderid);   
    void delete_kinddeed_record(const std::string& id);
    void delete_suborder_record(const std::string& id);
    void delete_order_record(const std::string& id);

    bool transfer(const std::string& name,
                const std::string& amount);

public:
    //对外的辅助接口
    bool is_deployer();
    bool is_founder();
    bool is_master();
    bool is_user();

    //部署者
    void initialize();
    void get_deployer();

    //update无对应函数
    void approve_founder();
    void recusal_founder();

    //基金会成员
    void approve_master();
    void recusal_master();
    void approve_online_kinddeed();
    void approve_offline_kinddeed();
    void approve_kinddeed_proof();
    void refuse_kinddeed_proof();


    //法师
    void apply_online_kinddeed();
    void apply_offline_kinddeed();
    void upload_kinddeed_proof();

    //用户
    void apply_master();
    void pray_kinddeed();

    //用户和法师共同
    void apply_founder();

    //基金会成员、法师共同
    void add_kinddeed();
    void delete_kinddeed();
    void update_kinddeed(); 

    //所有用户
    void find_kinddeed();
    void find_pray_kinddeed();
 };

namespace helpers{}

Buddha::Buddha() :
    _founder_table(context(), "founder"),
    _master_table(context(), "master"),
    _kinddeed_proof_table(context(), "kinddeed_proof"),
    _kinddeed_table(context(), "kinddeed"),
    _suborder_table(context(), "suborder"),
    _order_table(context(), "order"),
    ctx(context())
{

}

bool Buddha::is_founder_exist(const std::string& name,founder& ent) {
    if (!get_founder_table().find({{"name", name}}, &ent))
        return false;

    return true;
}

bool Buddha::is_master_exist(const std::string& name,master& ent){
    if (!get_master_table().find({{"name", name}}, &ent))
        return false;

    return true;
}

bool Buddha::is_kinddeed_proof_exist(const std::string& orderid,kinddeedproof& ent) {
    if (!get_kinddeed_proof_table().find({{"orderid", orderid}}, &ent))
        return false;

    return true;
}

bool Buddha::is_kinddeed_exist(const std::string& id,kinddeed& ent) {
    if (!get_kinddeed_table().find({{"id", id}}, &ent))
        return false;

    return true;
}

void Buddha::find_kinddeed(const std::string& id,kinddeed& ent) {
    get_kinddeed_table().find({{"id", id}}, &ent);
}

bool Buddha::is_kinddeed_online(const std::string& id){
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


bool Buddha::is_suborder_exist(const std::string& id,
                                suborder& ent) {
    if (!get_suborder_table().find({{"id", id}}, &ent)) {
        mycout << "suborder[" << id << "] is not exist ." << endl;
        return false;
    }

    return true;
}

bool Buddha::is_order_exist(const std::string& id,order& ent) {
    if (!get_order_table().find({{"id", id}}, &ent)) {
        ctx->error("order["+id + "] is not exist .");
        return false;
    }

    //删除子订单表中的子订单
    xchain::json suborderids = xchain::json::parse(ent.suborderids());

    if (!suborderids.is_array()) {
        ctx->error("field 'suborderids' need to be array .");
        get_order_table().del(ent);
        return false;
    }
    
    if ( suborderids.empty() || suborderids.size() == 0) {
        ctx->error("filed 'suborderids' empty .");
        get_order_table().del(ent);
        return false;
    }

    for(int i = 0 ; i < suborderids.size() ; i++) {
        std::string sodid = suborderids.at(i).template get<std::string>();
        suborder sod;
        if( !is_suborder_exist(sodid, sod) ) {
            ctx->error("sodid("+sodid+") is not exist .");
            get_order_table().del(ent);
            return false;
        }
    }

    return true;
}

bool Buddha::is_deployer(const std::string& name) {
    std::string deployer;
    if (!ctx->get_object("deployer", &deployer)) 
        return false;

    if (deployer != name )
        return false;

    return true ;
}

bool Buddha::is_founder(const std::string& name) {
    founder ent;
    if (!is_founder_exist(name, ent))
        return false;
    
    if( ent.is() != true ) 
        return false;

    return true;
}

bool Buddha::is_master(const std::string& name) {
    master ent;
    if (!is_master_exist(name, ent))
        return false;
    
    if( ent.is() != true ) 
        return false;

    return true ;
}


bool Buddha::is_user(const std::string& name) {
    if(is_deployer(name)) 
        return false;

    if(is_founder(name)) 
        return false;

    if(is_master(name)) 
        return false;

    return true ;
}

bool Buddha::is_deployer() {
    bool ret = is_deployer(ctx->initiator());
    if (ret) {
        ctx->ok(ctx->initiator() + " is deployer .") ;
        return true;
    }
    
    ctx->ok(ctx->initiator() + " is not deployer .") ;
    return false;
}

bool Buddha::is_founder() {
    bool ret = is_founder(ctx->initiator());
    if (ret) {
        ctx->ok(ctx->initiator() + " is founder .") ;
        return true;
    }
    
    ctx->ok(ctx->initiator() + " is not founder .") ;
    return false;
}

bool Buddha::is_master() {
    bool ret = is_master(ctx->initiator());
    if (ret) {
        ctx->ok(ctx->initiator() + " is master .") ;
        return true;
    }
    
    ctx->ok(ctx->initiator() + " is not master .") ;
    return false;
}

bool Buddha::is_user() {
    bool ret = is_user(ctx->initiator());
    if (ret) {
        ctx->ok(ctx->initiator() + " is user .") ;
        return true;
    }
    
    ctx->ok(ctx->initiator() + " is not user .") ;
    return false;
}

void Buddha::delete_founder_record(const std::string& name) {
    while(true) {
        founder ent;
        if(!is_founder_exist(name, ent))
            break;

        get_founder_table().del(ent);

        mycout << "delete founder " << ent.to_string() << endl ;
    }
}

void Buddha::delete_master_record(const std::string& name) {
    while(true) {
        master ent;
        if(!is_master_exist(name, ent))
            break;

        get_master_table().del(ent);
        mycout << "delete master " << ent.to_string() << endl ;
    }
}

void Buddha::delete_kinddeed_proof_record(const std::string& orderid) {
    while(true) {
        kinddeedproof ent;
        if(!is_kinddeed_proof_exist(orderid, ent))
            break;

        get_kinddeed_proof_table().del(ent);
        mycout << "delete kinddeed_proof " << ent.to_string() << endl ;
    }
}

void Buddha::delete_kinddeed_record(const std::string& id) {
    while(true) {
        kinddeed ent;
        if(!is_kinddeed_exist(id, ent))
            break;

        get_kinddeed_table().del(ent);
        mycout << "delete kinddeed " << ent.to_string() << endl ;
    }
}


void Buddha::delete_suborder_record(const std::string& id) {
    while(true) {
        suborder ent;
        if(!is_suborder_exist(id, ent))
            break;

        get_suborder_table().del(ent);
        mycout << "delete suborder " << ent.to_string() << endl ;
    }
}

void Buddha::delete_order_record(const std::string& orderid) {
    while(true) {
        order ent;
        if(!is_order_exist(orderid, ent))
            break;

        //删除子订单表中的子订单
        xchain::json suborderids = xchain::json::parse(ent.suborderids());
 
        if (!suborderids.is_array()) {
            ctx->error("field 'suborderids' need to be array .");
            return;
        }
        
        if ( suborderids.empty() || suborderids.size() == 0) {
            ctx->error("filed 'suborderids' empty .");
            return;
        }

        for(int i = 0 ; i < suborderids.size() ; i++) {
            std::string id = suborderids.at(i).template get<std::string>();
            delete_suborder_record(id);
        }

        get_order_table().del(ent);
        mycout << "delete order " << ent.to_string() << endl ;
    }
}

bool Buddha::transfer(const std::string& name,
                    const std::string& amount){
    //将抵押退还
    xchain::Account account = xchain::Account(name);
    if(!account.transfer(amount)) 
        return false;

    return true ;
}

namespace deployer{}
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

void Buddha::approve_founder() {
    const std::string& name = ctx->arg("name");
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

    if(is_founder(name)) {
        ctx->error(ent.to_string() + " is already founder .");
        return ;
    }

    delete_founder_record(name);        
    ent.set_is(true);
    get_founder_table().put(ent);
    ctx->ok("audit "+ ent.to_string() + " to be founder .");
}

void Buddha::recusal_founder() {
    const std::string& name = ctx->arg("name");
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

    delete_founder_record(name);

    ctx->ok("recusal founder "+ name + " success , guaranty " + guaranty + " has refund, please check balance.");
}

namespace ruler_founder{}

void Buddha::approve_master() {
    const std::string& name = ctx->arg("name");
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

    if(is_master(name)) {
        ctx->error(ent.to_string() + " is already master .");
        return ;
    }

    delete_master_record(name);
    ent.set_is(true);
    get_master_table().put(ent);

    ctx->ok("approve master "+ ent.to_string() + " success .");
}

void Buddha::recusal_master() {
    const std::string& name = ctx->arg("name");
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

    delete_master_record(name);

    ctx->ok("recusal master "+ ent.to_string() + " success .");
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

    delete_kinddeed_record(id);
    ent.set_applied(false);
    ent.set_online(true);
    get_kinddeed_table().put(ent);

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

    delete_kinddeed_record(id);
    ent.set_applied(false);
    ent.set_online(false);
    get_kinddeed_table().put(ent);

    ctx->ok("approve kinddeed "+ ent.to_string() + " offline success .");
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
    if (!is_order_exist(orderid, od)) {
        delete_kinddeed_proof_record(orderid);
        ctx->error("order and suborder lost, kinddeed proof " + orderid + " be delete .");
        return ;
    }

    kinddeedproof ent;
    if (!is_kinddeed_proof_exist(orderid, ent))  {
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

    delete_kinddeed_proof_record(orderid);
    ent.set_approved(true);
    get_kinddeed_proof_table().put(ent);

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
    if (!is_order_exist(orderid, od)) {
        delete_kinddeed_proof_record(orderid);
        ctx->error("order lost, kinddeed proof " + orderid + " be delete .");
        return ;
    }

    kinddeedproof ent;
    if (!is_kinddeed_proof_exist(orderid, ent))  {
        ctx->error("kinddeed proof " + orderid + " is not exist .");
        return ;
    }

    if (ent.approved())  {
        ctx->ok("kinddeed proof " + orderid + " has approved yet .");
        return ;
    }

    delete_kinddeed_proof_record(orderid);

    ctx->ok("refuse kinddeed "+ ent.to_string() + " proof success .");
}

namespace ruler_master{}
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

    delete_kinddeed_record(id);
    ent.set_applied(true);
    get_kinddeed_table().put(ent);

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

    delete_kinddeed_record(id);
    ent.set_applied(true);
    get_kinddeed_table().put(ent);

    ctx->ok("kinddeed " + ent.to_string() + " apply offline over, please wait for approve .");
}

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
    if (!is_order_exist(orderid, od)) {
        delete_kinddeed_proof_record(orderid);
        ctx->error("order and suborder lost, kinddeed proof " + orderid + " be delete .");
        return ;
    }

    if( od.mastername() != ctx->initiator() ) {
        ctx->error(ctx->initiator() + " is not the right master, it should be " + od.mastername());
        return ;
    }

    kinddeedproof ent;
    if (is_kinddeed_proof_exist(orderid, ent))  {
        ctx->error("kinddeed proof " + orderid + " is exist .");
        return ;
    }

    ent.set_orderid(orderid.c_str());
    ent.set_proof(proof.c_str());
    ent.set_timestamp(timestamp.c_str());
    ent.set_approved(false);
    get_kinddeed_proof_table().put(ent);

    ctx->ok("apply kinddeed "+ ent.to_string() + " proof over, please wait for approve .");
}


namespace ruler_user{}

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
    ent.set_is(false);
    get_master_table().put(ent);

    ctx->ok(ent.to_string() + " apply tobe master over, please wait for approve .");
}

void Buddha::pray_kinddeed() {

    cout << endl ;
    
    const std::string& orderid = ctx->arg("id");
    if(orderid.empty()) {
        ctx->error("orderid is empty");
        return ;
    }

    //判断订单中的产品部分是否是数组，是否数组为空
    auto suborders = xchain::json::parse(ctx->arg("suborders"));
 
    mycout << suborders.dump().c_str() << endl;

    if (!suborders.is_array()) {
        ctx->error("field 'suborders' need to be array .");
        return;
    }
    
    if ( suborders.empty() || suborders.size() == 0) {
        ctx->error("filed 'suborders' empty .");
        return;
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
    if (is_order_exist(orderid,od))  {
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

        mycout << "suboderid=" << sodid << ", kdid=" << kdid << ", count=" << count << endl;

        //判断子订单表是否已经存在子订单id
        suborder sod;
        if(is_suborder_exist(sodid, sod)) {
            ctx->error("suborder " + sodid + " is exist .");
            return ;
        }

        //判断子订单id在数组中是否重复
        for(int j=0; j< sodidArray.size() ; j++) {
            if( sodidArray[j] == sodid ) {
                ctx->error("suborder has repeat .");
                return ;
            }  
        }

        //获取所有的子订单id，存如数组，方便后面写入大订单表时使用
        sodidArray.push_back(sodid);

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
    

    //存储子订单表
    //更新善举表数量
    for(int i = 0 ; i < suborders.size() ; i++) {
        std::string sodid = suborders.at(i)["id"].template get<std::string>();
        std::string kdid = suborders.at(i)["kdid"].template get<std::string>();
        int64_t count = std::stoll(suborders.at(i)["count"].template get<std::string>());
        mycout << "suboderid=" << sodid << ", kdid=" << kdid << ", count=" << count << endl;

        kinddeed kd;
        find_kinddeed(kdid, kd);

        suborder od;
        od.set_id(sodid.c_str());
        od.set_orderid(orderid.c_str());
        od.set_kdid(kd.id().c_str());
        od.set_kdname(kd.name().c_str());
        od.set_kddesc(kd.desc().c_str());
        od.set_kdprice(kd.price());
        od.set_kdcount(count);
        get_suborder_table().put(od);

        int64_t c = kd.count()-count;
        delete_kinddeed_record(kdid);
        kd.set_count(c);
        get_kinddeed_table().put(kd);

        mycout << "order[" << orderid << "] suborder[" << sodid << "] kinddeed[" << kdid << "] count(" << kd.count() << "-" << count << "=" << c << ")" << endl ;
    }

    //存储大订单表
    order ent;
    ent.set_id(orderid.c_str());
    ent.set_owner(ctx->initiator());
    ent.set_mastername(mastername);
    ent.set_suborderids(sodidArray.dump().c_str());
    ent.set_amount(calced_amount);
    ent.set_timestamp(timestamp.c_str());
    get_order_table().put(ent);
    
    ctx->ok("pray kinddeed " + std::to_string(calced_amount) + " success .");
}

namespace ruler_master_user{}
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

    founder ent;
    if(is_founder_exist(ctx->initiator(),ent))
        delete_founder_record(ctx->initiator());

    ent.set_name(ctx->initiator().c_str());
    ent.set_desc(desc.c_str());
    ent.set_guaranty(ent.guaranty() + std::stoll(guaranty));
    ent.set_is(false);
    get_founder_table().put(ent);

    ctx->ok(ent.to_string() + " apply tobe founder over, please wait for approve .");
}

namespace ruler_founder_master{}

void Buddha::add_kinddeed() {
    if(!is_master() && !is_founder()) {
        ctx->error(ctx->initiator() + " is not founder and master, has no authority to add kinddeed .");
        return ;
    }

    const std::string& id = ctx->arg("id");
    const std::string& name = ctx->arg("name");
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

    get_kinddeed_table().put(ent);

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

    delete_kinddeed_record(id);

    ctx->ok("delete kinddeed " + ent.to_string() + " success .");
}

void Buddha::update_kinddeed() {
    if(!is_master() && !is_founder()) {
        ctx->error(ctx->initiator() + " is not founder and master, has no authority to update kinddeed .");
        return ;
    }

    const std::string& id = ctx->arg("id");
    const std::string& name = ctx->arg("name");
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

    delete_kinddeed_record(id);
    ent.set_id(id.c_str());
    ent.set_name(name.c_str());
    // ent.set_owner(ctx->initiator().c_str());
    ent.set_desc(desc.c_str());
    ent.set_price(std::stod(price));
    ent.set_count(std::stoll(count));
    ent.set_lasttime(lasttime.c_str());
    // ent.set_applied(false);
    // ent.set_online(false);
    get_kinddeed_table().put(ent);

    ctx->ok("update kinddeed " + ent.to_string() + " success .");
}


namespace ruler_founder_master_user{}

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


// ---------- 对外接口 -------------

// 合约部署者
DEFINE_METHOD(Buddha, initialize)     { self.initialize();     }
DEFINE_METHOD(Buddha, approve_founder)   { self.approve_founder();   }
DEFINE_METHOD(Buddha, recusal_founder)    { self.recusal_founder();    }

// 基金会成员
DEFINE_METHOD(Buddha, approve_master)    { self.approve_master();    }
DEFINE_METHOD(Buddha, recusal_master)    { self.recusal_master();    }
DEFINE_METHOD(Buddha, approve_online_kinddeed) { self.approve_online_kinddeed(); }
DEFINE_METHOD(Buddha, approve_offline_kinddeed)   { self.approve_offline_kinddeed();   }
DEFINE_METHOD(Buddha, approve_kinddeed_proof)   { self.approve_kinddeed_proof();   }
DEFINE_METHOD(Buddha, refuse_kinddeed_proof)   { self.refuse_kinddeed_proof();   }


// 法师或寺院
DEFINE_METHOD(Buddha, apply_online_kinddeed)   { self.apply_online_kinddeed();   }
DEFINE_METHOD(Buddha, apply_offline_kinddeed)    { self.apply_offline_kinddeed();    }
DEFINE_METHOD(Buddha, upload_kinddeed_proof)    { self.upload_kinddeed_proof();    }

// 用户
DEFINE_METHOD(Buddha, apply_master)            { self.apply_master();            }
DEFINE_METHOD(Buddha, pray_kinddeed)            { self.pray_kinddeed();            }

// 用户和法师
DEFINE_METHOD(Buddha, apply_founder)      { self.apply_founder();            }

// 基金会成员 和 法师或寺院
DEFINE_METHOD(Buddha, add_kinddeed)    { self.add_kinddeed();    }
DEFINE_METHOD(Buddha, delete_kinddeed)    { self.delete_kinddeed();    }
DEFINE_METHOD(Buddha, update_kinddeed) { self.update_kinddeed(); }

// 所有角色
DEFINE_METHOD(Buddha, find_kinddeed)   { self.find_kinddeed();   }
DEFINE_METHOD(Buddha, find_pray_kinddeed)   { self.find_pray_kinddeed();   }
DEFINE_METHOD(Buddha, is_deployer)     { self.is_deployer();     }
DEFINE_METHOD(Buddha, is_founder)     { self.is_founder();     }
DEFINE_METHOD(Buddha, is_master)     { self.is_master();     }
DEFINE_METHOD(Buddha, is_user)     { self.is_user();     }