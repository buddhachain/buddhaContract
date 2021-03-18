#ifndef _MASTER_H_
#define _MASTER_H_

#include "xchain/table/types.h"
#include "xchain/json/json.h"
#include "xchain/table/table.tpl.h"
#include "buddha.pb.h"

#include <string>
using namespace std;

class master: public buddha::Master {
    DEFINE_ROWKEY(id);                  //主键
    DEFINE_INDEX_BEGIN(3)
        DEFINE_INDEX_ADD(0, id)         //只主键能find，也支持scan
        DEFINE_INDEX_ADD(1, creditcode) //非主键不能find，支持scan
        DEFINE_INDEX_ADD(2, proof)      //非主键不能find，支持scan
    DEFINE_INDEX_END();

    string to_string();
    xchain::json to_json();
};


#endif // _MASTER_H_