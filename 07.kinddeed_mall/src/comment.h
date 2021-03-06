#ifndef _COMMENT_H_
#define _COMMENT_H_

#include "xchain/table/types.h"
#include "xchain/json/json.h"
#include "xchain/table/table.tpl.h"
#include "buddha.pb.h"

#include <string>
using namespace std;

class BCommentLabel: public CommentLabel {
    DEFINE_ROWKEY(id);
    DEFINE_INDEX_BEGIN(1)
        DEFINE_INDEX_ADD(0, id)
    DEFINE_INDEX_END();

    xchain::json to_json() const;
};

class BBeforeComment: public BeforeComment {
    DEFINE_ROWKEY(kdid,owner);      //联合主键
    DEFINE_INDEX_BEGIN(2)
        DEFINE_INDEX_ADD(0, kdid)
        DEFINE_INDEX_ADD(1, owner) 
    DEFINE_INDEX_END();

    xchain::json to_json() const;
};

class BAfterComment: public AfterComment {
    DEFINE_ROWKEY(orderid, owner);      //联合主键
    DEFINE_INDEX_BEGIN(2)
        DEFINE_INDEX_ADD(0, orderid) 
        DEFINE_INDEX_ADD(1, owner)   
    DEFINE_INDEX_END();

    xchain::json to_json() const;
};


#endif // _COMMENT_LABEL_H_