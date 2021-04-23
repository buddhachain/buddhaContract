#ifndef _MERIT_RANKING_H_
#define _MERIT_RANKING_H_

#include "xchain/table/types.h"
#include "xchain/json/json.h"
#include "xchain/table/table.tpl.h"
#include "buddha.pb.h"

#include <string>
using namespace std;

class BMeritRanking: public buddha::MeritRanking {
    DEFINE_ROWKEY(ranking);          //主键
    DEFINE_INDEX_BEGIN(2)
        DEFINE_INDEX_ADD(0, ranking) //只主键能find，也支持scan
        DEFINE_INDEX_ADD(1, id)      //非主键不能find，支持scan
    DEFINE_INDEX_END();

    xchain::json to_json();
};

#endif // _MERIT_RANKING_H_