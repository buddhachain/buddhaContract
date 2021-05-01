#ifndef _VISITOR_H_
#define _VISITOR_H_

#include "xchain/table/types.h"
#include "xchain/json/json.h"
#include "xchain/table/table.tpl.h"
#include "visitor.pb.h"

#include <string>
using namespace std;

class BVisitor: public Visitor {
    DEFINE_ROWKEY(id);                  //主键
    DEFINE_INDEX_BEGIN(1)
        DEFINE_INDEX_ADD(0, id, nickname, wechat)   //只主键能find，也支持scan
    DEFINE_INDEX_END();

    xchain::json to_json();
};


#endif // _VISITOR_H_