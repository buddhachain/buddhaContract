#include "founder.h"

string founder::to_string() {
    string str ;
    str += "{" ;
    str += id() + ",";
    str += desc() + ",";
    str += address() + ",";
    str += timestamp() + ",";
    str += std::to_string(guaranty()) + ",";
    str += std::to_string(approved());
    str += "}";
    return str;
}