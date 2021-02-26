#include "kinddeedproof.h"


std::string kinddeedproof::to_string() {
    std::string str ;
    str += "{" ;
    str += orderid() + ",";
    str += proof() + ",";
    str += timestamp() + ",";
    str += std::to_string(approved());
    str += "}";
    return str;
}