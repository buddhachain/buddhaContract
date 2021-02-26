#ifndef _MEMBER_H_
#define _MEMBER_H_

#include "xchain/table/types.h"
#include "xchain/table/table.tpl.h"
#include "buddha.pb.h"

#include <string>

class member: public buddha::Member {
    DEFINE_ROWKEY(id);
    DEFINE_ROWKEY(email);
    DEFINE_ROWKEY(phone);
    DEFINE_INDEX_BEGIN(3)
        DEFINE_INDEX_ADD(0, id)
        DEFINE_INDEX_ADD(0, email)
        DEFINE_INDEX_ADD(0, phone)
    DEFINE_INDEX_END();

    std::string to_string();
};
#endif // _MEMBER_H_