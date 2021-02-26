#ifndef _COMMENT_H_
#define _COMMENT_H_

#include "xchain/table/types.h"
#include "xchain/table/table.tpl.h"
#include "buddha.pb.h"

#include <string>

class commentlabel: public buddha::CommentLabel {
    DEFINE_ROWKEY(id);
    DEFINE_INDEX_BEGIN(1)
        DEFINE_INDEX_ADD(0, id)
    DEFINE_INDEX_END();

    std::string to_string();
};

class beforecomment: public buddha::BeforeComment {
    DEFINE_ROWKEY(memberid,kdid);
    DEFINE_INDEX_BEGIN(1)
        DEFINE_INDEX_ADD(0, memberid, kdid)
    DEFINE_INDEX_END();

    std::string to_string();
};

class aftercomment: public buddha::AfterComment {
    DEFINE_ROWKEY(memberid, orderid);
    DEFINE_INDEX_BEGIN(1)
        DEFINE_INDEX_ADD(0, memberid, orderid)
    DEFINE_INDEX_END();

    std::string to_string();
};


#endif // _COMMENT_LABEL_H_