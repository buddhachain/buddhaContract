#ifndef _SELL_H_
#define _SELL_H_

#include "xchain/table/types.h"
#include "xchain/json/json.h"
#include "xchain/table/table.tpl.h"
#include "sell.pb.h"

#include <string>
using namespace std;

class BBSell: public Sell {
    DEFINE_ROWKEY(id);
    DEFINE_INDEX_BEGIN(2)
        DEFINE_INDEX_ADD(0, id)
        DEFINE_INDEX_ADD(1, account)  
    DEFINE_INDEX_END();

    xchain::json to_json() const;
};


#endif // _SELL_H_