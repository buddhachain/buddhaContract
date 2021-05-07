#ifndef _FOUNDER_H_
#define _FOUNDER_H_

#include "xchain/table/types.h"
#include "xchain/json/json.h"
#include "xchain/table/table.tpl.h"
#include "founder.pb.h"

#include <string>
using namespace std;

const int64_t MEMBER    = 1;
const int64_t PRESIDENT = 2;

class BFounder: public Founder {
    DEFINE_ROWKEY(id);
    DEFINE_INDEX_BEGIN(2)
        DEFINE_INDEX_ADD(0, id)
        DEFINE_INDEX_ADD(1, approved)
    DEFINE_INDEX_END();

    xchain::json to_json() const;
};

#endif // _FOUNDER_H_