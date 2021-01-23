#include <inttypes.h>
#include "xchain/xchain.h"
#include "xchain/table/types.h"
#include "xchain/table/table.tpl.h"
#include "exchange.pb.h"

//data mytableing
struct Exchange : public xchain::Contract {
public:
    Exchange():
        _product(this->context(), "product")，
        _order(this->context(), "order")
        _exchange(this->context(), "exchange") {}

    // 1. rowkey can not be same with index
    struct product: public exchange::Product {
        DEFINE_ROWKEY(id);
        DEFINE_INDEX_BEGIN(1)
            DEFINE_INDEX_ADD(0, id)
        DEFINE_INDEX_END();
    };

    struct order: public exchange::Order {
        DEFINE_ROWKEY(id);
        DEFINE_INDEX_BEGIN(1)
            DEFINE_INDEX_ADD(0, id)
        DEFINE_INDEX_END();
    };

    struct exchange: public exchange::Exchange {
        DEFINE_ROWKEY(id);
        DEFINE_INDEX_BEGIN(1)
            DEFINE_INDEX_ADD(0, id)
        DEFINE_INDEX_END();
    };
private:
    xchain::cdt::Table<product>  _product;
    xchain::cdt::Table<order>    _order;
    xchain::cdt::Table<exchange> _exchange;

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
};

//初始化
DEFINE_METHOD(Exchange, initialize) {
    xchain::Context* ctx = self.context();
    ctx->put_object("deployer", ctx->initiator());
    ctx->emit_event("initialize", ctx->initiator());
    ctx->ok("deployer=" + ctx->initiator());
}

bool is_deployer_operate(xchain::Context* ctx) {
    std::string deployer;
    if (!ctx->get_object("deployer", &deployer)) {
        ctx->error("contrace error, unknown deplory");
        return false;
    }

    if (deployer != ctx->initiator() ) {
        ctx->error("deployer=" + deployer + ", caller=" + ctx->initiator());
        return false;
    }

    return true ;
}

bool is_product_exist(xchain::Context* ctx,
std::string&) {

    return true;
}

DEFINE_METHOD(Exchange, productfind) {
    xchain::Context* ctx = self.context();

    if(!is_deployer_operate(ctx))
        return ;

    const std::string& id = ctx->arg("id");
    Exchange::product ent;
    if (!self.get_product().find({{"id", id}}, &ent))  {
        ctx->error("can not find " + id);
        return ;
    }
        
    std::string re ;
    {
        re += "{" ;
        re += ent.id() + ",";
        re += ent.name() + ",";
        re += ent.desc() + ",";
        re += ent.price() + ",";
        re += ent.amount() + ",";
        re += ent.time() + ",";
        re += "}";
    }
    ctx->ok("ok -> " + re);
}

DEFINE_METHOD(Exchange, productadd) {
    xchain::Context* ctx = self.context();

    if(!is_deployer_operate(ctx))
        return ;

    const std::string& id = ctx->arg("id");
    Exchange::product ent;
    if (self.get_product().find({{"id", id}}, &ent))  {
        ctx->error("the product " + ctx->arg("id") + "," + ctx->arg("name") + " exist .");
        return ;
    }

    const std::string& id= ctx->arg("id");
    const std::string& name = ctx->arg("name");
    const std::string& desc = ctx->arg("desc");
    const std::string& price = ctx->arg("price");
    const std::string& amount = ctx->arg("amount");
    const std::string& time = ctx->arg("time");


    Exchange::product ent;
    ent.set_id(id.c_str());
    ent.set_name(name.c_str());
    ent.set_desc(desc.c_str());
    ent.set_price(price.c_str());
    ent.set_amount(amount.c_str());
    ent.set_time(time.c_str());
    self.get_product().put(ent);

    std::string re ;
    {
        re += "{" ;
        re += ent.id() + ",";
        re += ent.name() + ",";
        re += ent.desc() + ",";
        re += ent.price() + ",";
        re += ent.amount() + ",";
        re += ent.time() + ",";
        re += "} add success";
    }

    ctx->ok(re);
}

DEFINE_METHOD(Exchange, productdel) {
    xchain::Context* ctx = self.context();

    if(!is_deployer_operate(ctx))
        return ;

    const std::string& id = ctx->arg("id");
    Exchange::product ent;
    if (!self.get_product().find({{"id", id}}, &ent))  {
        ctx->error("can not find " + id);
        return ;
    }

    self.get_product().del(ent);

    std::string re ;
    {
        re += "{" ;
        re += ent.id() + ",";
        re += ent.name() + ",";
        re += ent.desc() + ",";
        re += ent.price() + ",";
        re += ent.amount() + ",";
        re += ent.time() + ",";
        re += "} del success";
    }
    ctx->ok(re);
}

DEFINE_METHOD(Exchange, productupdate) {
    xchain::Context* ctx = self.context();

    if(!is_deployer_operate(ctx))
        return ;

    const std::string& id = ctx->arg("id");
    Exchange::product oldproduct;
    if (!self.get_product().find({{"id", id}}, &oldproduct))  {
         ctx->error("can not find product " + id);
        return ;
    }

    //此处需要加锁

    self.get_product().del(oldproduct);

    const std::string& id= ctx->arg("id");
    const std::string& name = ctx->arg("name");
    const std::string& desc = ctx->arg("desc");
    const std::string& price = ctx->arg("price");
    const std::string& amount = ctx->arg("amount");
    const std::string& time = ctx->arg("time");


    Exchange::product newproduct;
    newproduct.set_id(id.c_str());
    newproduct.set_name(name.c_str());
    newproduct.set_desc(desc.c_str());
    newproduct.set_price(price.c_str());
    newproduct.set_amount(amount.c_str());
    newproduct.set_time(time.c_str());
    self.get_product().put(newproduct);

    //此处需要解锁 

    std::string re ;
    {
        re += "{" ;
        re += newproduct.id() + ",";
        re += newproduct.name() + ",";
        re += newproduct.desc() + ",";
        re += newproduct.price() + ",";
        re += newproduct.amount() + ",";
        re += newproduct.time() + ",";
        re += "} update success";
    }

    ctx->ok(re);
}

DEFINE_METHOD(Exchange, productscan) {
    xchain::Context* ctx = self.context();

    if(!is_deployer_operate(ctx))
        return ;

    const std::string& id = ctx->arg("id");
    
    auto it = self.get_product().scan({{"id",id}});
    int i = 0;
    std::string re ;
    while(it->next()) {
        Exchange::product ent;
        if (!it->get(&ent))
            break;


        std::string str ;
        {
            str += "{" ;
            str += ent.id() + ",";
            str += ent.name() + ",";
            str += ent.desc() + ",";
            str += ent.price() + ",";
            str += ent.amount() + ",";
            str += ent.time() + ",";
            str += "} ";
        }

        re += str;
        i += 1;
    }

    if (it->error()) {
        ctx->ok(it->error(true));
        return ;
    }
        
    ctx->ok(std::to_string(i) + " -> " + re + " > " + it->error(true));
}

DEFINE_METHOD(Exchange, buy) {
    xchain::Context* ctx = self.context();

    const std::string& productid = ctx->arg("productid");

    const std::string& id = ctx->arg("id");
    Exchange::product ent;
    if (!self.get_product().find({{"id", id}}, &ent))  {
        ctx->error("can not find product " + id);
        return ;
    }

    std::string re ;
    {
        re += "{" ;
        re += ent.id() + ",";
        re += ent.name() + ",";
        re += ent.desc() + ",";
        re += ent.price() + ",";
        re += ent.amount() + ",";
        re += ent.time() + ",";
        re += "}";
    }
    ctx->ok("ok -> " + re);
}
