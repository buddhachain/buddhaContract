#ifndef _PROPOSAL_H_
#define _PROPOSAL_H_

#include "xchain/table/types.h"
#include "xchain/table/table.tpl.h"
#include "buddha.pb.h"

#include <string>
using namespace std;

class proposal: public buddha::Proposal {
    DEFINE_ROWKEY(key);          //主键
    DEFINE_INDEX_BEGIN(1)
        DEFINE_INDEX_ADD(0, key) //主键只能find
    DEFINE_INDEX_END();

    string to_string();
};

#endif // _PROPOSAL_H_