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

void Buddha::initialize() {
    ctx->put_object("deployer", ctx->initiator());
    ctx->emit_event("initialize", ctx->initiator());
    _log_ok("deployer=" + ctx->initiator() + " success");
}

void Buddha::get_deployer() {
    string deployer;
    if (!ctx->get_object("deployer", &deployer)) {
        _log_error(__FUNCTION__, __LINE__,"unknown deployer .");
        return ;
    }

    if( !_is_deployer(ctx->initiator()) &&
        !_is_founder(ctx->initiator()) ) {
        _log_error(__FUNCTION__, __LINE__,ctx->initiator() + " is not deployer nor founder, have no authority to get deployer .");
        return ;
    }

    _log_ok("deployer=" + deployer);
}

bool Buddha::is_deployer() {
    bool ret = _is_deployer(ctx->initiator());
    if (ret) {
        _log_ok(ctx->initiator() + " is deployer .") ;
        return true;
    }
    
    _log_ok(ctx->initiator() + " is not deployer .") ;
    return false;
}


DEFINE_METHOD(Buddha, initialize)               { self.initialize();                }
DEFINE_METHOD(Buddha, get_deployer)             { self.get_deployer();              }
DEFINE_METHOD(Buddha, is_deployer)              { self.is_deployer();               }