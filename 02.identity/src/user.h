#ifndef _USER_H_
#define _USER_H_

#include "xchain/table/types.h"
#include "xchain/json/json.h"
#include "xchain/table/table.tpl.h"
#include "user.pb.h"

#include <string>
using namespace std;

class BUser: public User {
    DEFINE_ROWKEY(id);                  //主键
    DEFINE_INDEX_BEGIN(11)
        DEFINE_INDEX_ADD(0, id)         //只主键能find，也支持scan
        DEFINE_INDEX_ADD(1, nickname)   //非主键不能find，支持scan
        DEFINE_INDEX_ADD(2, name)       //非主键不能find，支持scan
        DEFINE_INDEX_ADD(3, wechat)     //非主键不能find，支持scan
        DEFINE_INDEX_ADD(4, phone)      //非主键不能find，支持scan
        DEFINE_INDEX_ADD(5, email)      //非主键不能find，支持scan
        DEFINE_INDEX_ADD(6, home_address)   //非主键不能find，支持scan
        DEFINE_INDEX_ADD(7, born_timestamp) //非主键不能find，支持scan
        DEFINE_INDEX_ADD(8, idcard)     //非主键不能find，支持scan
        DEFINE_INDEX_ADD(9, otherid)    //非主键不能find，支持scan
        DEFINE_INDEX_ADD(10, recommender)//非主键不能find，支持scan
    DEFINE_INDEX_END();

    xchain::json to_json();
};


#endif // _USER_H_