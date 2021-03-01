#include "kinddeed.h"

string kinddeed::to_string() {
    string str ;
    str += "{" ;
    str += id() + ",";
    str += name() + ",";
    str += owner() + ",";
    str += desc() + ",";
    str += lasttime() + ",";
    str += to_string(applied()) + ",";
    str += to_string(online()); 
    str += "}";
    return str;
}

string kinddeeddetail::to_string() {
    string str ;
    str += "{" ;
    str += kdid() + ",";
    str += to_string(sequence()) + ",";
    str += hash();
    str += "}";
    return str;
}

string kinddeedspec::to_string() {
    string str ;
    str += "{" ;
    str += kdid() + ",";
    str += to_string(sequence()) + ",";
    str += desc() + ",";
    str += to_string(price());
    str += "}";
    return str;
}
