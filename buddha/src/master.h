#ifndef _MASTER_H_
#define _MASTER_H_

#include "xchain/table/types.h"
#include "xchain/table/table.tpl.h"
#include "buddha.pb.h"

#include <string>
using namespace std;

class master: public buddha::Master {
    DEFINE_ROWKEY(id, creditcode, proof);
    DEFINE_INDEX_BEGIN(3)
        DEFINE_INDEX_ADD(0, id)
        DEFINE_INDEX_ADD(1, creditcode)
        DEFINE_INDEX_ADD(2, proof)
    DEFINE_INDEX_END();

    string to_string();
};


#endif // _MASTER_H_