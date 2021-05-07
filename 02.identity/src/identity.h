#ifndef _IDENTITY_H_
#define _IDENTITY_H_

#include "xchain/table/types.h"
#include "xchain/json/json.h"
#include "xchain/table/table.tpl.h"
#include "identity.pb.h"

#include <string>
using namespace std;

const int64_t VISITOR         = 1;
const int64_t USER            = 2;
const int64_t IDENTITY_USER   = 3;
const int64_t MASTER          = 4;
const int64_t TEMPLE          = 5;
const int64_t THEDEAD         = 6;


class BIdentity: public Identity {
    DEFINE_ROWKEY(id);    
    DEFINE_INDEX_BEGIN(2)
        DEFINE_INDEX_ADD(0, id)
        DEFINE_INDEX_ADD(1, type)
    DEFINE_INDEX_END();

    xchain::json to_json() const;
};


#endif // _IDENTITY_H_