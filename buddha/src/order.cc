#include "order.h"

string order::to_string() {
    string str ;
    str += "{" ;
    str += id() + ",";
    str += owner() + ",";
    str += kdowner() + ",";
    str += kdid() + ",";
    str += std::to_string(specid()) + ",";
    str += std::to_string(count()) + ",";
    str += std::to_string(amount()) + ",";
    str += timestamp() ;
    str += "}";
    return str;
}

xchain::json kinddeedproof::to_json() {
    xchain::json j = {
        {"id", id()},
        {"owner", owner()},
        {"kdowner", kdowner()},
        {"kdid", kdid()},
        {"specid", specid()},
        {"count", count()},
        {"amount", amount()},
        {"timestamp", timestamp()},
    };

    return j;
}
