#include "temple.h"

string temple::to_string() {
    string str ;
    str += "{" ;
    str += id() + ",";
    str += unit() + ",";
    str += creditcode() + ",";
    str += address() + ",";
    str += proof() + ",";
    str += std::to_string(approved());
    str += "}";
    return str;
}

xchain::json temple::to_json() {
    xchain::json j = {
        {"id", id()},
        {"unit", unit()},
        {"creditcode", creditcode()},
        {"address", address()},
        {"proof", proof()},
        {"approved", approved()},
    };

    return j;
}
