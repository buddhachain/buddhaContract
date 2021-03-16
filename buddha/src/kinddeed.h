
#ifndef _KINDDEED_H_
#define _KINDDEED_H_

#include "xchain/table/types.h"
#include "xchain/json/json.h"
#include "xchain/table/table.tpl.h"
#include "buddha.pb.h"

#include <string>
using namespace std;

class kinddeedtype : public buddha::KinddeedType {
    DEFINE_ROWKEY(id);          //主键
    DEFINE_INDEX_BEGIN(1)
        DEFINE_INDEX_ADD(0, id) //主键只能find
    DEFINE_INDEX_END();

    string to_string();
    xchain::json to_json();
};

class kinddeed: public buddha::Kinddeed {
    DEFINE_ROWKEY(id);              //主键
    DEFINE_INDEX_BEGIN(2)
        DEFINE_INDEX_ADD(0, id)     //主键只能find
        DEFINE_INDEX_ADD(1, owner)  //非主键只能scan
    DEFINE_INDEX_END();

    string to_string();
    xchain::json to_json();
};

class kinddeeddetail: public buddha::KinddeedDetail {
    DEFINE_ROWKEY(kdid,sequence);   //联合主键
    DEFINE_INDEX_BEGIN(1)
        DEFINE_INDEX_ADD(0, kdid)   //非主键只能scan
    DEFINE_INDEX_END();

    string to_string();
    xchain::json to_json();
};

class kinddeedspec: public buddha::KinddeedSpec {
    DEFINE_ROWKEY(kdid,sequence);   //联合主键
    DEFINE_INDEX_BEGIN(1)
        DEFINE_INDEX_ADD(0, kdid)   //非主键只能scan
    DEFINE_INDEX_END();

    string to_string();
    xchain::json to_json();
};


#endif // _KINDDEED_H_