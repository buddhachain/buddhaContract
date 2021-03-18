#include <inttypes.h>
#include "xchain/xchain.h"
#include "xchain/account.h"
#include "xchain/contract.pb.h"
#include "xchain/syscall.h"
#include "buddha.pb.h"
#include "buddha.h"

#include <iostream>
using namespace std;

string proposal::to_string() {
    string str ;
    str += "{" ;
    str += key() + ",";
    str += value() + ",";
    str += owner() + ",";
    str += newvalue() + ",";
    str += operate() + ",";
    str += timestamp() + ",";
    str += expire() + ",";
    str += std::to_string(count()) + ",";
    str += founders() + ",";
    str += results() + ",";
    str += timestamps();
    str += "}";
    return str;
}

xchain::json proposal::to_json() {
    xchain::json j = {
        {"key", key()},
        {"value", value()},
        {"owner", owner()},
        {"newvalue", newvalue()},
        {"operate", operate()},
        {"timestamp", timestamp()},
        {"expire", expire()},
        {"count", count()},
        {"founders", founders()},
        {"results", results()},
        {"timestamps", timestamps()},
    };

    return j;
}

bool Buddha::_is_proposal_exist(const string& key,proposal& ent) {
    if (!get_proposal_table().find({{"key", key}}, &ent))
        return false;

    return true;
}

bool Buddha::_scan_proposal(xchain::json& v, const string& cond) {
    auto it = get_proposal_table().scan({{"key",cond}});
    while(it->next()) {
        proposal ent;
        if (!it->get(&ent)) {
            mycout << "proposal table get failure : " << it->error(true) << endl;
            return false;
        }

        v.push_back(ent.to_json());
    }

    return true;
}

bool Buddha::_delete_proposal_record(const string& key) {
    proposal ent;
    if (!_is_proposal_exist(key, ent)){
        mycout << "proposal " << key << " is not exist ." << endl ;
        return false;
    }

    if( !get_proposal_table().del(ent) ) {
        mycout << "delete proposal " << ent.to_string() << " failure ." << endl ;
        return false;
    }

    mycout << "delete proposal " << ent.to_string() << " success ." << endl ;
    return true;
}

namespace 分界线{}

void Buddha::make_proposal(){
    const string& key = ctx->arg("key");
    if( key.empty()) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "key is empty .");
        return ;
    }

    const string& newvalue = ctx->arg("value");
    if( newvalue.empty()) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "value is empty .");
        return ;
    }

    const string& timestamp = ctx->arg("timestamp");
    if( timestamp.empty()) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "timestamp is empty .");
        return ;
    }

    const string& expire = ctx->arg("expire");
    if( expire.empty()) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "expire is empty .");
        return ;
    }

    //判断是否时基金会成员
    if( !is_founder()) {
        _log_error(__FILE__, __FUNCTION__, __LINE__,ctx->initiator() + " is not founder .");
        return ;
    }

    //判断是否已经存在这个提案
    proposal ent;
    if(_is_proposal_exist(key, ent)) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "proposal " + key + " is exist .");
        return ;
    }

    //获取所有的基金会成员
    xchain::json v ;
    if(!_scan_founder(v) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "scan founder failure .");
        return;
    }

    xchain::json id_array = xchain::json::array();
    xchain::json result_array = xchain::json::array();
    xchain::json timestamp_array = xchain::json::array();

    for(int i = 0 ; i < v.size() ; i++) {
        std::string id = v.at(i)["id"].template get<std::string>();
        id_array.push_back(id);
        if(id == ctx->initiator()) {
            //对于提案提出者，直接授权通过
            result_array.push_back("1");
            timestamp_array.push_back(timestamp);
            continue;
        }
        result_array.push_back("0");
        timestamp_array.push_back("0");
    }

    ent.set_key(key);
    ent.set_value("");
    ent.set_owner(ctx->initiator());    
    ent.set_newvalue(newvalue);
    ent.set_operate("0");
    ent.set_timestamp(timestamp);
    ent.set_expire(expire);
    ent.set_count(v.size());
    ent.set_founders(id_array.dump());
    ent.set_results(result_array.dump());
    ent.set_timestamps(timestamp_array.dump());

    if (!get_proposal_table().put(ent)) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "table put failure .", ent.to_json());
        return;
    }

    _log_ok(__FILE__, __FUNCTION__, __LINE__, ent.to_string() + " apply proposal over, please wait for approve .");

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