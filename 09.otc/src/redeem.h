#ifndef _REDEEM_H_
#define _REDEEM_H_

#include "xchain/table/types.h"
#include "xchain/json/json.h"
#include "xchain/table/table.tpl.h"
#include "redeem.pb.h"

#include <string>
using namespace std;

class BRedeem: public otc::Redeem {
    DEFINE_ROWKEY(id);  
    DEFINE_INDEX_BEGIN(2)
        DEFINE_INDEX_ADD(0, id)
        DEFINE_INDEX_ADD(1, guaranty_id)
    DEFINE_INDEX_END();

    xchain::json to_json() const;
};


#endif // _REDEEM_H_