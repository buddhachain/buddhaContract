#ifndef _FOUNDER_H_
#define _FOUNDER_H_

#include "xchain/table/types.h"
#include "xchain/table/table.tpl.h"
#include "buddha.pb.h"

#include <string>
using namespace std;

class founder: public buddha::Founder {
    DEFINE_ROWKEY(id);
    DEFINE_INDEX_BEGIN(1)
        DEFINE_INDEX_ADD(0, id)
    DEFINE_INDEX_END();

    string to_string();
};

#endif // _FOUNDER_H_