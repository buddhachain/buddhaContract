#include <inttypes.h>
#include "xchain/json/json.h"
#include "xchain/xchain.h"
#include "xchain/account.h"
#include "xchain/table/types.h"
#include "xchain/table/table.tpl.h"
#include "xchain/contract.pb.h"
#include "xchain/syscall.h"
#include "buddha.pb.h"

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

class order: public buddha::Order {
    DEFINE_ROWKEY(id);
    DEFINE_INDEX_BEGIN(1)
        DEFINE_INDEX_ADD(0, id)
    DEFINE_INDEX_END();

    std::string to_string() {
        std::string str ;
        str += "{" ;
        str += id() + ",";
        str += kinddeedid() + ",";
        str += kinddeedname() + ",";
        str += kinddeeddesc() + ",";
        str += std::to_string(kinddeedprice()) + ",";
        str += std::to_string(kinddeedcount()) ;
        str += "}";
        return str;
    }
};

class exchange: public buddha::Exchange {
    DEFINE_ROWKEY(orderid);
    DEFINE_INDEX_BEGIN(1)
        DEFINE_INDEX_ADD(0, orderid)
    DEFINE_INDEX_END();

    std::string to_string() {
        std::string str ;
        str += "{" ;
        str += orderid() + ",";
        str += kinddeeds() + ",";
        str += std::to_string(amount()) + ",";
        str += timestamp() ;
        str += "}";
        return str;
    }
};


class Buddha : public xchain::Contract {
public:
    Buddha(): _founder_table(context(),  "founder"),
                _master_table(context(),  "master"),
                _kinddeed_proof_table(context(),  "kinddeed_proof"),
                _kinddeed_table(context(),  "kinddeed"),
                _order_table(context(),    "order"),
                _exchange_table(context(), "exchange"),
                ctx(context()) {}

private:
    xchain::cdt::Table<founder>  _founder_table;
    xchain::cdt::Table<master>  _master_table;
    xchain::cdt::Table<kinddeedproof>  _kinddeed_proof_table;
    xchain::cdt::Table<kinddeed>  _kinddeed_table;
    xchain::cdt::Table<order>    _order_table;
    xchain::cdt::Table<exchange> _exchange_table;
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

    decltype(_order_table)& get_order_table() {
        return _order_table;
    }

    decltype(_exchange_table)& get_exchange_table() {
        return _exchange_table;
    }

private:
    //辅助函数
    bool is_founder_exist(const std::string& name,founder& ent);
    bool is_master_exist(const std::string& name,master& ent);

    bool is_kinddeed_proof_exist(const std::string& id,kinddeedproof& ent);
    bool is_kinddeed_exist(const std::string& id,kinddeed& ent);
    bool is_order_exist(const std::string& id,order& ent);
    bool is_exchange_exist(const std::string& id,exchange& ent);

    bool is_deployer(const std::string& name);
    bool is_founder(const std::string& name);
    bool is_master(const std::string& name);
    bool is_user(const std::string& name);

    bool is_deployer();
    bool is_founder();
    bool is_master();
    bool is_user();


    void delete_founder_record(const std::string& name);
    void delete_master_record(const std::string& name);
    void delete_kinddeed_proof_record(const std::string& orderid);   
    void delete_kinddeed_record(const std::string& id);
    void delete_order_record(const std::string& orderid);
    void delete_exchange_record(const std::string& orderid);

    bool refund(const std::string& name,
                const std::string& amount);

public:
    //部署者
    void initialize();
    //update无对应函数
    void approve_founder();
    void recusal_founder();

    //基金会成员
    void approve_master();
    void recusal_master();
    void approve_online_kinddeed();
    void approve_offline_kinddeed();
    void approve_kinddeed_proof();


    //法师
    void apply_online_kinddeed();
    void apply_offline_kinddeed();
    void upload_kinddeed_proof();

    //用户
    void apply_master();
    void pray_kinddeed();

    //用户和法师共同
    void apply_founder();

    //基金会成员、法师、普通用户共同
    void find_kinddeed();

    //基金会成员、法师共同
    void add_kinddeed();
    void delete_kinddeed();
    void update_kinddeed(); 

};

namespace helpers{}

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

bool Buddha::is_order_exist(const std::string& id,order& ent) {
    if (!get_order_table().find({{"id", id}}, &ent))
        return false;

    return true;
}

bool Buddha::is_exchange_exist(const std::string& id,exchange& ent) {
    if (!get_exchange_table().find({{"id", id}}, &ent))
        return false;

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
    return is_deployer(ctx->initiator());
}

bool Buddha::is_founder() {
    return is_founder(ctx->initiator());
}

bool Buddha::is_master() {
    return is_master(ctx->initiator());
}

bool Buddha::is_user() {
    return is_user(ctx->initiator());
}

void Buddha::delete_founder_record(const std::string& name) {
    while(true) {
        founder ent;
        if(!is_founder_exist(name, ent))
            break;

        get_founder_table().del(ent);
        std::string str ;
        str += "delete founder " + ent.to_string() ;
        ctx->logf(str.c_str());
    }
}

void Buddha::delete_master_record(const std::string& name) {
    while(true) {
        master ent;
        if(!is_master_exist(name, ent))
            break;

        get_master_table().del(ent);
        std::string str ;
        str += "delete master " + ent.to_string() ;
        ctx->logf(str.c_str());
    }
}

void Buddha::delete_kinddeed_proof_record(const std::string& orderid) {
    while(true) {
        kinddeedproof ent;
        if(!is_kinddeed_proof_exist(orderid, ent))
            break;

        get_kinddeed_proof_table().del(ent);
        std::string str ;
        str += "delete kinddeed_proof " + ent.to_string() ;
        ctx->logf(str.c_str());
    }
}

void Buddha::delete_kinddeed_record(const std::string& id) {
    while(true) {
        kinddeed ent;
        if(!is_kinddeed_exist(id, ent))
            break;

        get_kinddeed_table().del(ent);
        std::string str ;
        str += "delete kinddeed " + ent.to_string() ;
        ctx->logf(str.c_str());
    }
}


void Buddha::delete_order_record(const std::string& orderid) {
    while(true) {
        order ent;
        if(!is_order_exist(orderid, ent))
            break;

        get_order_table().del(ent);
        std::string str ;
        str += "delete order " + ent.to_string() ;
        ctx->logf(str.c_str());
    }
}

void Buddha::delete_exchange_record(const std::string& orderid) {
    while(true) {
        exchange ent;
        if(!is_exchange_exist(orderid, ent))
            break;

        get_exchange_table().del(ent);
        std::string str ;
        str += "delete exchange " + ent.to_string() ;
        ctx->logf(str.c_str());
    }
}

bool Buddha::refund(const std::string& name,
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
        ctx->ok(ent.to_string() + " is already founder .");
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
    if(!refund(name, guaranty)) {
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
        ctx->ok(ent.to_string() + " is already master .");
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

    exchange ex;
    order od;
    if (!is_order_exist(orderid, od) || !is_exchange_exist(orderid, ex)) {
        delete_exchange_record(orderid);
        delete_order_record(orderid);
        delete_kinddeed_proof_record(orderid);
        ctx->error("exchange and order lost, kinddeed proof " + orderid + " be delete .");
        return ;
    }

    kinddeedproof ent;
    if (!is_kinddeed_proof_exist(orderid, ent))  {
        ctx->ok("kinddeed proof " + orderid + " is not exist .");
        return ;
    }

    delete_kinddeed_proof_record(orderid);
    ent.set_approved(true);
    get_kinddeed_proof_table().put(ent);

    ctx->ok("approve kinddeed "+ ent.to_string() + " proof success .");
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

    if(!is_master()) {
        ctx->error(ctx->initiator() + " is not master, has no authority to upload kinddeed proof .");
        return ;
    }

    exchange ex;
    order od;
    if (!is_order_exist(orderid, od) || !is_exchange_exist(orderid, ex)) {
        delete_exchange_record(orderid);
        delete_order_record(orderid);
        delete_kinddeed_proof_record(orderid);
        ctx->error("exchange and order lost, kinddeed proof " + orderid + " be delete .");
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
        ctx->ok(ctx->initiator() + " is already master .");
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
    //应该是任何人都可以祈求。

    // if(!is_user()) {
    //     ctx->error(ctx->initiator() + " is not common user, has no authority to pray kinddeed .");
    //     return ;
    // }

    //判断订单是不是已经存在
    const std::string& orderid = ctx->arg("id");
    if(orderid.empty()) {
        ctx->error("orderid is empty");
        return ;
    }

    //判断订单中的产品部分是否是数组，是否数组为空
    const std::string& kinddeeds = ctx->arg("kinddeeds");

    auto kinddeed_ids = xchain::json::parse(kinddeeds);
 
    if (!kinddeed_ids.is_array()) {
        ctx->error("field 'kinddeeds' need to be array .");
        return;
    }
    
    if ( kinddeed_ids.empty() || kinddeed_ids.size() == 0) {
        ctx->error("filed 'kinddeeds' empty .");
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

    //判断总价格是否跟表中的计算价格相同
    double calced_amount = 0;
    for(int i = 0 ; i < kinddeed_ids.size() ; i++) {
        std::string id = kinddeed_ids.at(i)["id"].template get<std::string>();
        int64_t count = std::stoll(kinddeed_ids.at(i)["count"].template get<std::string>());

        kinddeed ent;
        if (!is_kinddeed_exist(id, ent))  {
            ctx->error("kinddeed " + id + " is not exist .");
            return ;
        }

        calced_amount += ent.price() * count ;
    }

    //由于可能存在善举价格浮动，实际价格可能高于或低于开始制作订单的总价格。
    if(calced_amount != std::stod(amount)){ //这个浮点数计算这个地方可能有bug，也可能没有
        ctx->error("delive amount " + amount
                   + ", real amount=" + std::to_string(calced_amount));
        return;
    }

    //如果exchange和order表有一个不存在此记录。则删除另外一个表的这个记录。
    exchange ex;
    order od;
    if (!is_order_exist(orderid, od) || !is_exchange_exist(orderid, ex)) {
        delete_exchange_record(orderid);
        delete_order_record(orderid);
    }

    //如果都存在，直接返回。
    exchange ex1;
    order od1;
    if (is_exchange_exist(orderid,ex1) && is_order_exist(orderid, od1))  {
        ctx->error("exchange " + orderid + " is exist .");
        return ;
    }

    //处理 order 和 kinddeed
    for(int i = 0 ; i < kinddeed_ids.size() ; i++) {
        std::string id = kinddeed_ids.at(i)["id"].template get<std::string>();
        int64_t count = std::stoll(kinddeed_ids.at(i)["count"].template get<std::string>());

        kinddeed prod;
        if (!is_kinddeed_exist(id, prod))  {
            ctx->error("kinddeed " + id + " is not exist .");
            return ;
        }

        //kinddeed产品个数减去count个
        delete_kinddeed_record(id);
        prod.set_count(prod.count()-count);
        get_kinddeed_table().put(prod);


        order od;
        od.set_id(orderid.c_str());
        od.set_kinddeedid(prod.id().c_str());
        od.set_kinddeedname(prod.name().c_str());
        od.set_kinddeeddesc(prod.desc().c_str());
        od.set_kinddeedprice(prod.price());
        od.set_kinddeedcount(count);
        get_order_table().put(od);
    }

    //存储exchange记录
    exchange ent;
    ent.set_orderid(orderid.c_str());
    ent.set_kinddeeds(kinddeeds.c_str());
    ent.set_amount(calced_amount);
    ent.set_timestamp(timestamp.c_str());
    get_exchange_table().put(ent);
    
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
        ctx->ok(ctx->initiator() + " is already founder .");
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


namespace ruler_founder_master_user{}

void Buddha::find_kinddeed() {       

    const std::string& id = ctx->arg("id");
    kinddeed ent;
    if (!is_kinddeed_exist(id, ent))  {
        ctx->ok("kinddeed " + id + " is not exist .");
        return ;
    }

    ctx->ok("found kinddeed " + ent.to_string());
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

// 法师或寺院
DEFINE_METHOD(Buddha, apply_online_kinddeed)   { self.apply_online_kinddeed();   }
DEFINE_METHOD(Buddha, apply_offline_kinddeed)    { self.apply_offline_kinddeed();    }
DEFINE_METHOD(Buddha, upload_kinddeed_proof)    { self.upload_kinddeed_proof();    }

// 用户
DEFINE_METHOD(Buddha, apply_master)            { self.apply_master();            }
DEFINE_METHOD(Buddha, pray_kinddeed)            { self.pray_kinddeed();            }

// 用户和法师
DEFINE_METHOD(Buddha, apply_founder)      { self.apply_founder();            }

// 基金会成员 和 法师或寺院 和 用户
DEFINE_METHOD(Buddha, find_kinddeed)   { self.find_kinddeed();   }

// 基金会成员 和 法师或寺院
DEFINE_METHOD(Buddha, add_kinddeed)    { self.add_kinddeed();    }
DEFINE_METHOD(Buddha, delete_kinddeed)    { self.delete_kinddeed();    }
DEFINE_METHOD(Buddha, update_kinddeed) { self.update_kinddeed(); }
