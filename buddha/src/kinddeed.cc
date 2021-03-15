#include "kinddeed.h"

string kinddeedtype::to_string() {
    string str ;
    str += "{" ;
    str += std::to_string(id()) + ",";
    str += desc();
    str += "}";
    return str;
}


xchain::json kinddeedtype::to_json() {
    xchain::json j = {
        {"id", id()},
        {"desc", desc()},
    };

    return j;
}

string kinddeed::to_string() {
    string str ;
    str += "{" ;
    str += id() + ",";
    str += name() + ",";
    str += owner() + ",";
    str += std::to_string(type()) + ",";
    str += lasttime() + ",";
    str += std::to_string(applied()) + ",";
    str += std::to_string(online()); 
    str += "}";
    return str;
}

xchain::json kinddeed::to_json() {
    xchain::json j = {
        {"id", id()},
        {"name", name()},
        {"owner", owner()},
        {"type", type()},
        {"lasttime", lasttime()},
        {"applied", applied()},
        {"online", online()},
    };

    return j;
}

string kinddeeddetail::to_string() {
    string str ;
    str += "{" ;
    str += kdid() + ",";
    str += std::to_string(sequence()) + ",";
    str += hash();
    str += "}";
    return str;
}

xchain::json kinddeeddetail::to_json() {
    xchain::json j = {
        {"kdid", kdid()},
        {"sequence", sequence()},
        {"hash", hash()},
    };

    return j;
}

string kinddeedspec::to_string() {
    string str ;
    str += "{" ;
    str += kdid() + ",";
    str += std::to_string(sequence()) + ",";
    str += desc() + ",";
    str += std::to_string(price());
    str += "}";
    return str;
}

xchain::json kinddeedspec::to_json() {
    xchain::json j = {
        {"kdid", kdid()},
        {"sequence", sequence()},
        {"desc", desc()},
        {"price", price()},
    };

    return j;
}
