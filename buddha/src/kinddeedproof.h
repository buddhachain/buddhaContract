#ifndef _KINDDEED_PROOF_H_
#define _KINDDEED_PROOF_H_

#include "xchain/table/types.h"
#include "xchain/json/json.h"
#include "xchain/table/table.tpl.h"
#include "buddha.pb.h"

#include <string>
using namespace std;

class kinddeedproof: public buddha::KinddeedProof {
    DEFINE_ROWKEY(orderid);             //主键
    DEFINE_INDEX_BEGIN(2)
        DEFINE_INDEX_ADD(0, orderid)    //主键只能find
        DEFINE_INDEX_ADD(1, owner)      //非主键只能scan
    DEFINE_INDEX_END();

    string to_string();
    xchain::json to_json();
};

#endif // _KINDDEED_PROOF_H_