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
    str += memberid() + ",";
    str += kdid() + ",";
    str += to_string(satisfaction()) + ",";
    str += labels();
    str += "}";
    return str;
}

string aftercomment::to_string() {
    string str ;
    str += "{" ;
    str += memberid() + ",";
    str += orderid() + ",";
    str += comment();
    str += "}";
    return str;
}
