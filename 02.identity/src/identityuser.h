#ifndef _IDENTITY_USER_H_
#define _IDENTITY_USER_H_

#include "xchain/table/types.h"
#include "xchain/json/json.h"
#include "xchain/table/table.tpl.h"
#include "identityuser.pb.h"

#include <string>
using namespace std;

class BIdentityUser: public IdentityUser {
    DEFINE_ROWKEY(id);
    DEFINE_INDEX_BEGIN(5)
        DEFINE_INDEX_ADD(0, id)
        DEFINE_INDEX_ADD(1, nickname, name, wechat, phone)   
        DEFINE_INDEX_ADD(2, email, home_address, born_timestamp)
        DEFINE_INDEX_ADD(3, idcard, otherid, recommender)
        DEFINE_INDEX_ADD(4, approved)
    DEFINE_INDEX_END();

    xchain::json to_json();
};


#endif // _IDENTITY_USER_H_