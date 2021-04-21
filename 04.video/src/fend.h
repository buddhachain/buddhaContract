#ifndef _FEND_H_
#define _FEND_H_

#include "xchain/table/types.h"
#include "xchain/json/json.h"
#include "xchain/table/table.tpl.h"
#include "video.pb.h"

#include <string>
using namespace std;

class fend: public video::Fend {
    DEFINE_ROWKEY(id);                  //主键
    DEFINE_INDEX_BEGIN(4)
        DEFINE_INDEX_ADD(0, id)         //只主键能find，也支持scan
        DEFINE_INDEX_ADD(1, author_id)  //非主键不能find，支持scan
        DEFINE_INDEX_ADD(2, room_id)    //非主键不能find，支持scan
        DEFINE_INDEX_ADD(3, audience_id)//非主键不能find，支持scan
    DEFINE_INDEX_END();

    xchain::json to_json();
};

class fendlog: public video::FendLog {
    DEFINE_ROWKEY(id);                  //主键
    DEFINE_INDEX_BEGIN(5)
        DEFINE_INDEX_ADD(0, id)         //只主键能find，也支持scan
        DEFINE_INDEX_ADD(1, fend_id)    //非主键不能find，支持scan
        DEFINE_INDEX_ADD(2, room_id)    //非主键不能find，支持scan
        DEFINE_INDEX_ADD(3, audience_id)//非主键不能find，支持scan
        DEFINE_INDEX_ADD(4, goods_id)   //非主键不能find，支持scan
    DEFINE_INDEX_END();

    xchain::json to_json();
};


#endif // _FEND_H_