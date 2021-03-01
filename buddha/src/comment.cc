#include "comment.h"

string commentlabel::to_string() {
    string str ;
    str += "{" ;
    str += id() + ",";
    str += desc();
    str += "}";
    return str;
}


string beforecomment::to_string() {
    string str ;
    str += "{" ;
    str += userid() + ",";
    str += kdid() + ",";
    str += std::to_string(satisfaction()) + ",";
    str += labels();
    str += "}";
    return str;
}

string aftercomment::to_string() {
    string str ;
    str += "{" ;
    str += userid() + ",";
    str += orderid() + ",";
    str += comment();
    str += "}";
    return str;
}
