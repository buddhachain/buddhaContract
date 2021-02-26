#ifndef _KINDDEED_PROOF_H_
#define _KINDDEED_PROOF_H_

#include "xchain/table/types.h"
#include "xchain/table/table.tpl.h"
#include "buddha.pb.h"

#include <string>

class kinddeedproof: public buddha::KinddeedProof {
    DEFINE_ROWKEY(orderid);
    DEFINE_ROWKEY(proof);
    DEFINE_INDEX_BEGIN(1)
        DEFINE_INDEX_ADD(0, orderid)
    DEFINE_INDEX_END();

    std::string to_string();
};

#endif // _KINDDEED_PROOF_H_