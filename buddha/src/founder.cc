#include "founder.h"

std::string founder::to_string() {
    std::string str ;
    str += "{" ;
    str += id() + ",";
    str += desc() + ",";
    str += std::to_string(guaranty()) + ",";
    str += std::to_string(approved());
    str += "}";
    return str;
}