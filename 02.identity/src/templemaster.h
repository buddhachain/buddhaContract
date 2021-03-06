#ifndef _TEMPLE_MASTER_H_
#define _TEMPLE_MASTER_H_

#include "xchain/table/types.h"
#include "xchain/json/json.h"
#include "xchain/table/table.tpl.h"
#include "templemaster.pb.h"

#include <string>
using namespace std;

class BTempleMaster: public TempleMaster {
    DEFINE_ROWKEY(templeid, masterid);  //联合主键
    DEFINE_INDEX_BEGIN(2)
        DEFINE_INDEX_ADD(0, templeid)   //非主键不能find，支持scan
        DEFINE_INDEX_ADD(1, masterid)   //非主键不能find，支持scan
    DEFINE_INDEX_END();

    xchain::json to_json() const;
};


#endif // _TEMPLE_MASTER_H_