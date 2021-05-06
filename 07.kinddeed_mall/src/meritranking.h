#ifndef _MERIT_RANKING_H_
#define _MERIT_RANKING_H_

#include "xchain/table/types.h"
#include "xchain/json/json.h"
#include "xchain/table/table.tpl.h"
#include "buddha.pb.h"

#include <string>
using namespace std;

class BMeritRanking: public MeritRanking {
    DEFINE_ROWKEY(ranking);
    DEFINE_INDEX_BEGIN(2)
        DEFINE_INDEX_ADD(0, ranking)
        DEFINE_INDEX_ADD(1, id)   
    DEFINE_INDEX_END();

    xchain::json to_json();
};

#endif // _MERIT_RANKING_H_