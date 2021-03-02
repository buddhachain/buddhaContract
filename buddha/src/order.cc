#include "order.h"

string order::to_string() {
    string str ;
    str += "{" ;
    str += id() + ",";
    str += owner() + ",";
    str += master() + ",";
    str += kdid() + ",";
    str += std::to_string(specid()) + ",";
    str += std::to_string(count()) + ",";
    str += std::to_string(amount()) + ",";
    str += timestamp() ;
    str += "}";
    return str;
}
