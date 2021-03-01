#include "kinddeed.h"

string kinddeed::to_string() {
    string str ;
    str += "{" ;
    str += id() + ",";
    str += name() + ",";
    str += owner() + ",";
    str += lasttime() + ",";
    str += std::to_string(applied()) + ",";
    str += std::to_string(online()); 
    str += "}";
    return str;
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
