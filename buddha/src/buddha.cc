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
        str += std::to_string(amount()) + ",";
        str += std::to_string(isyet());
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
        str += std::to_string(isyet());
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
        str += timestamp();
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
        str += desc() + ",";
        str += std::to_string(price()) + ",";
        str += std::to_string(count()) + ",";
        str += lasttime() + ",";
        str += isonline() ;        
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


    void delete_order_record(const std::string& id);
    void delete_exchage_record(const std::string& id);
    void sync_exchange_order(const std::string& id);

public:
    //部署者
    void initialize();
    //update无对应函数
    void authorize_founder();
    void recusal_founder();

    //基金会成员
    void authorize_master();
    void recusal_master();
    void authorize_online_kinddeed();
    void authorize_offline_kinddeed();
    void authorize_kinddeed_proof();


    //法师
    void apply_online_kinddeed();
    void apply_offline_kinddeed();
    void upload_kinddeed_proof();

    //用户
    void apply_tobe_master();
    void buy_kinddeed();

    //用户和法师共同
    void apply_tobe_founder();

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
    
    if( ent.isyet() != true ) 
        return false;

    return true;
}

bool Buddha::is_master(const std::string& name) {
    master ent;
    if (!is_master_exist(name, ent))
        return false;
    
    if( ent.isyet() != true ) 
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

void Buddha::delete_order_record(const std::string& id) {
    
    order ex;
    while (is_order_exist(id, ex))  {
        get_order_table().del(ex);

        std::string str ;
        str += "delete order " + id + " order table";
        ctx->logf(str.c_str());
    }
}

void Buddha::delete_exchage_record(const std::string& id) {
    exchange ex;

    while (is_exchange_exist(id, ex))  {
        get_exchange_table().del(ex);

        std::string str ;
        str += "delete order " + id + " exchange table";
        ctx->logf(str.c_str());
    }
}

void Buddha::sync_exchange_order(const std::string& id) {
    exchange ex;
    order od;
    if (!is_order_exist(id, od) && 
        !is_exchange_exist(id, ex))
        return ;

    delete_exchage_record(id);
    delete_order_record(id);
}

namespace deployer{}
void Buddha::initialize() {
    ctx->put_object("deployer", ctx->initiator());
    ctx->emit_event("initialize", ctx->initiator());
    ctx->ok("deployer=" + ctx->initiator() + " success");
}

void Buddha::authorize_founder() {
    const std::string& name = ctx->arg("name");
    if(name.empty()) {
        ctx->error("founder name is empty");
        return ;
    }

    if(!is_deployer()) {
        ctx->error(ctx->initiator() + " is not deployer, has no authority to authorize founder .");
        return ;
    }

    founder ent;
    if(!is_founder_exist(name,ent)) {
        ctx->error("founder " + name + " not exist .");
        return ;
    }

    if(is_founder(name)) {
        ctx->ok(name + " is founder already.");
        return ;
    }

    ent.set_isyet(true);
    get_founder_table().del(ent);
    get_founder_table().put(ent);

    ctx->ok("authorize founder "+ name + " success .");
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
        ctx->error("founder " + name + " not exist .");
        return ;
    }

    if(is_founder(name)) {
        ctx->error(name + " is founder already .");
        return ;
    }

    ent.set_isyet(false);
    get_founder_table().del(ent);
    get_founder_table().put(ent);

    ctx->ok("recusal founder "+ name + " success .");
}

namespace ruler_founder{}

void Buddha::authorize_master() {
    const std::string& name = ctx->arg("name");
    if(name.empty()) {
        ctx->error("master name is empty");
        return ;
    }

    if(!is_founder()) {
        ctx->error(ctx->initiator() + " is not founder, has no authority to authorize master .");
        return ;
    }

    master ent;
    if(!is_master_exist(name,ent)) {
        ctx->error("master " + name + " not exist .");
        return ;
    }

    if(is_master(name)) {
        ctx->ok(name + " is master already.");
        return ;
    }

    ent.set_isyet(true);
    get_master_table().del(ent);
    get_master_table().put(ent);

    ctx->ok("authorize master "+ name + " success .");
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
        ctx->error("master " + name + " not exist .");
        return ;
    }

    if(!is_master(name)) {
        ctx->ok(name + " is not master .");
        return ;
    }

    ent.set_isyet(false);
    get_master_table().del(ent);
    get_master_table().put(ent);

    ctx->ok("recusal master "+ name + " success .");
}

void Buddha::authorize_online_kinddeed() {
    const std::string& id = ctx->arg("id");
    if(id.empty()) {
        ctx->error("kinddeed id is empty");
        return ;
    }

    if(!is_founder()) {
        ctx->error(ctx->initiator() + " is not founder, has no authority to authorize online kinddeed .");
        return ;
    }


    kinddeed ent;
    if (!is_kinddeed_exist(id, ent))  {
        ctx->error("kinddeed " + id + " not exist .");
        return ;
    }

    get_kinddeed_table().del(ent);
    ent.set_isonline(true);
    get_kinddeed_table().put(ent);

    ctx->ok("authorize kinddeed "+ ent.to_string() + " online success .");
}

void Buddha::authorize_offline_kinddeed() {
    const std::string& id = ctx->arg("id");
    if(id.empty()) {
        ctx->error("kinddeed id is empty");
        return ;
    }

    if(!is_founder()) {
        ctx->error(ctx->initiator() + " is not founder, has no authority to authorize offline kinddeed .");
        return ;
    }

    kinddeed ent;
    if (!is_kinddeed_exist(id, ent))  {
        ctx->error("kinddeed " + id + " not exist .");
        return ;
    }

    get_kinddeed_table().del(ent);
    ent.set_isonline(false);
    get_kinddeed_table().put(ent);

    ctx->ok("authorize kinddeed "+ ent.to_string() + " offline success .");
}

void Buddha::authorize_kinddeed_proof() {
    const std::string& order_id = ctx->arg("orderid");
    if(order_id.empty()) {
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

    if(!is_founder()) {
        ctx->error(ctx->initiator() + " is not founder, has no authority to authorize kinddeed proof .");
        return ;
    }

    kinddeedproof ent;
    if (is_kinddeed_proof_exist(order_id, ent))  {
        ctx->ok("kinddeed proof " + order_id + " is exist .");
        return ;
    }

    sync_exchange_order(order_id);

    order od;
    if (!is_order_exist(order_id, od))  {
        ctx->error("order " + order_id + " is not exist .");
        return ;
    }

    ent.set_orderid(order_id.c_str());
    ent.set_proof(proof.c_str());
    ent.set_timestamp(timestamp.c_str());
    get_kinddeed_proof_table().put(ent);

    ctx->ok("authorize kinddeed "+ ent.to_string() + " proof success .");
}

namespace ruler_master{}
void Buddha::apply_online_kinddeed() {
    const std::string& id = ctx->arg("id");
    if(id.empty()) {
        ctx->error("kinddeed id is empty");
        return ;
    }

    if(!is_master()) {
        ctx->error(ctx->initiator() + " is not master, has no authority to apply online kinddeed .");
        return ;
    }
    
}

void Buddha::apply_offline_kinddeed() {
    if(!is_master()) {
        ctx->error(ctx->initiator() + " is not master, has no authority to apply offline kinddeed .");
        return ;
    }
}

void Buddha::upload_kinddeed_proof() {
    if(!is_master()) {
        ctx->error(ctx->initiator() + " is not master, has no authority to upload kinddeed proof .");
        return ;
    }
}


namespace ruler_user{}

void Buddha::apply_tobe_master(){

    
    if(!is_user()) {
        ctx->error(ctx->initiator() + " is not common user, has no authority to apply tobe master .");
        return ;
    }
}

void Buddha::buy_kinddeed() {
    if(!is_user()) {
        ctx->error(ctx->initiator() + " is not common user, has no authority to buy kinddeed .");
        return ;
    }

    //判断订单是不是已经存在
    const std::string& order_id = ctx->arg("id");

    sync_exchange_order(order_id);
         
    order od;
    if (!is_order_exist(order_id, od))  {
        ctx->error("order " + order_id + " is not exist .");
        return ;
    }

    //判断订单中的产品部分是否是数组，是否数组为空
    const std::string& kinddeeds = ctx->arg("kinddeeds");

    auto kinddeed_ids = xchain::json::parse(kinddeeds);
 
    if (!kinddeed_ids.is_array()) {
        ctx->error("field 'kinddeeds' need to be array .");
        return;
    }
    
    if ( kinddeed_ids.empty() || !kinddeed_ids.size()) {
        ctx->error("filed 'kinddeeds' empty .");
        return;
    }
    

    //判断总价格是否跟表中的计算价格相同
    const double& amount = std::stod(ctx->arg("amount"));
    double calced_amount = 0;
    for(int i = 0 ; i < kinddeed_ids.size() ; i++) {
        std::string id = kinddeed_ids.at(i)["id"].template get<std::string>();
        int64_t count = std::stoll(kinddeed_ids.at(i)["count"].template get<std::string>());

        kinddeed ent;
        if (!is_kinddeed_exist(id, ent))  {
            ctx->error("kinddeed " + id + " not exist .");
            return ;
        }

        calced_amount += ent.price() * count ;
    }

    double c = calced_amount-amount;
    if(abs(c)>0.000001){
        ctx->error("delive amount " + std::to_string(amount)
                   + ", real amount=" + std::to_string(calced_amount));
        return;
    }

    //处理 order 和 kinddeed
    for(int i = 0 ; i < kinddeed_ids.size() ; i++) {
        std::string id = kinddeed_ids.at(i)["id"].template get<std::string>();
        int64_t count = std::stoll(kinddeed_ids.at(i)["count"].template get<std::string>());

        kinddeed prod;
        if (!is_kinddeed_exist(id, prod))  {
            ctx->error("kinddeed " + id + " not exist .");
            return ;
        }

        //kinddeed产品个数减去count个
        get_kinddeed_table().del(prod);
        prod.set_count(prod.count()-count);
        get_kinddeed_table().put(prod);


        order od;
        od.set_id(order_id.c_str());
        od.set_kinddeedid(prod.id().c_str());
        od.set_kinddeedname(prod.name().c_str());
        od.set_kinddeeddesc(prod.desc().c_str());
        od.set_kinddeedprice(prod.price());
        od.set_kinddeedcount(count);
        get_order_table().put(od);
    }


    //存储exchange记录
    exchange ex;
    ex.set_orderid(order_id.c_str());
    ex.set_kinddeeds(kinddeeds.c_str());
    ex.set_amount(calced_amount);
    ex.set_timestamp(ctx->arg("timestamp"));
    get_exchange_table().put(ex);
    
    //外部转账    
    
    ctx->ok("ok -> " + std::to_string(calced_amount));
}

namespace ruler_master_user{}
void Buddha::apply_tobe_founder(){
    if(is_user()) {
        ctx->error(ctx->initiator() + " is not master, has no authority to apply tobe founder .");
        return ;
    }
}


namespace ruler_founder_master_user{}

void Buddha::find_kinddeed() {       

    const std::string& id = ctx->arg("id");
    kinddeed ent;
    if (!is_kinddeed_exist(id, ent))  {
        ctx->ok("kinddeed " + id + " not exist .");
        return ;
    }

    ctx->ok("ok -> " + ent.to_string());
}

namespace ruler_founder_master{}

void Buddha::add_kinddeed() {
    if(!is_deployer())
        return ;

    const std::string& id = ctx->arg("id");

    kinddeed ent;
    if (is_kinddeed_exist(id, ent))  {
        ctx->error("kinddeed " + id + "," + ctx->arg("name") + " exist .");
        return ;
    }

    ent.set_id(id.c_str());
    ent.set_name(ctx->arg("name").c_str());
    ent.set_desc(ctx->arg("desc").c_str());
    ent.set_price(std::stod(ctx->arg("price")));
    ent.set_count(std::stoll(ctx->arg("count")));
    ent.set_lasttime(ctx->arg("lasttime").c_str());

    get_kinddeed_table().put(ent);

    ctx->ok(ent.to_string());
}

void Buddha::delete_kinddeed() {
    if(!is_deployer())
        return ;

    const std::string& id = ctx->arg("id");

    kinddeed ent;
    if (!is_kinddeed_exist(id, ent))  {
        ctx->error("kinddeed " + id + " not exist .");
        return ;
    }

    get_kinddeed_table().del(ent);


    ctx->ok(ent.to_string());
}

void Buddha::update_kinddeed() {
    if(!is_deployer())
        return ;

    const std::string& id = ctx->arg("id");

    kinddeed ent;
    if (!is_kinddeed_exist(id, ent))  {
        ctx->error("kinddeed " + id + " not exist .");
        return ;
    }

    get_kinddeed_table().del(ent);
    ent.set_id(id.c_str());
    ent.set_name(ctx->arg("name").c_str());
    ent.set_desc(ctx->arg("desc").c_str());
    ent.set_price(std::stod(ctx->arg("price")));
    ent.set_count(std::stoll(ctx->arg("count")));
    ent.set_lasttime(ctx->arg("lasttime").c_str());
    get_kinddeed_table().put(ent);

    ctx->ok(ent.to_string() + "update success");
}



// ---------- 对外接口 -------------

// 合约部署者
DEFINE_METHOD(Buddha, initialize)     { self.initialize();     }
DEFINE_METHOD(Buddha, authorize_founder)   { self.authorize_founder();   }
DEFINE_METHOD(Buddha, recusal_founder)    { self.recusal_founder();    }

// 基金会成员
DEFINE_METHOD(Buddha, authorize_master)    { self.authorize_master();    }
DEFINE_METHOD(Buddha, recusal_master)    { self.recusal_master();    }
DEFINE_METHOD(Buddha, authorize_online_kinddeed) { self.authorize_online_kinddeed(); }
DEFINE_METHOD(Buddha, authorize_offline_kinddeed)   { self.authorize_offline_kinddeed();   }
DEFINE_METHOD(Buddha, authorize_kinddeed_proof)   { self.authorize_kinddeed_proof();   }

// 法师或寺院
DEFINE_METHOD(Buddha, apply_online_kinddeed)   { self.apply_online_kinddeed();   }
DEFINE_METHOD(Buddha, apply_offline_kinddeed)    { self.apply_offline_kinddeed();    }
DEFINE_METHOD(Buddha, upload_kinddeed_proof)    { self.upload_kinddeed_proof();    }

// 用户
DEFINE_METHOD(Buddha, apply_tobe_master)            { self.apply_tobe_master();            }
DEFINE_METHOD(Buddha, buy_kinddeed)            { self.buy_kinddeed();            }

// 用户和法师
DEFINE_METHOD(Buddha, apply_tobe_founder)      { self.apply_tobe_founder();            }

// 基金会成员 和 法师或寺院 和 用户
DEFINE_METHOD(Buddha, find_kinddeed)   { self.find_kinddeed();   }

// 基金会成员 和 法师或寺院
DEFINE_METHOD(Buddha, add_kinddeed)    { self.add_kinddeed();    }
DEFINE_METHOD(Buddha, delete_kinddeed)    { self.delete_kinddeed();    }
DEFINE_METHOD(Buddha, update_kinddeed) { self.update_kinddeed(); }
