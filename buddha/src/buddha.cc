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

Buddha::Buddha() :
    _founder_table(         context(), "founder"                ),
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

    ctx(context())
{
}


void Buddha::_log_error(string fun, int line, string str) {
    cout << fun << "[" << line << "] " << str << endl;

    ctx->error("{ \"result\":false, \"message\":\"" + str +"\" }");
}

void Buddha::_log_ok(string str) {
    ctx->ok("{ \"result\":true, \"message\":\"" + str +"\" }");
}
