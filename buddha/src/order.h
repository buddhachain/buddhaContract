#ifndef _ORDER_H_
#define _ORDER_H_

#include "xchain/table/types.h"
#include "xchain/json/json.h"
#include "xchain/table/table.tpl.h"
#include "buddha.pb.h"

#include <string>
using namespace std;

class order: public buddha::Order {
    DEFINE_ROWKEY(id);                  //主键
    DEFINE_INDEX_BEGIN(2)
        DEFINE_INDEX_ADD(0, id)         //只主键能find，也支持scan
        DEFINE_INDEX_ADD(1, kdowner)    //非主键不能find，支持scan
    DEFINE_INDEX_END();

    string to_string();
    xchain::json to_json();
};


#endif // _ORDER_H_