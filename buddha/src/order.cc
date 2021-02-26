#include "order.h"

std::string order::to_string() {
    std::string str ;
    str += "{" ;
    str += id() + ",";
    str += owner() + ",";
    str += mastername() + ",";
    str += kdid() + ",";
    str += std::to_string(kdseqid()) + ",";
    str += std::to_string(count()) + ",";
    str += std::to_string(amount()) + ",";
    str += timestamp() ;
    str += "}";
    return str;
}
