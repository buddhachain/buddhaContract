#include <inttypes.h>
#include "xchain/xchain.h"
#include "xchain/account.h"
#include "xchain/contract.pb.h"
#include "xchain/syscall.h"
#include "buddha.pb.h"
#include "buddha.h"

#include <iostream>
using namespace std;

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

bool Buddha::_scan_proposal(xchain::json& ja, const string& cond) {
    auto it = get_proposal_table().scan({{"key",cond}});
    while(it->next() ) {
        proposal ent;
        if (!it->get(&ent) ) {
            mycout << "proposal table get failure : " << it->error(true) << endl;
            return false;
        }

        ja.push_back(ent.to_json());
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
        mycout << "delete proposal " << ent.to_json().dump() << " failure ." << endl ;
        return false;
    }

    mycout << "delete proposal " << ent.to_json().dump() << " success ." << endl ;
    return true;
}

namespace 分界线{}

void Buddha::make_proposal(){
    const string& key = ctx->arg("key");
    if( key.empty() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "key is empty .");
        return ;
    }

    const string& newvalue = ctx->arg("value");
    if( newvalue.empty() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "value is empty .");
        return ;
    }

    const string& timestamp = ctx->arg("timestamp");
    if( timestamp.empty() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "timestamp is empty .");
        return ;
    }

    const string& expire = ctx->arg("expire");
    if( expire.empty() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "expire is empty .");
        return ;
    }

    //判断是否时基金会成员
    if( !is_founder() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__,ctx->initiator() + " is not founder .");
        return ;
    }

    //判断是否已经存在这个提案
    proposal ent;
    if(_is_proposal_exist(key, ent) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "proposal " + key + " is exist .", ent.to_json() );
        return ;
    }

    //获取所有的基金会成员
    xchain::json ja ;
    if(!_scan_founder(ja) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "scan founder failure .");
        return;
    }

    xchain::json jafounder = xchain::json::array();
    xchain::json jaresult = xchain::json::array();
    xchain::json jatimestamp = xchain::json::array();

    for(int i = 0 ; i < ja.size() ; i++) {
        std::string id = ja.at(i)["id"].template get<std::string>();
        jafounder.push_back(id);
        if(id == ctx->initiator() ) {
            //对于提案提出者，直接授权通过
            jaresult.push_back("1");
            jatimestamp.push_back(timestamp);
            continue;
        }
        jaresult.push_back("0");
        jatimestamp.push_back("0");
    }

    ent.set_key(key);                   //设置key
    ent.set_value("");                  //添加的新key，其value先配置为空
    ent.set_owner(ctx->initiator());    //设置提案的所有者
    ent.set_newvalue(newvalue);         //配置新的key，对应的新的value值
    ent.set_operate("0");               //操作为添加
    ent.set_timestamp(timestamp);       //设置发起提案的时间
    ent.set_expire(expire);             //设置提案通过的过期时间，其他基金会成员要在此时间内进行通过或不通过，否则此提案被设置为过期
    ent.set_count(ja.size());           //设置发起提案时的基金会成员个数
    ent.set_founders(jafounder.dump()); //设置发起提案时的基金会成员列表
    ent.set_results(jaresult.dump());   //设置各个基金会成员对提案操作的结果列表
    ent.set_timestamps(jatimestamp.dump()); //设置各个基金会成员对提案的操作时间

    if (!get_proposal_table().put(ent) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "table put failure .", ent.to_json());
        return;
    }

    _log_ok(__FILE__, __FUNCTION__, __LINE__, key + " apply proposal over, please wait for approve .", ent.to_json() );
}

void Buddha::delete_proposal(){
    const string& key = ctx->arg("key");
    if( key.empty() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "key is empty .");
        return ;
    }

    const string& timestamp = ctx->arg("timestamp");
    if( timestamp.empty() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "timestamp is empty .");
        return ;
    }

    const string& expire = ctx->arg("expire");
    if( expire.empty() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "expire is empty .");
        return ;
    }

    //判断是否时基金会成员
    if( !is_founder() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__,ctx->initiator() + " is not founder .");
        return ;
    }

    //判断是否已经存在这个提案
    proposal ent;
    if(!_is_proposal_exist(key, ent) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "proposal " + key + " is not exist ." );
        return ;
    }

    //获取所有的基金会成员
    xchain::json ja ;
    if(!_scan_founder(ja) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "scan founder failure .");
        return;
    }

    xchain::json jafounder = xchain::json::array();
    xchain::json jaresult = xchain::json::array();
    xchain::json jatimestamp = xchain::json::array();

    for(int i = 0 ; i < ja.size() ; i++) {
        std::string id = ja.at(i)["id"].template get<std::string>();
        jafounder.push_back(id);
        if( id == ctx->initiator() ) {
            //对于提案提出者，直接授权通过
            jaresult.push_back("1");
            jatimestamp.push_back(timestamp);
            continue;
        }
        jaresult.push_back("0");
        jatimestamp.push_back("0");
    }

    // ent.set_key(key);                   //key值保持不变
    // ent.set_value("");                  //通过前保持原值不变
    ent.set_owner(ctx->initiator());    //设置提案的所有者,这个提案所有者可能不同于原提案创建者
    // ent.set_newvalue(newvalue);         //删除时，不需要新值配置
    ent.set_operate("1");               //操作为删除
    ent.set_timestamp(timestamp);       //设置删除提案的时间
    ent.set_expire(expire);             //设置删除提案通过的过期时间，其他基金会成员要在此时间内进行通过或不通过，否则此提案被设置为过期
    ent.set_count(ja.size());           //设置删除提案时的基金会成员个数
    ent.set_founders(jafounder.dump());      //设置删除提案时的基金会成员列表，此时的基金会列表，不同于发起时的基金会列表，基金会列表以当时的所有基金会成员为准
    ent.set_results(jaresult.dump());   //设置各个基金会成员对提案操作的结果列表
    ent.set_timestamps(jatimestamp.dump()); //设置各个基金会成员对提案的操作时间

    if (!get_proposal_table().put(ent) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "table put failure .", ent.to_json());
        return;
    }

    _log_ok(__FILE__, __FUNCTION__, __LINE__, key + " apply proposal over, please wait for approve .", ent.to_json() );
}

void Buddha::update_proposal(){
    const string& key = ctx->arg("key");
    if( key.empty() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "key is empty .");
        return ;
    }

    const string& newvalue = ctx->arg("value");
    if( newvalue.empty() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "value is empty .");
        return ;
    }

    const string& timestamp = ctx->arg("timestamp");
    if( timestamp.empty() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "timestamp is empty .");
        return ;
    }

    const string& expire = ctx->arg("expire");
    if( expire.empty() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "expire is empty .");
        return ;
    }

    //判断是否时基金会成员
    if( !is_founder() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__,ctx->initiator() + " is not founder .");
        return ;
    }

    //判断是否已经存在这个提案
    proposal ent;
    if(!_is_proposal_exist(key, ent) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "proposal " + key + " is not exist ." );
        return ;
    }

    //获取所有的基金会成员
    xchain::json ja ;
    if(!_scan_founder(ja) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "scan founder failure .");
        return;
    }

    xchain::json jafounder = xchain::json::array();
    xchain::json jaresult = xchain::json::array();
    xchain::json jatimestamp = xchain::json::array();

    for(int i = 0 ; i < ja.size() ; i++) {
        std::string id = ja.at(i)["id"].template get<std::string>();
        jafounder.push_back(id);
        if(id == ctx->initiator() ) {
            //对于提案提出者，直接授权通过
            jaresult.push_back("1");
            jatimestamp.push_back(timestamp);
            continue;
        }
        jaresult.push_back("0");
        jatimestamp.push_back("0");
    }

    // ent.set_key(key);                   //key值保持不变
    // ent.set_value("");                  //通过前保持原值不变
    ent.set_owner(ctx->initiator());    //设置提案的所有者,这个提案所有者可能不同于原提案创建者
    ent.set_newvalue(newvalue);         //修改提案配置的新值
    ent.set_operate("2");               //操作为修改
    ent.set_timestamp(timestamp);       //设置修改提案的时间
    ent.set_expire(expire);             //设置修改提案通过的过期时间，其他基金会成员要在此时间内进行通过或不通过，否则此提案被设置为过期
    ent.set_count(ja.size());           //设置修改提案时的基金会成员个数
    ent.set_founders(jafounder.dump()); //设置修改提案时的基金会成员列表，此时的基金会列表，不同于发起时的基金会列表，基金会列表以当时的所有基金会成员为准
    ent.set_results(jaresult.dump());   //设置各个基金会成员对提案操作的结果列表
    ent.set_timestamps(jatimestamp.dump()); //设置各个基金会成员对提案的操作时间

    if (!get_proposal_table().put(ent) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "table put failure .", ent.to_json());
        return;
    }

    _log_ok(__FILE__, __FUNCTION__, __LINE__, key + " apply proposal over, please wait for approve .", ent.to_json() );
}

void Buddha::approve_proposal(){
    const string& key = ctx->arg("key");
    if( key.empty() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "key is empty .");
        return ;
    }

    const string& timestamp = ctx->arg("timestamp");
    if( timestamp.empty() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "timestamp is empty .");
        return ;
    }

    //判断是否时基金会成员
    if( !is_founder() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__,ctx->initiator() + " is not founder .");
        return ;
    }

    //判断是否已经存在这个提案
    proposal ent;
    if(!_is_proposal_exist(key, ent) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "proposal " + key + " is not exist ." );
        return ;
    }

    //判断是否过期
    if(ent.expire() < timestamp) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "proposal " + key + " is expired, yet ." );
        return ;
    }

    //获取所有的基金会成员
    xchain::json ja ;
    if(!_scan_founder(ja) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "scan founder failure .");
        return;
    }


    xchain::json jafounder = xchain::json::array(ent.founders());
    xchain::json jaresult = xchain::json::array(ent.results());
    xchain::json jatimestamp = xchain::json::array(ent.timestamps());
    jafounder.push_back(ctx->initiator();
    jaresult.push_back("1");
    jatimestamp.push_back(timestamp);

    // ent.set_key(key);                   //key值保持不变
    // ent.set_owner(ctx->initiator());    //授权通过，提案所有者不变
    // ent.set_operate("2");               //授权通过，提案操作不变
    // ent.set_timestamp(timestamp);       //授权通过，修改提案的时间不变
    // ent.set_expire(expire);             //授权通过，修改提案的时间不变
    // ent.set_count(ja.size());           //设置修改提案时的基金会成员个数
    ent.set_founders(jafounder.dump()); //设置修改提案时的基金会成员列表，此时的基金会列表，不同于发起时的基金会列表，基金会列表以当时的所有基金会成员为准
    ent.set_results(jaresult.dump());   //设置各个基金会成员对提案操作的结果列表
    ent.set_timestamps(jatimestamp.dump()); //设置各个基金会成员对提案的操作时间

    // 如果基金会成员个数已满足，并且每个基金会成员都是通过的，则修改提案
    if() {
        ent.set_value("");                  //通过前保持原值
        ent.set_newvalue(newvalue);         //修改提案配置的新值
    }

    if (!get_proposal_table().put(ent) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "table put failure .", ent.to_json());
        return;
    }

    _log_ok(__FILE__, __FUNCTION__, __LINE__, key + " apply proposal over, please wait for approve .", ent.to_json() );
}

void Buddha::recusal_proposal(){

}

void Buddha::find_proposal(){
    const string& key = ctx->arg("key");
    if( key.empty() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "proposal key is empty .");
        return ;
    }

    //判断提案是否存在
    proposal ent;
    if (!_is_proposal_exist(key, ent))  {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "proposal " + key + " is not exist .");
        return ;
    }

    _log_ok(__FILE__, __FUNCTION__, __LINE__, "find", ent.to_json());
}

void Buddha::list_proposal(){
    //身份检查，部署者和基金会成员具有权限
    if( !is_deployer() &&
        !is_founder() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__,ctx->initiator() + " is not deployer nor founder, have no authority to list proposal .");
        return ;
    }

    //获取所有提案
    xchain::json ja;
    if(!_scan_proposal(ja) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "scan proposal failure .");
        return;
    }

    _log_ok(__FILE__, __FUNCTION__, __LINE__, "size=" + to_string(ja.size()), ja);
}



DEFINE_METHOD(Buddha, make_proposal)            { self.make_proposal();             }
DEFINE_METHOD(Buddha, delete_proposal)          { self.delete_proposal();           }
DEFINE_METHOD(Buddha, update_proposal)          { self.update_proposal();           }
DEFINE_METHOD(Buddha, approve_proposal)         { self.approve_proposal();          }
DEFINE_METHOD(Buddha, recusal_proposal)         { self.recusal_proposal();          }
DEFINE_METHOD(Buddha, find_proposal)            { self.find_proposal();             }
DEFINE_METHOD(Buddha, list_proposal)            { self.list_proposal();             }