#ifndef _TEMPLE_MASTER_H_
#define _TEMPLE_MASTER_H_

#include "xchain/table/types.h"
#include "xchain/table/table.tpl.h"
#include "buddha.pb.h"

#include <string>

class templemaster: public buddha::TempleMaster {
    DEFINE_ROWKEY(templeid);
    DEFINE_ROWKEY(masterid);
    DEFINE_INDEX_BEGIN(2)
        DEFINE_INDEX_ADD(0, templeid)
        DEFINE_INDEX_ADD(1, masterid)
    DEFINE_INDEX_END();

    std::string to_string();
};


#endif // _TEMPLE_MASTER_H_