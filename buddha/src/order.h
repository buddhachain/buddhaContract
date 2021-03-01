#ifndef _ORDER_H_
#define _ORDER_H_

#include "xchain/table/types.h"
#include "xchain/table/table.tpl.h"
#include "buddha.pb.h"

#include <string>
using namespace std;

class order: public buddha::Order {
    DEFINE_ROWKEY(id);
    DEFINE_INDEX_BEGIN(1)
        DEFINE_INDEX_ADD(0, id)
    DEFINE_INDEX_END();

    string to_string();
};


#endif // _ORDER_H_