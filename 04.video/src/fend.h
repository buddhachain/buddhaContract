#ifndef _FEND_H_
#define _FEND_H_

#include "xchain/table/types.h"
#include "xchain/json/json.h"
#include "xchain/table/table.tpl.h"
#include "video.pb.h"

#include <string>
using namespace std;

class fend: public video::Fend {
    DEFINE_ROWKEY(id);
    DEFINE_INDEX_BEGIN(2)
        DEFINE_INDEX_ADD(0, id)
        DEFINE_INDEX_ADD(1, author_id, room_id, audience_id)
    DEFINE_INDEX_END();

    xchain::json to_json() const;
};

class fendlog: public video::FendLog {
    DEFINE_ROWKEY(id);
    DEFINE_INDEX_BEGIN(2)
        DEFINE_INDEX_ADD(0, id)
        DEFINE_INDEX_ADD(1, fend_id, room_id, audience_id, goods_id)
    DEFINE_INDEX_END();

    xchain::json to_json() const;
};


#endif // _FEND_H_