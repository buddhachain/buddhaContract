#ifndef _ROOM_H_
#define _ROOM_H_

#include "xchain/table/types.h"
#include "xchain/json/json.h"
#include "xchain/table/table.tpl.h"
#include "video.pb.h"

#include <string>
using namespace std;

class room: public video::Room {
    DEFINE_ROWKEY(id);
    DEFINE_INDEX_BEGIN(5)
        DEFINE_INDEX_ADD(0, id)
        DEFINE_INDEX_ADD(1, author_id) 
        DEFINE_INDEX_ADD(2, title)   
        DEFINE_INDEX_ADD(3, desc)    
        DEFINE_INDEX_ADD(4, type)    
    DEFINE_INDEX_END();

    xchain::json to_json() const;
};


#endif // _ROOM_H_