#include "founder.h"

string founder::to_string() {
    string str ;
    str += "{" ;
    str += id() + ",";
    str += desc() + ",";
    str += address() + ",";
    str += timestamp() + ",";
    str += std::to_string(guaranty()) + ",";
    str += std::to_string(approved());
    str += "}";
    return str;
}


xchain::json founder::to_json() {
    xchain::json j = {
        {"id", id()},
        {"desc", desc()},
        {"address", address()},
        {"timestamp", timestamp()},
        {"guaranty", guaranty()},
        {"approved", approved()},
    };

    return j;
}
