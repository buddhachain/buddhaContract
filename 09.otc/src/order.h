#ifndef _ORDER_H_
#define _ORDER_H_

#include "xchain/table/types.h"
#include "xchain/json/json.h"
#include "xchain/table/table.tpl.h"
#include "order.pb.h"

#include <string>
using namespace std;

class BOrder: public otc::Order {
    DEFINE_ROWKEY(id);
    DEFINE_INDEX_BEGIN(4)
        DEFINE_INDEX_ADD(0, id)
        DEFINE_INDEX_ADD(1, guaranty_id)
        DEFINE_INDEX_ADD(2, buyer)   
        DEFINE_INDEX_ADD(3, state)   
    DEFINE_INDEX_END();

    xchain::json to_json() const;
};


#endif // _ORDER_H_