#include "kinddeed.h"

std::string kinddeed::to_string() {
    std::string str ;
    str += "{" ;
    str += id() + ",";
    str += name() + ",";
    str += owner() + ",";
    str += desc() + ",";
    str += lasttime() + ",";
    str += std::to_string(applied()) + ",";
    str += std::to_string(online()); 
    str += "}";
    return str;
}

std::string kinddeeddetail::to_string() {
    std::string str ;
    str += "{" ;
    str += kdid() + ",";
    str += std::to_string(sequence()) + ",";
    str += hash();
    str += "}";
    return str;
}

std::string kinddeedspec::to_string() {
    std::string str ;
    str += "{" ;
    str += kdid() + ",";
    str += std::to_string(sequence()) + ",";
    str += desc() + ",";
    str += std::to_string(price());
    str += "}";
    return str;
}
