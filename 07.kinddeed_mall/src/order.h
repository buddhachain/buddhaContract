#ifndef _ORDER_H_
#define _ORDER_H_

#include "xchain/table/types.h"
#include "xchain/json/json.h"
#include "xchain/table/table.tpl.h"
#include "buddha.pb.h"

#include <string>
using namespace std;

class BOrder: public Order {
    DEFINE_ROWKEY(id);
    DEFINE_INDEX_BEGIN(2)
        DEFINE_INDEX_ADD(0, id)
        DEFINE_INDEX_ADD(1, kdowner) 
    DEFINE_INDEX_END();

    xchain::json to_json();
};


#endif // _ORDER_H_