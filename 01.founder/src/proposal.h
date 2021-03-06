#ifndef _PROPOSAL_H_
#define _PROPOSAL_H_

#include "xchain/table/types.h"
#include "xchain/json/json.h"
#include "xchain/table/table.tpl.h"
#include "proposal.pb.h"

#include <string>
using namespace std;

class BProposal: public Proposal {
    DEFINE_ROWKEY(key);
    DEFINE_INDEX_BEGIN(1)
        DEFINE_INDEX_ADD(0, key)
    DEFINE_INDEX_END();

    xchain::json to_json() const;
};

#endif // _PROPOSAL_H_