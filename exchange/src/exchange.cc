#include <inttypes.h>
#include "xchain/json/json.h"
#include "xchain/xchain.h"
#include "xchain/table/types.h"
#include "xchain/table/table.tpl.h"
#include "exchange.pb.h"

class Exchange : public xchain::Contract {
public:
    Exchange(): _product(context(), "product"),
                _order(context(), "order"),
                _exchange(context(), "exchange") {}

    // 1. rowkey can not be same with index
    struct product: public myexchange::Product {
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
            str += price() + ",";
            str += amount() + ",";
            str += time() + ",";
            str += "}";
            return str;
        }
    };

    struct order: public myexchange::Order {
        DEFINE_ROWKEY(id);
        DEFINE_INDEX_BEGIN(1)
            DEFINE_INDEX_ADD(0, id)
        DEFINE_INDEX_END();
    };

    struct exchange: public myexchange::Exchange {
        DEFINE_ROWKEY(orderid);
        DEFINE_INDEX_BEGIN(1)
            DEFINE_INDEX_ADD(0, orderid)
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

    // void initialize();

    //处理产品
    // void productfind();
    // void productadd();
    // void productdel();
    // void productupdate();
    // void productscan();

    //操作订单

    //对外接口
    // void buy();

private:
    //  bool is_deployer_operate(xchain::Context* ctx);
    //  bool is_product_exist(const xchain::Context* ctx,
    //                        const std::string& id,
    //                        product& ent);

};

// bool Exchange::is_deployer_operate(xchain::Context* ctx) {
//     std::string deployer;
//     if (!ctx->get_object("deployer", &deployer)) {
//         ctx->error("contrace error, unknown deplory");
//         return false;
//     }

//     if (deployer != ctx->initiator() ) {
//         ctx->error("deployer=" + deployer + ", caller=" + ctx->initiator());
//         return false;
//     }

//     return true ;
// }


// bool Exchange::is_product_exist(const xchain::Context* ctx,
//                                 const std::string& id,
//                                 product& ent) {

//     if (!get_product().find({{"id", id}}, &ent))
//         return false;

//     return true;
// }

// void Exchange::initialize() {
//     xchain::Context* ctx = context();
//     ctx->put_object("deployer", ctx->initiator());
//     ctx->emit_event("initialize", ctx->initiator());
//     ctx->ok("deployer=" + ctx->initiator());
// }

DEFINE_METHOD(Exchange, productfind) {

// void Exchange::productfind() {
    xchain::Context* ctx = context();

    // if(!is_deployer_operate(ctx))
    //     return ;

    // const std::string& id = ctx->arg("id");
    // product ent;
    // if (!is_product_exist(ctx, id, ent))  {
    //     ctx->ok("product " + id + " not exist .");
    //     return ;
    // }

    ctx->ok("ok -> ");// + ent.to_string());
}

// void Exchange::productadd() {
//     xchain::Context* ctx = context();

//     if(!is_deployer_operate(ctx))
//         return ;

//     const std::string& id = ctx->arg("id");


//     //加锁
//     product ent;
//     if (is_product_exist(ctx, id, ent))  {
//         ctx->error("product " + ctx->arg("id") + "," + ctx->arg("name") + " exist .");
//         return ;
//     }

//     ent.set_id(ctx->arg("id").c_str());
//     ent.set_name(ctx->arg("name").c_str());
//     ent.set_desc(ctx->arg("desc").c_str());
//     ent.set_price(ctx->arg("price").c_str());
//     ent.set_amount(ctx->arg("amount").c_str());
//     ent.set_time(ctx->arg("time").c_str());

//     get_product().put(ent);
//     //解锁

//     ctx->ok(ent.to_string());
// }

// void Exchange::productdel() {
//     xchain::Context* ctx = context();

//     if(!is_deployer_operate(ctx))
//         return ;

//     const std::string& id = ctx->arg("id");

//     //加锁
//     product ent;
//     if (!is_product_exist(ctx, id, ent))  {
//         ctx->error("product " + id + " not exist .");
//         return ;
//     }

//     get_product().del(ent);
//     //解锁


//     ctx->ok(ent.to_string());
// }

// void Exchange::productupdate() {
//     xchain::Context* ctx = context();

//     if(!is_deployer_operate(ctx))
//         return ;

//     const std::string& id = ctx->arg("id");

//     //加锁
//     product ent;
//     if (!is_product_exist(ctx, id, ent))  {
//          ctx->error("product " + id + " not exist .");
//         return ;
//     }

//     get_product().del(ent);

//     ent.set_id(ctx->arg("id").c_str());
//     ent.set_name(ctx->arg("name").c_str());
//     ent.set_desc(ctx->arg("desc").c_str());
//     ent.set_price(ctx->arg("price").c_str());
//     ent.set_amount(ctx->arg("amount").c_str());
//     ent.set_time(ctx->arg("time").c_str());

//     get_product().put(ent);
//     //解锁

//     ctx->ok(ent.to_string() + "update success");
// }

// void Exchange::productscan() {
//     xchain::Context* ctx = context();

//     if(!is_deployer_operate(ctx))
//         return ;

//     const std::string& id = ctx->arg("id");

//     auto it = get_product().scan({{"id",id}});
//     int i = 0;
//     std::string re ;
//     while(it->next()) {
//         Exchange::product ent;
//         if (!it->get(&ent))
//             break;

//         re += ent.to_string();
//         i += 1;
//     }

//     if (it->error()) {
//         ctx->ok(it->error(true));
//         return ;
//     }

//     ctx->ok(std::to_string(i) + " -> " + re + " > " + it->error(true));
// }

// void Exchange::buy() {
//     xchain::Context* ctx = context();

//     const std::string& order_id = ctx->arg("id");
//     // const std::string& product_size = ctx->arg("product_size");
//     // const std::string& products = ctx->arg("products");
//     ctx->ok("ok -> " + order_id);

//     //设置exchange对象
//     // exchange ex;
//     // ex.set_orderid(order_id.c_str());
//     // ex.set_productsize(product_size.c_str());
//     // ex.set_products(products.c_str());

//     //设置order对象
//     // std::string re ;
//     // auto j = xchain::json::parse(products);
    
//     // for(int i = 0 ; i < j.size() ; i++) {
//     //     re += j[i];
//     // }

//     //设置产品对象
//     // product ent;
//     // if (!is_product_exist(ctx, id, ent))  {
//     //     ctx->error("product " + id + " not exist .");
//     //     return ;
//     // }

//     // ctx->ok("ok -> " + std::to_string(j.size()));
//     ctx->ok("ok -> " + order_id);
// }


//初始化
// DEFINE_METHOD(Exchange, initialize) { initialize(); }
// DEFINE_METHOD(Exchange, productfind) { productfind(); }
// DEFINE_METHOD(Exchange, productadd) { productadd(); }
// DEFINE_METHOD(Exchange, productdel) { productdel(); }
// DEFINE_METHOD(Exchange, productupdate) { productupdate(); }
// DEFINE_METHOD(Exchange, productscan) { productscan(); }
// DEFINE_METHOD(Exchange, buy) { buy(); }