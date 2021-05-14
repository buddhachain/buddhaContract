#ifndef _IDENTIFY_USER_H_
#define _IDENTIFY_USER_H_

#include "xchain/table/types.h"
#include "xchain/json/json.h"
#include "xchain/table/table.tpl.h"
#include "identifyuser.pb.h"

#include <string>
using namespace std;

class BIdentifyUser: public IdentifyUser {
    DEFINE_ROWKEY(id);
    DEFINE_INDEX_BEGIN(2)
        DEFINE_INDEX_ADD(0, id)
        DEFINE_INDEX_ADD(1, approved)
    DEFINE_INDEX_END();

    xchain::json to_json() const;
};


#endif // _IDENTIFY_USER_H_