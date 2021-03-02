#include "temple.h"

string temple::to_string() {
    string str ;
    str += "{" ;
    str += id() + ",";
    str += unit() + ",";
    str += creditcode() + ",";
    str += address() + ",";
    str += proof() + ",";
    str += std::to_string(approved());
    str += "}";
    return str;
}
