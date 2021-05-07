#ifndef _KINDDEED_PROOF_H_
#define _KINDDEED_PROOF_H_

#include "xchain/table/types.h"
#include "xchain/json/json.h"
#include "xchain/table/table.tpl.h"
#include "buddha.pb.h"

#include <string>
using namespace std;

class BKinddeedProof: public KinddeedProof {
    DEFINE_ROWKEY(orderid);   
    DEFINE_INDEX_BEGIN(2)
        DEFINE_INDEX_ADD(0, orderid)   
        DEFINE_INDEX_ADD(1, owner)   
    DEFINE_INDEX_END();

    xchain::json to_json() const;
};

#endif // _KINDDEED_PROOF_H_