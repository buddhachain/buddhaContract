#include "master.h"

string master::to_string() {
    string str ;
    str += "{" ;
    str += id() + ",";
    str += creditcode() + ",";
    str += proof() + ",";
    str += std::to_string(approved());
    str += "}";
    return str;
}

xchain::json kinddeedproof::to_json() {
    xchain::json j = {
        {"id", id()},
        {"creditcode", creditcode()},
        {"proof", proof()},
        {"approved", approved()},
    };

    return j;
}
