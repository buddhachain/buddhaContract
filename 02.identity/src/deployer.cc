#include <inttypes.h>
#include "xchain/xchain.h"
#include "xchain/account.h"
#include "xchain/contract.pb.h"
#include "xchain/syscall.h"
#include "main.h"

#include <iostream>
using namespace std;

bool Main::_is_deployer(const string& id) {
    string deployer;
    if (!ctx->get_object("deployer", &deployer)) 
        return false;

    if (deployer != id )
        return false;

    return true ;
}

bool Main::_transfer(const string& toid,
                    const string& toamount){
    //将抵押退还
    xchain::Account account = xchain::Account(toid);
    if( !account.transfer(toamount)) 
        return false;

    return true ;
}

namespace 分界线{}

void Main::initialize() {
    //deployer对象存储
    ctx->put_object("deployer", ctx->initiator());
    ctx->emit_event("initialize", ctx->initiator());
    _log_ok(__FILE__, __FUNCTION__, __LINE__, "deployer=" + ctx->initiator());
}

void Main::get_deployer() {
    //获取deployer对象
    string deployer;
    if (!ctx->get_object("deployer", &deployer) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "unknown deployer .");
        return ;
    }

    //判断当前调用者是否是合约部署者或者基金会成员
    if( !_is_deployer(ctx->initiator()) &&
        !_is_founder(ctx->initiator()) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__,ctx->initiator() + " is not deployer nor founder, have no authority to get deployer .");
        return ;
    }

    _log_ok(__FILE__, __FUNCTION__, __LINE__, "deployer=" + deployer);
}

bool Main::is_deployer() {
    bool ret = _is_deployer(ctx->initiator());
    if (ret) {
        _log_ok(__FILE__, __FUNCTION__, __LINE__, ctx->initiator() + " is deployer .") ;
        return true;
    }
    
    _log_ok(__FILE__, __FUNCTION__, __LINE__, ctx->initiator() + " is not deployer .") ;
    return false;
}


DEFINE_METHOD(Buddha, initialize)               { self.initialize();                }
DEFINE_METHOD(Buddha, get_deployer)             { self.get_deployer();              }
DEFINE_METHOD(Buddha, is_deployer)              { self.is_deployer();               }