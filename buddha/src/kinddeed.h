
#ifndef _KINDDEED_H_
#define _KINDDEED_H_

#include "xchain/table/types.h"
#include "xchain/table/table.tpl.h"
#include "buddha.pb.h"

#include <string>
using namespace std;

class kinddeedtype : public buddha::KinddeedType {
    DEFINE_ROWKEY(id);
    DEFINE_INDEX_BEGIN(1)
        DEFINE_INDEX_ADD(0, id)
    DEFINE_INDEX_END();

    string to_string();
};

class kinddeed: public buddha::Kinddeed {
    DEFINE_ROWKEY(id);
    DEFINE_INDEX_BEGIN(2)
        DEFINE_INDEX_ADD(0, id)
        DEFINE_INDEX_ADD(1, owner)
        DEFINE_INDEX_ADD(2, type)
        DEFINE_INDEX_ADD(3, applied)
        DEFINE_INDEX_ADD(4, online)
    DEFINE_INDEX_END();

    string to_string() ;
};

class kinddeeddetail: public buddha::KinddeedDetail {
    DEFINE_ROWKEY(kdid,sequence);
    DEFINE_INDEX_BEGIN(1)
        DEFINE_INDEX_ADD(0, kdid)
    DEFINE_INDEX_END();

    string to_string();
};

class kinddeedspec: public buddha::KinddeedSpec {
    DEFINE_ROWKEY(kdid,sequence);
    DEFINE_INDEX_BEGIN(1)
        DEFINE_INDEX_ADD(0, kdid)
    DEFINE_INDEX_END();

    string to_string() ;
};


#endif // _KINDDEED_H_