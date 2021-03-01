#include "temple.h"

std::string temple::to_string() {
    std::string str ;
    str += "{" ;
    str += id() + ",";
    str += unit() + ",";
    str += creditcode() + ",";
    str += address() + ",";
    str += deedplaceproof() + ",";
    str += std::to_string(approved());
    str += "}";
    return str;
}
