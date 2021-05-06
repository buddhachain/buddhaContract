#ifndef _TEMPLE_H_
#define _TEMPLE_H_

#include "xchain/table/types.h"
#include "xchain/json/json.h"
#include "xchain/table/table.tpl.h"
#include "temple.pb.h"

#include <string>
using namespace std;

class BTemple: public Temple {
    DEFINE_ROWKEY(id);
    DEFINE_INDEX_BEGIN(3)
        DEFINE_INDEX_ADD(0, id)
        DEFINE_INDEX_ADD(1, unit, creditcode, address, proof)
        DEFINE_INDEX_ADD(2, approved)
    DEFINE_INDEX_END();

    xchain::json to_json();
};

#endif // _TEMPLE_H_