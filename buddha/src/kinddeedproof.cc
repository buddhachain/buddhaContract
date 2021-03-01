#include "kinddeedproof.h"


string kinddeedproof::to_string() {
    string str ;
    str += "{" ;
    str += orderid() + ",";
    str += proof() + ",";
    str += timestamp() + ",";
    str += to_string(approved());
    str += "}";
    return str;
}