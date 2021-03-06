#include <inttypes.h>
#include "xchain/xchain.h"
#include "xchain/account.h"
#include "xchain/contract.pb.h"
#include "xchain/syscall.h"
#include "buddha.pb.h"
#include "buddha.h"

#include <iostream>
using namespace std;

Main::Buddha() :
    _founder_table(         context(), "founder"                ),
    _proposal_table(        context(), "proposal"               ),
    _temple_table(          context(), "temple"                 ),
    _master_table(          context(), "master"                 ),
    _templemaster_table(    context(), "templemaster"           ),
    _kinddeedtype_table(    context(), "kinddeedtype"           ),
    _kinddeed_table(        context(), "kinddeed"               ),
    _kinddeeddetail_table(  context(), "kinddeeddetail"         ),
    _kinddeedspec_table(    context(), "kinddeedspec"           ),
    _commentlabel_table(    context(), "commentlabel"           ),
    _beforecomment_table(   context(), "beforecomment"          ),
    _order_table(           context(), "order"                  ),
    _kinddeedproof_table(   context(), "kinddeedproof"          ),
    _aftercomment_table(    context(), "aftercomment"           ),
    _credit_table(          context(), "credit"                 ),
    _creditranking_table(   context(), "creditranking"          ),
    _merit_table(           context(), "merit"                  ),
    _meritranking_table(    context(), "meritranking"           ),

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
