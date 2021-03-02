#ifndef _TEMPLE_H_
#define _TEMPLE_H_

#include "xchain/table/types.h"
#include "xchain/table/table.tpl.h"
#include "buddha.pb.h"

#include <string>
using namespace std;

class temple: public buddha::Temple {
    DEFINE_ROWKEY(id);//,unit,creditcode,address,proof);
    DEFINE_INDEX_BEGIN(5)
        DEFINE_INDEX_ADD(0, id)
        DEFINE_INDEX_ADD(1, unit)
        DEFINE_INDEX_ADD(2, creditcode)
        DEFINE_INDEX_ADD(3, address)
        DEFINE_INDEX_ADD(4, proof)
    DEFINE_INDEX_END();

    string to_string();
};


#endif // _TEMPLE_H_