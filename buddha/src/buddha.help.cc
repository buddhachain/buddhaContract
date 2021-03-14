#include <inttypes.h>
#include "xchain/json/json.h"
#include "xchain/xchain.h"
#include "xchain/account.h"
#include "xchain/contract.pb.h"
#include "xchain/syscall.h"
#include "buddha.pb.h"
#include "buddha.h"

#include <iostream>
using namespace std;

void Buddha::_log_error(string fun, int line, string str) {
    cout << fun << "[" << line << "] " << str << endl;

    ctx->error("{ \"result\":false, \"message\":\"" + str +"\" }");
}

void Buddha::_log_ok(string str) {
    ctx->ok("{ \"result\":true, \"message\":\"" + str +"\" }");
}
