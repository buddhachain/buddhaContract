#ifndef _COMMENT_H_
#define _COMMENT_H_

#include "xchain/table/types.h"
#include "xchain/json/json.h"
#include "xchain/table/table.tpl.h"
#include "buddha.pb.h"

#include <string>
using namespace std;

class commentlabel: public buddha::CommentLabel {
    DEFINE_ROWKEY(id);          //主键
    DEFINE_INDEX_BEGIN(1)
        DEFINE_INDEX_ADD(0, id) //主键只能find
    DEFINE_INDEX_END();

    string to_string();
    xchain::json to_json();
};

class beforecomment: public buddha::BeforeComment {
    DEFINE_ROWKEY(kdid,owner);      //联合主键
    DEFINE_INDEX_BEGIN(2)
        DEFINE_INDEX_ADD(0, kdid)   //非主键只能scan
        DEFINE_INDEX_ADD(1, owner)  //非主键只能scan
    DEFINE_INDEX_END();

    string to_string();
    xchain::json to_json();
};

class aftercomment: public buddha::AfterComment {
    DEFINE_ROWKEY(orderid, owner);      //联合主键
    DEFINE_INDEX_BEGIN(2)
        DEFINE_INDEX_ADD(0, orderid)    //非主键只能scan
        DEFINE_INDEX_ADD(1, owner)      //非主键只能scan
    DEFINE_INDEX_END();

    string to_string();
    xchain::json to_json();
};


#endif // _COMMENT_LABEL_H_