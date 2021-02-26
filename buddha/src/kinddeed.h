
#ifndef _KINDDEED_H_
#define _KINDDEED_H_

#include "xchain/table/types.h"
#include "xchain/table/table.tpl.h"
#include "buddha.pb.h"

#include <string>

class kinddeed: public buddha::Kinddeed {
    DEFINE_ROWKEY(id);
    DEFINE_INDEX_BEGIN(1)
        DEFINE_INDEX_ADD(0, id)
    DEFINE_INDEX_END();

    std::string to_string() ;
};

class kinddeeddetail: public buddha::KinddeedDetail {
    //DEFINE_ROWKEY(kdid);
    DEFINE_INDEX_BEGIN(1)
        DEFINE_INDEX_ADD(0, kdid)
    DEFINE_INDEX_END();

    std::string to_string();
};

class kinddeedspec: public buddha::KinddeedSpec {
    //DEFINE_ROWKEY(kdid);
    DEFINE_INDEX_BEGIN(1)
        DEFINE_INDEX_ADD(0, kdid)
    DEFINE_INDEX_END();

    std::string to_string() ;
};


#endif // _KINDDEED_H_