#include "templemaster.h"

std::string templemaster::to_string() {
    std::string str ;
    str += "{" ;
    str += templeid() + ",";
    str += masterid() + ",";
    str += std::to_string(approved());
    str += "}";
    return str;
}
