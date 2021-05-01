#ifndef _TEMPLE_H_
#define _TEMPLE_H_

#include "xchain/table/types.h"
#include "xchain/json/json.h"
#include "xchain/table/table.tpl.h"
#include "buddha.pb.h"

#include <string>
using namespace std;

class BTemple: public Temple {
    DEFINE_ROWKEY(id);                  //主键
    DEFINE_INDEX_BEGIN(5)
        DEFINE_INDEX_ADD(0, id)         //只主键能find，也支持scan
        DEFINE_INDEX_ADD(1, unit)       //非主键不能find，支持scan
        DEFINE_INDEX_ADD(2, creditcode) //非主键不能find，支持scan
        DEFINE_INDEX_ADD(3, address)    //非主键不能find，支持scan
        DEFINE_INDEX_ADD(4, proof)      //非主键不能find，支持scan
    DEFINE_INDEX_END();

    xchain::json to_json();
};


#endif // _TEMPLE_H_