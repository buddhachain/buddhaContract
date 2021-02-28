#ifndef _MASTER_H_
#define _MASTER_H_

#include "xchain/table/types.h"
#include "xchain/table/table.tpl.h"
#include "buddha.pb.h"

#include <string>

class master: public buddha::Master {
    DEFINE_ROWKEY(id);
    DEFINE_ROWKEY(creditcode);
    DEFINE_INDEX_BEGIN(2)
        DEFINE_INDEX_ADD(0, id)
        DEFINE_INDEX_ADD(1, creditcode)
    DEFINE_INDEX_END();

    std::string to_string();
};


#endif // _MASTER_H_