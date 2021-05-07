#ifndef _GUARANTY_H_
#define _GUARANTY_H_

#include "xchain/table/types.h"
#include "xchain/json/json.h"
#include "xchain/table/table.tpl.h"
#include "guaranty.pb.h"

#include <string>
using namespace std;

class BGuaranty: public otc::Guaranty {
    DEFINE_ROWKEY(id);
    DEFINE_INDEX_BEGIN(2)
        DEFINE_INDEX_ADD(0, id)
        DEFINE_INDEX_ADD(1, seller)  
    DEFINE_INDEX_END();

    xchain::json to_json() const;
};


#endif // _GUARANTY_H_