#include "founder.h"

string founder::to_string() {
    string str ;
    str += "{" ;
    str += id() + ",";
    str += desc() + ",";
    str += to_string(guaranty()) + ",";
    str += to_string(approved());
    str += "}";
    return str;
}