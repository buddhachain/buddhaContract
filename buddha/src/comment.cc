#include "comment.h"

string commentlabel::to_string() {
    string str ;
    str += "{" ;
    str += std::to_string(id()) + ",";
    str += desc();
    str += "}";
    return str;
}

xchain::json commentlabel::to_json() {
    xchain::json j = {
        {"id", id()},
        {"desc", desc()},
    };

    return j;
}


string beforecomment::to_string() {
    string str ;
    str += "{" ;
    str += owner() + ",";
    str += kdid() + ",";
    str += std::to_string(satisfaction()) + ",";
    str += labels() + ",";
    str += comment() + ",";
    str += timestamp();
    str += "}";
    return str;
}

xchain::json beforecomment::to_json() {
    xchain::json j = {
        {"owner", owner()},
        {"kdid", kdid()},
        {"satisfaction", satisfaction()},
        {"labels", labels()},
        {"comment", comment()},
        {"timestamp", timestamp()},
    };

    return j;
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

xchain::json aftercomment::to_json() {
    xchain::json j = {
        {"orderid", orderid()},
        {"owner", owner()},
        {"comment", comment()},
        {"timestamp", timestamp()},
    };

    return j;
}
