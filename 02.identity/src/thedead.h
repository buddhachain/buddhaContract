#ifndef _THEDEAD_H_
#define _THEDEAD_H_

#include "xchain/table/types.h"
#include "xchain/json/json.h"
#include "xchain/table/table.tpl.h"
#include "thedead.pb.h"

#include <string>
using namespace std;

class BTheDead: public TheDead {
    DEFINE_ROWKEY(id);
    DEFINE_INDEX_BEGIN(4)
        DEFINE_INDEX_ADD(0, id)
        DEFINE_INDEX_ADD(1, name)   
        DEFINE_INDEX_ADD(2, born_timestamp, born_address, dead_timestamp, dead_address)
        DEFINE_INDEX_ADD(3, idcard, otherid)
    DEFINE_INDEX_END();

    xchain::json to_json() const;
};


#endif // _THEDEAD_H_