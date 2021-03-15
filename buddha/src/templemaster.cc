#include "templemaster.h"

string templemaster::to_string() {
    string str ;
    str += "{" ;
    str += templeid() + ",";
    str += masterid() + ",";
    str += std::to_string(approved());
    str += "}";
    return str;
}

xchain::json templemaster::to_json() {
    xchain::json j = {
        {"templeid", templeid()},
        {"masterid", masterid()},
        {"approved", approved()},
    };

    return j;
}
