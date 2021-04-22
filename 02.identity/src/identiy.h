#ifndef _IDENTITY_H_
#define _IDENTITY_H_

#include "xchain/table/types.h"
#include "xchain/json/json.h"
#include "xchain/table/table.tpl.h"
#include "identity.pb.h"

#include <string>
using namespace std;

class identity: public identity::Identity {
    DEFINE_ROWKEY(id);              //主键
    DEFINE_INDEX_BEGIN(2)
        DEFINE_INDEX_ADD(0, id)     //只主键能find，也支持scan
        DEFINE_INDEX_ADD(1, type)   //非主键不能find，支持scan
    DEFINE_INDEX_END();

    xchain::json to_json();
};


#endif // _IDENTITY_H_