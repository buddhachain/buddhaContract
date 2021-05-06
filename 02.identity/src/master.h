#ifndef _MASTER_H_
#define _MASTER_H_

#include "xchain/table/types.h"
#include "xchain/json/json.h"
#include "xchain/table/table.tpl.h"
#include "master.pb.h"

#include <string>
using namespace std;

class BMaster: public Master {
    DEFINE_ROWKEY(id);
    DEFINE_INDEX_BEGIN(3)
        DEFINE_INDEX_ADD(0, id)
        DEFINE_INDEX_ADD(1, buddhist_name, creditcode, proof )
        DEFINE_INDEX_ADD(2, approved)
    DEFINE_INDEX_END();

    xchain::json to_json();
};


#endif // _MASTER_H_