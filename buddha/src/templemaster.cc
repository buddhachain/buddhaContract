#include "templemaster.h"

string templemaster::to_string() {
    string str ;
    str += "{" ;
    str += templeid() + ",";
    str += masterid() + ",";
    str += to_string(approved());
    str += "}";
    return str;
}
