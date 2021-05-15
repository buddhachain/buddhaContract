#ifndef _REDEEAM_SELL_H_
#define _REDEEAM_SELL_H_

#include "xchain/table/types.h"
#include "xchain/json/json.h"
#include "xchain/table/table.tpl.h"
#include "redeem_sell.pb.h"

#include <string>
using namespace std;

class BBRedeemSell: public RedeemSell {
    DEFINE_ROWKEY(id);  
    DEFINE_INDEX_BEGIN(2)
        DEFINE_INDEX_ADD(0, id)
        DEFINE_INDEX_ADD(1, sellid)
    DEFINE_INDEX_END();

    xchain::json to_json() const;
};


#endif // _REDEEAM_SELL_H_