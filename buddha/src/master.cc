#include "master.h"

std::string master::to_string() {
    std::string str ;
    str += "{" ;
    str += id() + ",";
    str += unit() + ",";
    str += creditcode() + ",";
    str += address() + ",";
    str += deedplaceproof() + ",";
    str += std::to_string(approved()) + ",";
    str += approvedproof();
    str += "}";
    return str;
}
