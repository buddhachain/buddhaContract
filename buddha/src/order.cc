#include "order.h"

string order::to_string() {
    string str ;
    str += "{" ;
    str += id() + ",";
    str += owner() + ",";
    str += mastername() + ",";
    str += kdid() + ",";
    str += to_string(kdseqid()) + ",";
    str += to_string(count()) + ",";
    str += to_string(amount()) + ",";
    str += timestamp() ;
    str += "}";
    return str;
}
