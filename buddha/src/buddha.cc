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

class Buddha : public xchain::Contract {
public:
    Buddha(): _product(context(),  "product"),
                _order(context(),    "order"),
                _exchange(context(), "exchange"),
                ctx(context()) {}

    // 1. rowkey can not be same with index
    class product: public buddha::Product {
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
            str += lasttime();
            str += "}";
            return str;
        }

        void find();
        void add();
        void del();
        void update();
        void scan();

    };

    class order: public buddha::Order {
        DEFINE_ROWKEY(id);
        DEFINE_INDEX_BEGIN(1)
            DEFINE_INDEX_ADD(0, id)
        DEFINE_INDEX_END();
    };

    class exchange: public buddha::Exchange {
        DEFINE_ROWKEY(order_id);
        DEFINE_INDEX_BEGIN(1)
            DEFINE_INDEX_ADD(0, order_id)
        DEFINE_INDEX_END();
    };

private:
    xchain::cdt::Table<product>  _product;
    xchain::cdt::Table<order>    _order;
    xchain::cdt::Table<exchange> _exchange;
    xchain::Context* ctx;

public:
    decltype(_product)& get_product() {
        return _product;
    }

    decltype(_order)& get_order() {
        return _order;
    }

    decltype(_exchange)& get_exchange() {
        return _exchange;
    }

    void initialize();

    //处理产品
    void product_find();
    void product_add();
    void product_del();
    void product_update();
    void product_scan();

    //对外接口
    void buy();
    void repeal_buy();

private:
     bool is_deployer_operate();
     bool is_product_exist(const std::string& id,product& ent);
     bool is_order_exist(const std::string& id,order& ent);
     bool is_exchange_exist(const std::string& id,exchange& ent);

};

bool Buddha::is_deployer_operate() {
    std::string deployer;
    if (!ctx->get_object("deployer", &deployer)) {
        ctx->error("contrace error, unknown deployer");
        return false;
    }

    if (deployer != ctx->initiator() ) {
        ctx->error("deployer=" + deployer + ", caller=" + ctx->initiator());
        return false;
    }

    return true ;
}


bool Buddha::is_product_exist(const std::string& id,product& ent) {
    if (!get_product().find({{"id", id}}, &ent))
        return false;

    return true;
}

bool Buddha::is_order_exist(const std::string& id,order& ent) {
    if (!get_order().find({{"id", id}}, &ent))
        return false;

    return true;
}

bool Buddha::is_exchange_exist(const std::string& id,exchange& ent) {
    if (!get_exchange().find({{"id", id}}, &ent))
        return false;

    return true;
}

void Buddha::initialize() {
    ctx->put_object("deployer", ctx->initiator());
    ctx->emit_event("initialize", ctx->initiator());
    ctx->ok("deployer=" + ctx->initiator());
}

void Buddha::product_find() {
    if(!is_deployer_operate())
        return ;

    const std::string& id = ctx->arg("id");
    product ent;
    if (!is_product_exist(id, ent))  {
        ctx->ok("product " + id + " not exist .");
        return ;
    }

    ctx->ok("ok -> " + ent.to_string());
}

void Buddha::product_add() {
    if(!is_deployer_operate())
        return ;

    const std::string& id = ctx->arg("id");

    //加锁
    product ent;
    if (is_product_exist(id, ent))  {
        ctx->error("product " + id + "," + ctx->arg("name") + " exist .");
        return ;
    }

    ent.set_id(id.c_str());
    ent.set_name(ctx->arg("name").c_str());
    ent.set_desc(ctx->arg("desc").c_str());
    ent.set_price(std::stod(ctx->arg("price")));
    ent.set_count(std::stoll(ctx->arg("count")));
    ent.set_lasttime(ctx->arg("lasttime").c_str());

    get_product().put(ent);
    //解锁

    ctx->ok(ent.to_string());
}

void Buddha::product_del() {
    if(!is_deployer_operate())
        return ;

    const std::string& id = ctx->arg("id");

    //加锁
    product ent;
    if (!is_product_exist(id, ent))  {
        ctx->error("product " + id + " not exist .");
        return ;
    }

    get_product().del(ent);
    //解锁


    ctx->ok(ent.to_string());
}

void Buddha::product_update() {
    if(!is_deployer_operate())
        return ;


    const std::string& id = ctx->arg("id");

    //加锁
    product ent;
    if (!is_product_exist(id, ent))  {
        ctx->error("product " + id + " not exist .");
        return ;
    }

    get_product().del(ent);
    ent.set_id(id.c_str());
    ent.set_name(ctx->arg("name").c_str());
    ent.set_desc(ctx->arg("desc").c_str());
    ent.set_price(std::stod(ctx->arg("price")));
    ent.set_count(std::stoll(ctx->arg("count")));
    ent.set_lasttime(ctx->arg("lasttime").c_str());
    get_product().put(ent);

    // //解锁

    ctx->ok(ent.to_string() + "update success");
}

void Buddha::product_scan() {
    if(!is_deployer_operate())
        return ;

    const std::string& id = ctx->arg("id");

    auto it = get_product().scan({{"id",id}});
    int i = 0;
    std::string re ;
    while(it->next()) {
        Buddha::product ent;
        if (!it->get(&ent))
            break;

        re += ent.to_string();
        i += 1;
    }

    if (it->error()) {
        ctx->ok(it->error(true));
        return ;
    }

    ctx->ok(std::to_string(i) + " -> " + re + " > " + it->error(true));
}

void Buddha::buy() {

    //判断订单是不是已经存在
    const std::string& order_id = ctx->arg("id");
    order od;
    if (is_order_exist(order_id, od))  {
        ctx->error("order " + order_id + " exist .");
        //解锁
        return ;
    }

    //判断订单中的产品部分是否是数组，是否数组为空
    const std::string& products = ctx->arg("products");

    auto product_ids = xchain::json::parse(products);
 
    if (!product_ids.is_array()) {
        ctx->error("field 'products' need to be array .");
        return;
    }
    
    if ( product_ids.empty() || !product_ids.size()) {
        ctx->error("filed 'products' empty .");
        return;
    }
    
    //加锁

    //判断总价格是否跟表中的计算价格相同
    const double& amount = std::stod(ctx->arg("amount"));
    double calced_amount = 0;
    for(int i = 0 ; i < product_ids.size() ; i++) {
        std::string id = product_ids.at(i)["id"].template get<std::string>();
        int64_t count = std::stoll(product_ids.at(i)["count"].template get<std::string>());

        product ent;
        if (!is_product_exist(id, ent))  {
            ctx->error("product " + id + " not exist .");
            //解锁
            return ;
        }

        calced_amount += ent.price() * count ;
    }

    double c = calced_amount-amount;
    if(abs(c)>0.000001){
        ctx->error("delive amount " + std::to_string(amount)
                   + ", real amount=" + std::to_string(calced_amount));
        //解锁
        return;
    }

    //处理 order 和 product
    for(int i = 0 ; i < product_ids.size() ; i++) {
        std::string id = product_ids.at(i)["id"].template get<std::string>();
        int64_t count = std::stoll(product_ids.at(i)["count"].template get<std::string>());

        product prod;
        if (!is_product_exist(id, prod))  {
            ctx->error("product " + id + " not exist .");
            //解锁
            return ;
        }

        //product产品个数减去count个
        get_product().del(prod);
        prod.set_count(prod.count()-count);
        get_product().put(prod);


        order od;
        od.set_id(order_id.c_str());
        od.set_product_id(prod.id().c_str());
        od.set_product_name(prod.name().c_str());
        od.set_product_desc(prod.desc().c_str());
        od.set_product_price(prod.price());
        od.set_product_count(count);
        get_order().put(od);
    }


    //存储exchange记录
    exchange ex;
    ex.set_order_id(order_id.c_str());
    ex.set_products(products.c_str());
    ex.set_amount(calced_amount);
    ex.set_timestamp(ctx->arg("timestamp"));
    get_exchange().put(ex);
    
    //外部转账    
    
    //解锁

    ctx->ok("ok -> " + std::to_string(calced_amount));
}

void Buddha::repeal_buy() {
    //判断订单是不是已经存在
    const std::string& order_id = ctx->arg("id");
    order od;
    if (!is_order_exist(order_id, od))  {
        ctx->error("order " + order_id + " is not exist .");
        //解锁
        return ;
    }

    //判断订单中的产品部分是否是数组，是否数组为空
    const std::string& products = ctx->arg("products");

    auto product_ids = xchain::json::parse(products);
 
    if (!product_ids.is_array()) {
        ctx->error("field 'products' need to be array .");
        return;
    }
    
    if ( product_ids.empty() || !product_ids.size()) {
        ctx->error("filed 'products' empty .");
        return;
    }
    
    //加锁

    //判断总价格是否跟表中的计算价格相同
    const double& amount = std::stod(ctx->arg("amount"));
    double calced_amount = 0;
    for(int i = 0 ; i < product_ids.size() ; i++) {
        std::string id = product_ids.at(i)["id"].template get<std::string>();
        int64_t count = std::stoll(product_ids.at(i)["count"].template get<std::string>());

        product ent;
        if (!is_product_exist(id, ent))  {
            ctx->error("product " + id + " not exist .");
            //解锁
            return ;
        }

        calced_amount += ent.price() * count ;
    }

    double c = calced_amount-amount;
    if(abs(c)>0.000001){
        ctx->error("delive amount " + std::to_string(amount)
                   + ", real amount=" + std::to_string(calced_amount));
        //解锁
        return;
    }

    //处理 order 和 product
    for(int i = 0 ; i < product_ids.size() ; i++) {
        std::string id = product_ids.at(i)["id"].template get<std::string>();
        int64_t count = std::stoll(product_ids.at(i)["count"].template get<std::string>());

        product prod;
        if (!is_product_exist(id, prod))  {
            ctx->error("product " + id + " not exist .");
            //解锁
            return ;
        }

        //product产品个数减去count个
        get_product().del(prod);
        prod.set_count(prod.count()-count);
        get_product().put(prod);


        order od;
        od.set_id(order_id.c_str());
        od.set_product_id(prod.id().c_str());
        od.set_product_name(prod.name().c_str());
        od.set_product_desc(prod.desc().c_str());
        od.set_product_price(prod.price());
        od.set_product_count(count);
        get_order().put(od);
    }


    //存储exchange记录
    exchange ex;
    ex.set_order_id(order_id.c_str());
    ex.set_products(products.c_str());
    ex.set_amount(calced_amount);
    ex.set_timestamp(ctx->arg("timestamp"));
    get_exchange().put(ex);
    
    //外部转账    
    
    //解锁

    ctx->ok("ok -> " + std::to_string(calced_amount));
}

//初始化
DEFINE_METHOD(Buddha, initialize)     { self.initialize();     }
DEFINE_METHOD(Buddha, product_find)   { self.product_find();   }
DEFINE_METHOD(Buddha, product_add)    { self.product_add();    }
DEFINE_METHOD(Buddha, product_del)    { self.product_del();    }
DEFINE_METHOD(Buddha, product_update) { self.product_update(); }
DEFINE_METHOD(Buddha, product_scan)   { self.product_scan();   }
DEFINE_METHOD(Buddha, buy)            { self.buy();            }
DEFINE_METHOD(Buddha, repeal_buy)     { self.repeal_buy();     }