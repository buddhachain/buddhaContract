#ifndef _TEMPLE_MASTER_H_
#define _TEMPLE_MASTER_H_

#include "xchain/table/types.h"
#include "xchain/table/table.tpl.h"
#include "buddha.pb.h"

#include <string>
using namespace std;

class templemaster: public buddha::TempleMaster {
    DEFINE_ROWKEY(templeid, masterid);
    DEFINE_INDEX_BEGIN(0)
        DEFINE_INDEX_ADD(0, templeid, masterid)
        DEFINE_INDEX_ADD(1, templeid)
        DEFINE_INDEX_ADD(2, masterid)
    DEFINE_INDEX_END();

    string to_string();
};


#endif // _TEMPLE_MASTER_H_