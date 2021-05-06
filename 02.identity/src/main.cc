#include <inttypes.h>
#include "xchain/xchain.h"
#include "xchain/account.h"
#include "xchain/contract.pb.h"
#include "xchain/syscall.h"
#include "main.h"

#include <iostream>
using namespace std;

Main::Main() :
    _identity_table(        context(), "identity"       ),
    _visitor_table(         context(), "visitor"        ),
    _user_table(            context(), "user"           ),
    _identityuser_table(   context(), "identity_user"  ),
    _master_table(          context(), "master"         ),
    _temple_table(          context(), "temple"         ),
    _templemaster_table(    context(), "templemaster"   ),
    _thedead_table(         context(), "thedead"        ),

    ctx(context())
{
}

void Main::_log_error(const string& file, const string& fun, const int line, const string& message) {
    cout << file << "(" << line << ") [" << fun << "] " << message << endl;
    xchain::json ret ;
    ret["result"] = false;
    ret["message"] = message;

    ctx->ok(ret.dump());
}


void Main::_log_error(const string& file, const string& fun, const int line, const string& message, const xchain::json& j) {
    cout << file << "(" << line << ") [" << fun << "] " << j.dump() << endl;
    xchain::json ret ;
    ret["result"] = false;
    ret["message"] = message;
    ret["value"] = j;
    if(j.is_array())
        ret["size"] = j.size();

    ctx->ok(ret.dump());
}

void Main::_log_ok(const string& file, const string& fun, const int line, const string& message) {
    cout << file << "(" << line << ") [" << fun << "] " << message << endl;
    xchain::json ret ;
    ret["result"] = true;
    ret["message"] = message;
    ctx->ok(ret.dump());
}

void Main::_log_ok(const string& file, const string& fun, const int line, const string& message, const xchain::json& j) {
    cout << file << "(" << line << ") [" << fun << "] " << j.dump() << endl;
    xchain::json ret ;
    ret["result"] = true;
    ret["message"] = message;
    ret["value"] = j;
    if(j.is_array())
        ret["size"] = j.size();

    ctx->ok(ret.dump());
}

bool Main::_is_founder(const string& id) {
    xchain::Response resp;
    bool ret = ctx->call("wasm", "founder", "is_founder", ctx->args(), &resp);
    if (!ret) {
        ctx->error("call failed");
        return false;
    }
    
    *ctx->mutable_response() = resp;
    mycout << "resp.message=" << resp.message << endl ;
    mycout << "resp.body=" << resp.body << endl ;
    mycout << "resp.status=" << to_string(resp.status) << endl ;
    
    return resp.status;
}


bool Main::is_founder() {
    if (!_is_founder(ctx->initiator()) ) {
        _log_ok(__FILE__, __FUNCTION__, __LINE__, ctx->initiator() + " is not founder .") ;
        return false;
    }
    
    _log_ok(__FILE__, __FUNCTION__, __LINE__, ctx->initiator() + " is founder .") ;
    return true;
}

