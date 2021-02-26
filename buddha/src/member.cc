#include "member.h"

std::string member::to_string() {
    std::string str ;
    str += "{" ;
    str += id() + ",";
    str += nickname() + ",";
    str += sex() + ",";
    str += address() + ",";
    str += email() + ",";
    str += phone();
    str += "}";
    return str;
}
