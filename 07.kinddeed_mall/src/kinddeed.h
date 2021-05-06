
#ifndef _KINDDEED_H_
#define _KINDDEED_H_

#include "xchain/table/types.h"
#include "xchain/json/json.h"
#include "xchain/table/table.tpl.h"
#include "buddha.pb.h"

#include <string>
using namespace std;

class BKinddeedType : public KinddeedType {
    DEFINE_ROWKEY(id);
    DEFINE_INDEX_BEGIN(1)
        DEFINE_INDEX_ADD(0, id)
    DEFINE_INDEX_END();

    xchain::json to_json();
};

class BKinddeed: public Kinddeed {
    DEFINE_ROWKEY(id);    
    DEFINE_INDEX_BEGIN(2)
        DEFINE_INDEX_ADD(0, id)
        DEFINE_INDEX_ADD(1, owner) 
    DEFINE_INDEX_END();

    xchain::json to_json();
};

class BKinddeedDetail: public KinddeedDetail {
    DEFINE_ROWKEY(kdid,sequence);   //联合主键
    DEFINE_INDEX_BEGIN(1)
        DEFINE_INDEX_ADD(0, kdid)
    DEFINE_INDEX_END();

    xchain::json to_json();
};

class BKinddeedSpec: public KinddeedSpec {
    DEFINE_ROWKEY(kdid,sequence);   //联合主键
    DEFINE_INDEX_BEGIN(1)
        DEFINE_INDEX_ADD(0, kdid)
    DEFINE_INDEX_END();

    xchain::json to_json();
};


#endif // _KINDDEED_H_