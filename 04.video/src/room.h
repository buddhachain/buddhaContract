#ifndef _ROOM_H_
#define _ROOM_H_

#include "xchain/table/types.h"
#include "xchain/json/json.h"
#include "xchain/table/table.tpl.h"
#include "video.pb.h"

#include <string>
using namespace std;

class room: public video::Room {
    DEFINE_ROWKEY(id);                  //主键
    DEFINE_INDEX_BEGIN(5)
        DEFINE_INDEX_ADD(0, id)         //只主键能find，也支持scan
        DEFINE_INDEX_ADD(1, author_id)  //非主键不能find，支持scan
        DEFINE_INDEX_ADD(2, title)      //非主键不能find，支持scan
        DEFINE_INDEX_ADD(3, desc)       //非主键不能find，支持scan
        DEFINE_INDEX_ADD(4, type)       //非主键不能find，支持scan
    DEFINE_INDEX_END();

    xchain::json to_json();
};


#endif // _ROOM_H_