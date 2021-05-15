#ifndef _BUY_ORDER_H_
#define _BUY_ORDER_H_

#include "xchain/table/types.h"
#include "xchain/json/json.h"
#include "xchain/table/table.tpl.h"
#include "buy_order.pb.h"

#include <string>
using namespace std;

class BCBuyOrder: public BuyOrder {
    DEFINE_ROWKEY(id);
    DEFINE_INDEX_BEGIN(3)
        DEFINE_INDEX_ADD(0, id)
        DEFINE_INDEX_ADD(1, sell_id, buyer)
        DEFINE_INDEX_ADD(2, state)   
    DEFINE_INDEX_END();

    xchain::json to_json() const;
};


#endif // _BUY_ORDER_H_