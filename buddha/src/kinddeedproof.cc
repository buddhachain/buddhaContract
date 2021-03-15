#include "kinddeedproof.h"


string kinddeedproof::to_string() {
    string str ;
    str += "{" ;
    str += orderid() + ",";
    str += owner() + ",";
    str += proof() + ",";
    str += timestamp() + ",";
    str += std::to_string(approved());
    str += "}";
    return str;
}

xchain::json kinddeedproof::to_json() {
    xchain::json j = {
        {"orderid", orderid()},
        {"owner", owner()},
        {"proof", proof()},
        {"timestamp", timestamp()},
        {"approved", approved()},
    };

    return j;
}
