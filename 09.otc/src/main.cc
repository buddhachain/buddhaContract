#include <inttypes.h>
#include "xchain/xchain.h"
#include "xchain/account.h"
#include "xchain/contract.pb.h"
#include "xchain/syscall.h"
#include "otc.pb.h"
#include "otc.h"

#include <iostream>
using namespace std;

Otc::Otc() :
    _sell_table(   context(), "sell"    ),
    _redeemsell_table(     context(), "redeem"      ),
    _order_table(      context(), "order"       ),

    ctx(context())
{
}

void Otc::_log_error(const string& file, const string& fun, const int line, const string& message) {
    cout << file << "(" << line << ") [" << fun << "] " << message << endl;
    xchain::json ret ;
    ret["result"] = false;
    ret["message"] = message;

    ctx->ok(ret.dump());
}


void Otc::_log_error(const string& file, const string& fun, const int line, const string& message, const xchain::json& j) {
    cout << file << "(" << line << ") [" << fun << "] " << j.dump() << endl;
    xchain::json ret ;
    ret["result"] = false;
    ret["message"] = message;
    ret["value"] = j;
    if(j.is_array())
        ret["size"] = j.size();

    ctx->ok(ret.dump());
}

void Otc::_log_ok(const string& file, const string& fun, const int line, const string& message) {
    cout << file << "(" << line << ") [" << fun << "] " << message << endl;
    xchain::json ret ;
    ret["result"] = true;
    ret["message"] = message;
    ctx->ok(ret.dump());
}

void Otc::_log_ok(const string& file, const string& fun, const int line, const string& message, const xchain::json& j) {
    cout << file << "(" << line << ") [" << fun << "] " << j.dump() << endl;
    xchain::json ret ;
    ret["result"] = true;
    ret["message"] = message;
    ret["value"] = j;
    if(j.is_array())
        ret["size"] = j.size();

    ctx->ok(ret.dump());
}
