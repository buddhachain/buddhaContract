#include <inttypes.h>
#include "xchain/json/json.h"
#include "xchain/xchain.h"
#include "xchain/account.h"
#include "xchain/contract.pb.h"
#include "xchain/syscall.h"
#include "buddha.pb.h"
#include "buddha.h"

#include <iostream>
using namespace std;


void Buddha::make_proposal(){
    const string& key = ctx->arg("key");
    if( key.empty()) {
        _log_error(__FUNCTION__, __LINE__,"key is empty .");
        return ;
    }

    const string& newvalue = ctx->arg("value");
    if( newvalue.empty()) {
        _log_error(__FUNCTION__, __LINE__,"value is empty .");
        return ;
    }

    const string& timestamp = ctx->arg("timestamp");
    if( timestamp.empty()) {
        _log_error(__FUNCTION__, __LINE__,"timestamp is empty .");
        return ;
    }

    const string& expire = ctx->arg("expire");
    if( expire.empty()) {
        _log_error(__FUNCTION__, __LINE__,"expire is empty .");
        return ;
    }

    //判断是否时基金会成员
    if( !is_founder()) {
        _log_error(__FUNCTION__, __LINE__,ctx->initiator() + " is not founder .");
        return ;
    }

    //判断是否已经存在这个提案
    proposal ent;
    if(_is_proposal_exist(key, ent)) {
        _log_error(__FUNCTION__, __LINE__,"proposal " + key + " is exist .");
        return ;
    }

    //获取所有的基金会成员
    xchain::json v ;
    if(!_scan_founder(v) ) {
        _log_error(__FUNCTION__, __LINE__, "scan founder failure .");
        return;
    }

    xchain::json id_array = xchain::json::array();
    xchain::json result_array = xchain::json::array();
    xchain::json timestamp_array = xchain::json::array();
    for( auto& e : v) {
        id_array.push_back(e.id());
        if(e.id() == ctx->initiator()) {
            result_array.push_back("1");
            timestamp_array.push_back(timestamp);
            continue;
        }
        result_array.push_back("0");
        timestamp_array.push_back("0");
    }

    //删除此提案
    _delete_proposal_record(key);

    ent.set_key(key);
    ent.set_value("");
    ent.set_owner(ctx->initiator());    
    ent.set_newvalue(newvalue);
    ent.set_operate("0");
    ent.set_timestamp(timestamp);
    ent.set_expire(expire);
    ent.set_count(v.size());
    ent.set_founders(id_array.dump().c_str());
    ent.set_results(result_array.dump());
    ent.set_timestamps(timestamp_array.dump());

    if (!get_proposal_table().put(ent)) {
        _log_error(__FUNCTION__, __LINE__,"proposal table put " + ent.to_string() + " failure .");
        return;
    }

    _log_ok(__FUNCTION__, __LINE__, ent.to_string() + " apply proposal over, please wait for approve .");

}

void Buddha::delete_proposal(){

}

void Buddha::update_proposal(){

}

void Buddha::approve_proposal(){

}

void Buddha::recusal_proposal(){

}

void Buddha::find_proposal(){

}

void Buddha::list_proposal(){

}



DEFINE_METHOD(Buddha, make_proposal)            { self.make_proposal();             }
DEFINE_METHOD(Buddha, delete_proposal)          { self.delete_proposal();           }
DEFINE_METHOD(Buddha, update_proposal)          { self.update_proposal();           }
DEFINE_METHOD(Buddha, approve_proposal)         { self.approve_proposal();          }
DEFINE_METHOD(Buddha, recusal_proposal)         { self.recusal_proposal();          }
DEFINE_METHOD(Buddha, find_proposal)            { self.find_proposal();             }
DEFINE_METHOD(Buddha, list_proposal)            { self.list_proposal();             }