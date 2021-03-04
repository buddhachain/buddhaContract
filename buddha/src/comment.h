#ifndef _COMMENT_H_
#define _COMMENT_H_

#include "xchain/table/types.h"
#include "xchain/table/table.tpl.h"
#include "buddha.pb.h"

#include <string>
using namespace std;

class commentlabel: public buddha::CommentLabel {
    DEFINE_ROWKEY(id);
    DEFINE_INDEX_BEGIN(1)
        DEFINE_INDEX_ADD(0, id)
    DEFINE_INDEX_END();

    string to_string();
};

class beforecomment: public buddha::BeforeComment {
    DEFINE_ROWKEY(owner,kdid);
    DEFINE_INDEX_BEGIN(1)
        DEFINE_INDEX_ADD(0, owner, kdid)
    DEFINE_INDEX_END();

    string to_string();
};

class aftercomment: public buddha::AfterComment {
    DEFINE_ROWKEY(orderid);
    DEFINE_INDEX_BEGIN(2)
        DEFINE_INDEX_ADD(0, orderid)
        DEFINE_INDEX_ADD(1, owner)
    DEFINE_INDEX_END();

    string to_string();
};


#endif // _COMMENT_LABEL_H_