#include "comment.h"

std::string commentlabel::to_string() {
    std::string str ;
    str += "{" ;
    str += id() + ",";
    str += desc();
    str += "}";
    return str;
}


std::string beforecomment::to_string() {
    std::string str ;
    str += "{" ;
    str += memberid() + ",";
    str += kdid() + ",";
    str += std::to_string(satisfaction()) + ",";
    str += labels();
    str += "}";
    return str;
}

std::string aftercomment::to_string() {
    std::string str ;
    str += "{" ;
    str += memberid() + ",";
    str += orderid() + ",";
    str += comment();
    str += "}";
    return str;
}
