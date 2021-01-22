#include <inttypes.h>
#include "xchain/xchain.h"
#include "xchain/table/types.h"
#include "xchain/table/table.tpl.h"
#include "exchange.pb.h"

//data mytableing
struct Product : public xchain::Contract {
public:
    Product(): _entity(this->context(), "entity") {}

    // 1. rowkey can not be same with index
    struct entity: public exchange::Product {
        DEFINE_ROWKEY(id);
        DEFINE_INDEX_BEGIN(1)
            DEFINE_INDEX_ADD(0, id)
        DEFINE_INDEX_END();
    };
private:
    xchain::cdt::Table<entity> _entity;

public:
    decltype(_entity)& get_entity() {
        return _entity;
    }
};

//初始化
DEFINE_METHOD(Product, initialize) {
    xchain::Context* ctx = self.context();
    ctx->ok(ctx->initiator());
}

DEFINE_METHOD(Product, find) {
    xchain::Context* ctx = self.context();
    const std::string& id = ctx->arg("id");
    Product::entity ent;
    if (!self.get_entity().find({{"id", id}}, &ent))  {
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


DEFINE_METHOD(Product, add) {
    xchain::Context* ctx = self.context();
    const std::string& id= ctx->arg("id");
    const std::string& name = ctx->arg("name");
    const std::string& desc = ctx->arg("desc");
    const std::string& price = ctx->arg("price");
    const std::string& amount = ctx->arg("amount");
    const std::string& time = ctx->arg("time");

    Product::entity ent;
    ent.set_id(id.c_str());
    ent.set_name(name.c_str());
    ent.set_desc(desc.c_str());
    ent.set_price(price.c_str());
    ent.set_amount(amount.c_str());
    ent.set_time(time.c_str());
    self.get_entity().put(ent);

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

DEFINE_METHOD(Product, del) {
    xchain::Context* ctx = self.context();    
    const std::string& id = ctx->arg("id");
    Product::entity ent;
    if (!self.get_entity().find({{"id", id}}, &ent))  {
        ctx->error("can not find " + id);
        return ;
    }

    self.get_entity().del(ent);

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

DEFINE_METHOD(Product, scan) {
    xchain::Context* ctx = self.context();
    const std::string& id = ctx->arg("id");
    
    auto it = self.get_entity().scan({{"id",id}});
    int i = 0;
    std::string re ;
    while(it->next()) {
        Product::entity ent;
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
