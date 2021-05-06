#ifndef _VISITOR_H_
#define _VISITOR_H_

#include "xchain/table/types.h"
#include "xchain/json/json.h"
#include "xchain/table/table.tpl.h"
#include "visitor.pb.h"

#include <string>
using namespace std;

class BVisitor: public Visitor {
    DEFINE_ROWKEY(id);
    DEFINE_INDEX_BEGIN(2)
        DEFINE_INDEX_ADD(0, id)
        DEFINE_INDEX_ADD(1, nickname, wechat)
    DEFINE_INDEX_END();

    xchain::json to_json();
};


#endif // _VISITOR_H_