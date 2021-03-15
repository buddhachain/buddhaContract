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

xchain::json kinddeedproof::to_json() {
    xchain::json j = {
        {"key", key()},
        {"value", value()},
        {"owner", owner()},
        {"newvalue", newvalue()},
        {"operate", operate()},
        {"timestamp", timestamp()},
        {"expire", expire()},
        {"count", count()},
        {"founders", founders()},
        {"results", results()},
        {"timestamps", timestamps()},
    };

    return j;
}
