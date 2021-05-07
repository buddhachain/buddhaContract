#ifndef _FOCUS_H_
#define _FOCUS_H_

#include "xchain/table/types.h"
#include "xchain/json/json.h"
#include "xchain/table/table.tpl.h"
#include "video.pb.h"

#include <string>
using namespace std;

class focus: public video::Focus {
    DEFINE_ROWKEY(room_id, audience_id);   //联合主键
    DEFINE_INDEX_BEGIN(2)
        DEFINE_INDEX_ADD(0, room_id)  
        DEFINE_INDEX_ADD(1, audience_id)
    DEFINE_INDEX_END();

    xchain::json to_json() const;
};


#endif // _FOCUS_H_