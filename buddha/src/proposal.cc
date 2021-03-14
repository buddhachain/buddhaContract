#include "proposal.h"

string proposal::to_string() {
    string str ;
    str += "{" ;
    str += key() + ",";
    str += value() + ",";
    str += owner() + ",";
    str += newvalue() + ",";
    str += operate() + ",";
    str += timestamp() + ",";
    str += expire() + ",";
    str += std::to_string(count()) + ",";
    str += founders() + ",";
    str += results() + ",";
    str += timestamps();
    str += "}";
    return str;
}
