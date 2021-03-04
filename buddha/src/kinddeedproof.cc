#include "kinddeedproof.h"


string kinddeedproof::to_string() {
    string str ;
    str += "{" ;
    str += orderid() + ",";
    str += owner() + ",";
    str += proof() + ",";
    str += timestamp() + ",";
    str += std::to_string(approved());
    str += "}";
    return str;
}