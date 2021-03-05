#ifndef _KINDDEED_PROOF_H_
#define _KINDDEED_PROOF_H_

#include "xchain/table/types.h"
#include "xchain/table/table.tpl.h"
#include "buddha.pb.h"

#include <string>
using namespace std;

class kinddeedproof: public buddha::KinddeedProof {
    DEFINE_ROWKEY(orderid,proof);
    DEFINE_INDEX_BEGIN(3)
        DEFINE_INDEX_ADD(0, orderid)
        DEFINE_INDEX_ADD(1, proof)
        DEFINE_INDEX_ADD(2, owner, orderid)
    DEFINE_INDEX_END();

    string to_string();
};

#endif // _KINDDEED_PROOF_H_