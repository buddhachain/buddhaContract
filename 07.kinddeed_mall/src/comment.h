#ifndef _COMMENT_H_
#define _COMMENT_H_

#include "xchain/table/types.h"
#include "xchain/json/json.h"
#include "xchain/table/table.tpl.h"
#include "buddha.pb.h"

#include <string>
using namespace std;

class BCommentLabel: public buddha::CommentLabel {
    DEFINE_ROWKEY(id);          //主键
    DEFINE_INDEX_BEGIN(1)
        DEFINE_INDEX_ADD(0, id) //只主键能find，也支持scan
    DEFINE_INDEX_END();

    xchain::json to_json();
};

class BBeforeComment: public buddha::BeforeComment {
    DEFINE_ROWKEY(kdid,owner);      //联合主键
    DEFINE_INDEX_BEGIN(2)
        DEFINE_INDEX_ADD(0, kdid)   //非主键不能find，支持scan
        DEFINE_INDEX_ADD(1, owner)  //非主键不能find，支持scan
    DEFINE_INDEX_END();

    xchain::json to_json();
};

class BAfterComment: public buddha::AfterComment {
    DEFINE_ROWKEY(orderid, owner);      //联合主键
    DEFINE_INDEX_BEGIN(2)
        DEFINE_INDEX_ADD(0, orderid)    //非主键不能find，支持scan
        DEFINE_INDEX_ADD(1, owner)      //非主键不能find，支持scan
    DEFINE_INDEX_END();

    xchain::json to_json();
};


#endif // _COMMENT_LABEL_H_