#ifndef _ORDER_H_
#define _ORDER_H_

#include "xchain/table/types.h"
#include "xchain/table/table.tpl.h"
#include "buddha.pb.h"

#include <string>
using namespace std;

class order: public buddha::Order {
    DEFINE_ROWKEY(id);                  //主键
    DEFINE_INDEX_BEGIN(2)
        DEFINE_INDEX_ADD(0, id)         //主键只能find
        DEFINE_INDEX_ADD(1, kdowner)    //非主键只能scan
    DEFINE_INDEX_END();

    string to_string();
};


#endif // _ORDER_H_