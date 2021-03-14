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


void Buddha::add_kinddeeddetail() {
    const string& id = ctx->arg("id");
    const string& sequence = ctx->arg("sequence");
    const string& hash = ctx->arg("hash");
    if (!_add_kinddeeddetail(id,sequence,hash)) {
        _log_error(__FUNCTION__, __LINE__,"_add_kinddeeddetail " + id + " failure .");
        return;
    }

    _log_ok("ok");
}

void Buddha::add_kinddeedspec() {
    const string& id = ctx->arg("id");    
    const string& sequence = ctx->arg("sequence");
    const string& desc = ctx->arg("desc");
    const string& price = ctx->arg("price");
    if (!_add_kinddeedspec(id,sequence,desc,price)) {
        _log_error(__FUNCTION__, __LINE__,"_add_kinddeedspec " + id + " failure .");
        return;
    }

    _log_ok("ok");
}

void Buddha::add_kinddeed() {
    const string& id = ctx->arg("id");
    const string& name = ctx->arg("name");
    const string& owner = ctx->initiator();
    const string& type = ctx->arg("type");
    const string& lasttime = ctx->arg("lasttime");
    const string& detail = ctx->arg("detail");
    const string& spec = ctx->arg("spec");

    if( id.empty()) {
        _log_error(__FUNCTION__, __LINE__,"kinddeed id is empty .");
        return ;
    }

    if( name.empty()) {
        _log_error(__FUNCTION__, __LINE__,"kinddeed name is empty .");
        return ;
    }

    if( type.empty()) {
        _log_error(__FUNCTION__, __LINE__,"kinddeed type is empty .");
        return ;
    }

    if( lasttime.empty()) {
        _log_error(__FUNCTION__, __LINE__,"kinddeed lasttime is empty .");
        return ;
    }
    
    auto detail_array = xchain::json::parse(detail);
    // mycout << detail_array.dump() << endl ;
    if (!detail_array.is_array()) {
        _log_error(__FUNCTION__, __LINE__,"field 'detail' need to be array .");
        return;
    }
    
    if ( detail_array.empty() || detail_array.size() == 0) {
        _log_error(__FUNCTION__, __LINE__,"filed 'detail' empty .");
        return;
    }

    auto spec_array = xchain::json::parse(spec);
    // mycout << spec_array.dump() << endl ;
    if (!spec_array.is_array()) {
        _log_error(__FUNCTION__, __LINE__,"field 'spec' need to be array .");
        return;
    }
    
    if ( spec_array.empty() || spec_array.size() == 0) {
        _log_error(__FUNCTION__, __LINE__,"filed 'spec' empty .");
        return;
    }

    if( !is_founder() &&
        !is_temple() &&
        !is_master() ) {
        _log_error(__FUNCTION__, __LINE__,ctx->initiator() + " is not founder,temple and master, have no authority to add kinddeed .");
        return ;
    }

    //判断善举是否存在
    kinddeed ent;
    if (_is_kinddeed_exist(id, ent))  {
        _log_error(__FUNCTION__, __LINE__,"kinddeed " + ent.to_string() + " is exist .");
        return ;
    }

    //判断善举类型是否存在
    kinddeedtype type_ent;
    if (!_is_kinddeedtype_exist(type, type_ent))  {
        _log_error(__FUNCTION__, __LINE__,"kinddeedtype " + type + " is not exist .");
        return ;
    }

    // vector<kinddeeddetail> v_kinddeeddetail_ent;
    // if (_is_kinddeeddetail_exist_by_kdid(id, v_kinddeeddetail_ent))  {
    //     _log_error(__FUNCTION__, __LINE__,"kinddeeddetail " + ent.to_string() + " is exist .");
    //     return ;
    // }

    // vector<kinddeedspec> v_kinddeedspec_ent;
    // if (_is_kinddeedspec_exist_by_kdid(id, v_kinddeedspec_ent))  {
    //     _log_error(__FUNCTION__, __LINE__,"kinddeedspec " + ent.to_string() + " is exist .");
    //     return ;
    // }


    if( !_delete_kinddeeddetail_records(id) ) {
        _log_error(__FUNCTION__, __LINE__, "delete kinddeeddetail " + id + " failure .");
        return;
    }

    if( !_delete_kinddeedspec_records(id) ) {
        _log_error(__FUNCTION__, __LINE__, "delete kinddeedspec " + id + " failure .") ;
        return;
    }

    for(int i = 0 ; i < detail_array.size() ; i++) {
        string sequence = detail_array.at(i)["sequence"].template get<string>();
        string hash = detail_array.at(i)["hash"].template get<string>();        
        if (!_add_kinddeeddetail(id,sequence,hash)) {
            _log_error(__FUNCTION__, __LINE__,"_add_kinddeeddetail " + id + " failure .");
            return;
        }
    }

    // mycout << spec_array.dump() << endl ;
    for(int i = 0 ; i < spec_array.size() ; i++) {
        string sequence = spec_array.at(i)["sequence"].template get<string>();
        string desc = spec_array.at(i)["desc"].template get<string>();
        string price = spec_array.at(i)["price"].template get<string>();

        if (!_add_kinddeedspec(id,sequence,desc,price)) {
            _log_error(__FUNCTION__, __LINE__,"_add_kinddeedspec " + id + " failure .");
            return;
        }
    }

    ent.set_id(id);
    ent.set_name(name);
    ent.set_owner(ctx->initiator());
    ent.set_type(stoll(type));
    ent.set_lasttime(lasttime);
    ent.set_applied(false);
    ent.set_online(false);

    if (!get_kinddeed_table().put(ent)) {
        _log_error(__FUNCTION__, __LINE__,"kinddeed table put " + ent.to_string() + " failure .");
        return;
    }

    _log_ok("add kinddeed " + ent.to_string() + " success .");
}

void Buddha::delete_kinddeed() {

    const string& id = ctx->arg("id");
    if( id.empty()) {
        _log_error(__FUNCTION__, __LINE__,"kinddeed id is empty .");
        return ;
    }

    //判断善举是否存在
    kinddeed ent;
    if (!_is_kinddeed_exist(id, ent))  {
        _log_error(__FUNCTION__, __LINE__,"kinddeed " + id + " is not exist .");
        return ;
    }

    if( !is_founder() &&
        !is_temple() &&
        !is_master() ) {
        _log_error(__FUNCTION__, __LINE__,ctx->initiator() + " is not founder and master, have no authority to delete kinddeed .");
        return ;
    }

    if( ent.owner() != ctx->initiator() ) {
        _log_error(__FUNCTION__, __LINE__,"kinddeed " + ent.to_string() + " is not belong to you .");
        return ;
    }

    if( !_delete_kinddeed_record(id) ) {
        _log_error(__FUNCTION__, __LINE__,"delete kinddeed " + ent.to_string() + " failure .");
        return;
    }

    _log_ok("delete kinddeed " + ent.to_string() + " success .");
}

void Buddha::update_kinddeed() {
    const string& id = ctx->arg("id");
    const string& name = ctx->arg("name");
    const string& owner = ctx->initiator();
    const string& type = ctx->arg("type");
    const string& lasttime = ctx->arg("lasttime");
    const string& detail = ctx->arg("detail");
    const string& spec = ctx->arg("spec");

    if( id.empty()) {
        _log_error(__FUNCTION__, __LINE__,"kinddeed id is empty .");
        return ;
    }

    if( name.empty()) {
        _log_error(__FUNCTION__, __LINE__,"kinddeed name is empty .");
        return ;
    }

    if( type.empty()) {
        _log_error(__FUNCTION__, __LINE__,"kinddeed type is empty .");
        return ;
    }

    if( lasttime.empty()) {
        _log_error(__FUNCTION__, __LINE__,"kinddeed lasttime is empty .");
        return ;
    }

    auto detail_array = xchain::json::parse(detail);
    // mycout << detail_array.dump() << endl ;
    if (!detail_array.is_array()) {
        _log_error(__FUNCTION__, __LINE__,"field 'detail' need to be array .");
        return;
    }
    
    if ( detail_array.empty() || detail_array.size() == 0) {
        _log_error(__FUNCTION__, __LINE__,"filed 'detail' empty .");
        return;
    }

    auto spec_array = xchain::json::parse(spec);
    // mycout << spec_array.dump() << endl ;
    if (!spec_array.is_array()) {
        _log_error(__FUNCTION__, __LINE__,"field 'spec' need to be array .");
        return;
    }
    
    if ( spec_array.empty() || spec_array.size() == 0) {
        _log_error(__FUNCTION__, __LINE__,"filed 'spec' empty .");
        return;
    }

    if( !is_founder() &&
        !is_temple() &&
        !is_master() ) {
        _log_error(__FUNCTION__, __LINE__,ctx->initiator() + " is not founder and master, have no authority to update kinddeed .");
        return ;
    }

    //判断善举是否存在
    kinddeed ent;
    if (_is_kinddeed_exist(id, ent))  {
        _log_error(__FUNCTION__, __LINE__,"kinddeed " + ent.to_string() + " is exist .");
        return ;
    }

    //判断善举类型是否存在
    kinddeedtype type_ent;
    if (!_is_kinddeedtype_exist(type, type_ent))  {
        _log_error(__FUNCTION__, __LINE__,"kinddeedtype " + type + " is not exist .");
        return ;
    }

    //判断善举描述是否存在
    vector<kinddeeddetail> v_kinddeeddetail_ent;
    if (_is_kinddeeddetail_exist_by_kdid(id, v_kinddeeddetail_ent))  {
        _log_error(__FUNCTION__, __LINE__,"kinddeeddetail " + ent.to_string() + " is exist .");
        return ;
    }

    //判断善举规格是否存在
    vector<kinddeedspec> v_kinddeedspec_ent;
    if (_is_kinddeedspec_exist_by_kdid(id, v_kinddeedspec_ent))  {
        _log_error(__FUNCTION__, __LINE__,"kinddeedspec " + ent.to_string() + " is exist .");
        return ;
    }

    for(int i = 0 ; i < detail_array.size() ; i++) {
        int64_t sequence = stoll(detail_array.at(i)["sequence"].template get<string>());
        string hash = detail_array.at(i)["hash"].template get<string>();

        kinddeeddetail ent;
        ent.set_kdid(id);
        ent.set_sequence(sequence);
        ent.set_hash(hash);

        if (!get_kinddeeddetail_table().put(ent)) {
            _log_error(__FUNCTION__, __LINE__,"kinddeeddetail table put " + ent.to_string() + " failure .");
            return;
        }
    }
    
    for(int i = 0 ; i < spec_array.size() ; i++) {
        int64_t sequence = stoll(spec_array.at(i)["sequence"].template get<string>());
        string desc = spec_array.at(i)["desc"].template get<string>();
        int64_t price = stoll(spec_array.at(i)["price"].template get<string>());

        kinddeedspec ent;
        ent.set_kdid(id);
        ent.set_sequence(sequence);
        ent.set_desc(desc);
        ent.set_price(price);

        if (!get_kinddeedspec_table().put(ent)) {
            _log_error(__FUNCTION__, __LINE__,"kinddeedspec table put " + ent.to_string() + " failure .");
            return;
        }
    }

    ent.set_id(id);
    ent.set_name(name);
    ent.set_owner(ctx->initiator());
    ent.set_type(stoll(type));
    ent.set_lasttime(lasttime);
    ent.set_applied(false);
    ent.set_online(false);

    if (!get_kinddeed_table().put(ent)) {
        _log_error(__FUNCTION__, __LINE__,"kinddeed table put " + ent.to_string() + " failure .");
        return;
    }

    _log_ok("update kinddeed " + ent.to_string() + " success .");
}

void Buddha::find_kinddeed() {       

    const string& id = ctx->arg("id");
    if( id.empty()) {
        _log_error(__FUNCTION__, __LINE__,"kinddeed id is empty .");
        return ;
    }

    //判断善举是否存在
    kinddeed kinddeed_ent;
    if (!_is_kinddeed_exist(id, kinddeed_ent))  {
        _log_ok("kinddeed " + id + " is not exist .");
        return ;
    }

    //获取善举描述
    vector<kinddeeddetail> v_kinddeeddetail_ent;
    _is_kinddeeddetail_exist_by_kdid(id, v_kinddeeddetail_ent);
    string detail_string ;
    for(int i = 0 ; i < v_kinddeeddetail_ent.size() ; i++ ) {
        detail_string += v_kinddeeddetail_ent[i].to_string();
    }

    //获取善举规格
    vector<kinddeedspec> v_kinddeedspec_ent;
    _is_kinddeedspec_exist_by_kdid(id, v_kinddeedspec_ent);
    string spec_string ;
    for(int i = 0 ; i < v_kinddeedspec_ent.size() ; i++ ) {
        spec_string += v_kinddeedspec_ent[i].to_string();
    }

    _log_ok(kinddeed_ent.to_string() + detail_string + spec_string);
}

void Buddha::list_kinddeed() {        
    if( is_deployer() ||
        is_founder() ) {    //善举过多时，此时不安全，尽可能少调用
        auto it = get_kinddeed_table().scan({{"id",ctx->arg("id")}});
        int i = 0;
        string ret;
        while(it->next()) {
            kinddeed ent;
            if (!it->get(&ent)) {
                _log_error(__FUNCTION__, __LINE__, "kinddeed table get failure : " + it->error(true));
                return;
            }
            i++;
            ret += ent.to_string();
        }
        _log_ok("size=" + to_string(i) + " " + ret);
        return ;
    }

    if( is_temple() ||
        is_master() ) {    //善举过多时，此时不安全，不过一般不会太多。
        auto it = get_kinddeed_table().scan({{"owner",ctx->initiator()}});
        int i = 0;
        string ret;
        while(it->next()) {
            kinddeed ent;
            if (!it->get(&ent)) {
                _log_error(__FUNCTION__, __LINE__, "kinddeed table get failure : " + it->error(true));
                return;
            }

            i++;
            ret += ent.to_string();
        }
        _log_ok("size=" + to_string(i) + " " + ret);
        return ;
    }

    _log_error(__FUNCTION__, __LINE__,ctx->initiator() + " have no authority to list kinddeed .");
}

void Buddha::list_kinddeeddetail() {        
    if( !is_deployer() &&
        !is_founder() &&
        !is_temple() &&
        !is_master() ) {
        _log_error(__FUNCTION__, __LINE__,ctx->initiator() + " have no authority to list kinddeeddetail .");
        return ;
    }

    auto it = get_kinddeeddetail_table().scan({{"kdid",ctx->arg("kdid")}});
    int i = 0;
    string ret;
    while(it->next()) {
        kinddeeddetail ent;
        if (!it->get(&ent)) {
            _log_error(__FUNCTION__, __LINE__, "kinddeeddetail table get failure : " + it->error(true));
            return;
        }
        i++;
        ret += ent.to_string();
    }
    _log_ok("size=" + to_string(i) + " " + ret);
}

void Buddha::list_kinddeedspec() {        
    if( !is_deployer() &&
        !is_founder() &&
        !is_temple() &&
        !is_master() ) {
        _log_error(__FUNCTION__, __LINE__,ctx->initiator() + " have no authority to list kinddeedspec .");
        return ;
    }

    auto it = get_kinddeedspec_table().scan({{"kdid",ctx->arg("kdid")}});
    int i = 0;
    string ret;
    while(it->next()) {
        kinddeedspec ent;
        if (!it->get(&ent)) {
            _log_error(__FUNCTION__, __LINE__, "kinddeedspec table get failure : " + it->error(true));
            return;
        }
        i++;
        ret += ent.to_string();
    }
    _log_ok("size=" + to_string(i) + " " + ret);
}



DEFINE_METHOD(Buddha, add_kinddeeddetail)       { self.add_kinddeeddetail();        }
DEFINE_METHOD(Buddha, add_kinddeedspec)         { self.add_kinddeedspec();          }
DEFINE_METHOD(Buddha, add_kinddeed)             { self.add_kinddeed();              }
DEFINE_METHOD(Buddha, update_kinddeed)          { self.update_kinddeed();           }
DEFINE_METHOD(Buddha, delete_kinddeed)          { self.delete_kinddeed();           }
DEFINE_METHOD(Buddha, find_kinddeed)            { self.find_kinddeed();             }
DEFINE_METHOD(Buddha, list_kinddeed)            { self.list_kinddeed();             }
DEFINE_METHOD(Buddha, list_kinddeeddetail)      { self.list_kinddeeddetail();       }
DEFINE_METHOD(Buddha, list_kinddeedspec)        { self.list_kinddeedspec();         }
