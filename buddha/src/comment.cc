#include "comment.h"

string commentlabel::to_string() {
    string str ;
    str += "{" ;
    str += std::to_string(id()) + ",";
    str += desc();
    str += "}";
    return str;
}


string beforecomment::to_string() {
    string str ;
    str += "{" ;
    str += owner() + ",";
    str += kdid() + ",";
    str += std::to_string(satisfaction()) + ",";
    str += labels() + ",";
    str += comment();
    str += timestamp();
    str += "}";
    return str;
}

string aftercomment::to_string() {
    string str ;
    str += "{" ;
    str += orderid() + ",";
    str += owner() + ",";
    str += comment();
    str += timestamp();
    str += "}";
    return str;
}
