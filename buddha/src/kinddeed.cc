#include <inttypes.h>
#include "xchain/xchain.h"
#include "xchain/account.h"
#include "xchain/contract.pb.h"
#include "xchain/syscall.h"
#include "buddha.pb.h"
#include "buddha.h"

#include <iostream>
using namespace std;

xchain::json kinddeed::to_json() {
    xchain::json j = {
        {"id", id()},
        {"name", name()},
        {"owner", owner()},
        {"type", type()},
        {"lasttime", lasttime()},
        {"online", online()},
    };

    return j;
}

xchain::json kinddeeddetail::to_json() {
    xchain::json j = {
        {"kdid", kdid()},
        {"sequence", sequence()},
        {"hash", hash()},
    };

    return j;
}

xchain::json kinddeedspec::to_json() {
    xchain::json j = {
        {"kdid", kdid()},
        {"sequence", sequence()},
        {"desc", desc()},
        {"price", price()},
    };

    return j;
}


bool Buddha::_is_kinddeed_exist(const string& id,kinddeed& ent) {
    if (!get_kinddeed_table().find({{"id", id}}, &ent))
        return false;

    return true;
}

bool Buddha::_is_kinddeeddetail_exist(const string& kdid,
                                       const string& seq,
                                       kinddeeddetail& ent) {
    if (!get_kinddeeddetail_table().find({{"kdid", kdid},{"sequence",seq}}, &ent))
        return false;

    return true;
}

bool Buddha::_is_kinddeeddetail_exist_by_kdid(const string& kdid,vector<kinddeeddetail>& vent) {
    auto it = get_kinddeeddetail_table().scan({{"kdid",kdid}});
    while(it->next() ) {
        kinddeeddetail ent;
        if (!it->get(&ent) ) {
            if(it->error(true) == "success") 
                return false;
            mycout << "kinddeeddetail table get failure : " << it->error(true) << endl;
            return false;
        }
        vent.push_back(ent);
    }

    if( vent.size()==0)
        return false;

    return true;
}

bool Buddha::_is_kinddeedspec_exist(const string& kdid,
                                       const string& seq,
                                       kinddeedspec& ent) {
    if (!get_kinddeedspec_table().find({{"kdid", kdid},{"sequence",seq}}, &ent))
        return false;

    return true;
}

bool Buddha::_is_kinddeedspec_exist_by_kdid(const string& kdid,vector<kinddeedspec>& vent) {
    auto it = get_kinddeedspec_table().scan({{"kdid",kdid}});
    while(it->next() ) {
        kinddeedspec ent;
        if (!it->get(&ent) ) {
            if(it->error(true) == "success") 
                return false;
            mycout << "kinddeedspec table get failure : " << it->error(true) << endl;
            return false;
        }

        vent.push_back(ent);
    }

    if( vent.size()==0)
        return false;

    return true;
}


bool Buddha::_is_kinddeed_online(const string& id){
    kinddeed ent;
    if (!get_kinddeed_table().find({{"id", id}}, &ent) ) {
        mycout << "kinddeed " << id << " is not exist ." << endl;
        return false;
    }

    if( ent.online() != true ) {
        mycout << "kinddeed " << id << " is not online ." << endl;
        return false;
    }

    return true;

}

bool Buddha::_scan_kinddeed_by_id(xchain::json& ja, const string& cond) {
    auto it = get_kinddeed_table().scan({{"id",cond}});
    while(it->next() ) {
        kinddeed ent;
        if (!it->get(&ent) ) {
            mycout << "kinddeed table get failure : " << it->error(true) << endl;
            return false;
        }

        ja.push_back(ent.to_json());
    }

    return true;
}

bool Buddha::_scan_kinddeed_by_owner(xchain::json& ja, const string& cond) {
    auto it = get_kinddeed_table().scan({{"owner",cond}});
    while(it->next() ) {
        kinddeed ent;
        if (!it->get(&ent) ) {
            mycout << "kinddeed table get failure : " << it->error(true) << endl;
            return false;
        }

        ja.push_back(ent.to_json());
    }

    return true;
}

bool Buddha::_scan_kinddeeddetail(xchain::json& ja, const string& cond) {
    auto it = get_kinddeeddetail_table().scan({{"kdid",cond}});
    while(it->next() ) {
        kinddeeddetail ent;
        if (!it->get(&ent) ) {
            mycout << "kinddeeddetail table get failure : " << it->error(true) << endl;
            return false;
        }

        ja.push_back(ent.to_json());
    }

    return true;
}

bool Buddha::_scan_kinddeedspec(xchain::json& ja, const string& cond) {
    auto it = get_kinddeedspec_table().scan({{"kdid",cond}});
    while(it->next() ) {
        kinddeedspec ent;
        if (!it->get(&ent) ) {
            mycout << "kinddeedspec table get failure : " << it->error(true) << endl;
            return false;
        }

        ja.push_back(ent.to_json());
    }

    return true;
}

bool Buddha::_delete_kinddeed_record(const string& id) {
    kinddeed ent;
    if (!_is_kinddeed_exist(id, ent)){
        mycout << "kinddeed " << id << " is not exist ." << endl ;
        return false;
    }

    if( !get_kinddeed_table().del(ent) ) {
        mycout << "delete kinddeed " << ent.to_json().dump() << " failure ." << endl ;
        return false;
    }

    //删除此善举的所有描述记录
    if( !_delete_kinddeeddetail_records(id) ) {
        mycout << "delete kinddeeddetail " << id << " failure ." << endl ;
        return false;
    }

    //删除此善举的所有规格记录
    if( !_delete_kinddeedspec_records(id) ) {
        mycout << "delete kinddeedspec " << id << " failure ." << endl ;
        return false;
    }

    mycout << "delete kinddeed " << ent.to_json().dump() << " success ." << endl ;
    return true;
}

bool Buddha::_delete_kinddeeddetail_records(const string& id) {

    while(true) {
        kinddeeddetail ent;
        if (!get_kinddeeddetail_table().find({{"kdid", id}}, &ent))
            break;

        if( !get_kinddeeddetail_table().del(ent) ) {
            mycout << "delete kinddeeddetail " << ent.to_json().dump() << " failure ." << endl ;
            return false;
        }
    }

    mycout << "delete kinddeeddetails success ." << endl ;
    return true;
}

bool Buddha::_delete_kinddeeddetail_record(const string& id, const string& sequence ) {
    kinddeeddetail ent;
    if (!get_kinddeeddetail_table().find({{"kdid", id},{"sequence",sequence}}, &ent) ) {
        mycout << "not found kinddeeddetail " << id << "," << sequence << " failure ." << endl ;
        return false;
    }

    if( !get_kinddeeddetail_table().del(ent) ) {
        mycout << "delete kinddeeddetail " << ent.to_json().dump() << " failure ." << endl ;
        return false;
    }

    mycout << "delete kinddeeddetail success ." << endl ;
    return true;
}

bool Buddha::_delete_kinddeedspec_records(const string& id) {
    while(true) {
        kinddeedspec ent;
        if (!get_kinddeedspec_table().find({{"kdid", id}}, &ent))
            break;

        if( !get_kinddeedspec_table().del(ent) ) {
            mycout << "delete kinddeedspec " << ent.to_json().dump() << " failure ." << endl ;
            return false;
        }
    }

    mycout << "delete kinddeedspecs success ." << endl ;
    return true;
}

bool Buddha::_delete_kinddeedspec_record(const string& id, const string& sequence ) {
    kinddeedspec ent;
    if (!get_kinddeedspec_table().find({{"kdid", id},{"sequence",sequence}}, &ent) ) {
        mycout << "not found kinddeedspec " << id << "," << sequence << " failure ." << endl ;
        return false;
    }

    if( !get_kinddeedspec_table().del(ent) ) {
        mycout << "delete kinddeedspec " << ent.to_json().dump() << " failure ." << endl ;
        return false;
    }

    mycout << "delete kinddeedspec success ." << endl ;
    return true;
}

bool Buddha::_add_kinddeeddetail(const string& kdid,
                                 const string& sequence,
                                 const string& hash) {

    if( kdid.empty() ) {
        mycout << "kdid is empty ." << endl;
        return false;
    }

    if( sequence.empty() ) {
        mycout << "sequence is empty ." << endl;
        return false;
    }

    if( hash.empty() ) {
        mycout << "hash is empty ." << endl;
        return false;
    }

    //删除在此善举已经存在的描述
    kinddeeddetail ent;
    if(_is_kinddeeddetail_exist(kdid, sequence, ent)) 
        if(!_delete_kinddeeddetail_record(kdid, sequence)) 
            return false;

    ent.set_kdid(kdid);
    ent.set_sequence(stoll(sequence));
    ent.set_hash(hash);

    mycout << ent.to_json().dump() << endl;

    if (!get_kinddeeddetail_table().put(ent) ) {
        mycout << "kinddeeddetail table put " << ent.to_json().dump() << " failure ." << endl;
        return false;
    }

    return true ;
}

bool Buddha::_add_kinddeedspec(const string& kdid,
                               const string& sequence,
                               const string& desc,
                               const string& price) {

    if( kdid.empty() ) {
        mycout << "kdid is empty ." << endl;
        return false;
    }

    if( sequence.empty() ) {
        mycout << "sequence is empty ." << endl;
        return false;
    }

    if( desc.empty() ) {
        mycout << "desc is empty ." << endl;
        return false;
    }

    if( price.empty() ) {
        mycout << "price is empty ." << endl;
        return false;
    }

    //删除在此善举已经存在的规格
    kinddeedspec ent;
    if(_is_kinddeedspec_exist(kdid, sequence, ent))
        if(!_delete_kinddeedspec_record(kdid, sequence)) 
            return false;

    ent.set_kdid(kdid);
    ent.set_sequence(stoll(sequence));
    ent.set_desc(desc);
    ent.set_price(stoll(price));

    mycout << ent.to_json().dump() << endl;

    if (!get_kinddeedspec_table().put(ent) ) {
        mycout << "kinddeedspec table put " << ent.to_json().dump() << " failure ." << endl;
        return false;
    }

    return true ;
}


namespace 分界线{}

void Buddha::add_kinddeeddetail() {
    const string& id = ctx->arg("id");
    const string& sequence = ctx->arg("sequence");
    const string& hash = ctx->arg("hash");

    if( id.empty() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "kinddeed id is empty .");
        return ;
    }

    if( sequence.empty() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "kinddeed sequence is empty .");
        return ;
    }

    if( hash.empty() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "kinddeed hash is empty .");
        return ;
    }

    if (!_add_kinddeeddetail(id,sequence,hash) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "_add_kinddeeddetail " + id + " failure .");
        return;
    }

    _log_ok(__FILE__, __FUNCTION__, __LINE__, "ok");
}

void Buddha::add_kinddeedspec() {
    const string& id = ctx->arg("id");    
    const string& sequence = ctx->arg("sequence");
    const string& desc = ctx->arg("desc");
    const string& price = ctx->arg("price");

    if( id.empty() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "kinddeed id is empty .");
        return ;
    }

    if( sequence.empty() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "kinddeed sequence is empty .");
        return ;
    }

    if( desc.empty() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "kinddeed desc is empty .");
        return ;
    }
    
    if( price.empty() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "kinddeed price is empty .");
        return ;
    }
    
    if (!_add_kinddeedspec(id,sequence,desc,price) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "_add_kinddeedspec " + id + " failure .");
        return;
    }

    _log_ok(__FILE__, __FUNCTION__, __LINE__, "ok");
}

void Buddha::add_kinddeed() {
    const string& id = ctx->arg("id");
    const string& name = ctx->arg("name");
    const string& owner = ctx->initiator();
    const string& type = ctx->arg("type");
    const string& lasttime = ctx->arg("lasttime");
    const string& detail = ctx->arg("detail");
    const string& spec = ctx->arg("spec");

    if( id.empty() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "kinddeed id is empty .");
        return ;
    }

    if( name.empty() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "kinddeed name is empty .");
        return ;
    }

    if( type.empty() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "kinddeed type is empty .");
        return ;
    }

    if( lasttime.empty() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "kinddeed lasttime is empty .");
        return ;
    }

    //判断善举描述是否是数组
    auto detail_array = xchain::json::parse(detail);
    if (!detail_array.is_array() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "field 'detail' need to be array .");
        return;
    }
    
    if ( detail_array.empty() || detail_array.size() == 0) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "filed 'detail' empty .");
        return;
    }

    //判断善举规格是否是数组
    auto spec_array = xchain::json::parse(spec);
    if (!spec_array.is_array() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "field 'spec' need to be array .");
        return;
    }
    
    if ( spec_array.empty() || spec_array.size() == 0) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "filed 'spec' empty .");
        return;
    }

    //身份检查，判断是否是基金会成员，寺院，法师
    if( !is_founder() &&
        !is_temple() &&
        !is_master() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__,ctx->initiator() + " is not founder,temple and master, have no authority to add kinddeed .");
        return ;
    }

    //判断善举是否存在
    kinddeed ent;
    if (_is_kinddeed_exist(id, ent))  {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "kinddeed " + id + " is exist .", ent.to_json());
        return ;
    }

    //判断善举类型是否存在
    kinddeedtype type_ent;
    if (!_is_kinddeedtype_exist(type, type_ent))  {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "kinddeedtype " + type + " is not exist .");
        return ;
    }

    //判断善举描述是否存在
    vector<kinddeeddetail> v_kinddeeddetail_ent;
    if (_is_kinddeeddetail_exist_by_kdid(id, v_kinddeeddetail_ent))  {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "kinddeeddetail is exist ." );
        return ;
    }

    //判断善举规格是否存在
    vector<kinddeedspec> v_kinddeedspec_ent;
    if (_is_kinddeedspec_exist_by_kdid(id, v_kinddeedspec_ent))  {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "kinddeeddetail is exist ." );
        return ;
    }

    //添加善举描述列表
    for(int i = 0 ; i < detail_array.size() ; i++) {
        string sequence = detail_array.at(i)["sequence"].template get<string>();
        string hash = detail_array.at(i)["hash"].template get<string>();

        //添加善举描述记录        
        if (!_add_kinddeeddetail(id,sequence,hash) ) {
            _log_error(__FILE__, __FUNCTION__, __LINE__, "_add_kinddeeddetail " + id + " failure .");
            return;
        }
    }

    //添加善举规格列表
    for(int i = 0 ; i < spec_array.size() ; i++) {
        string sequence = spec_array.at(i)["sequence"].template get<string>();
        string desc = spec_array.at(i)["desc"].template get<string>();
        string price = spec_array.at(i)["price"].template get<string>();

        //添加善举规格记录        
        if (!_add_kinddeedspec(id,sequence,desc,price) ) {
            _log_error(__FILE__, __FUNCTION__, __LINE__, "_add_kinddeedspec " + id + " failure .");
            return;
        }
    }

    ent.set_id(id);
    ent.set_name(name);
    ent.set_owner(ctx->initiator());
    ent.set_type(stoll(type));
    ent.set_lasttime(lasttime);
    ent.set_online(true);

    if (!get_kinddeed_table().put(ent) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "table put failure .", ent.to_json());
        return;
    }


    _log_ok(__FILE__, __FUNCTION__, __LINE__, "create", ent.to_json());
}

void Buddha::delete_kinddeed() {

    const string& id = ctx->arg("id");
    if( id.empty() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "kinddeed id is empty .");
        return ;
    }

    //判断善举是否存在
    kinddeed ent;
    if (!_is_kinddeed_exist(id, ent))  {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "kinddeed " + id + " is not exist .");
        return ;
    }

    //身份检查，判断是否是基金会成员，寺院，法师
    if( !is_founder() &&
        !is_temple() &&
        !is_master() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__,ctx->initiator() + " is not founder and master, have no authority to delete kinddeed .");
        return ;
    }

    //判断是否是善举所有者
    if( ent.owner() != ctx->initiator() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "kinddeed " + id + " is not belong to you .", ent.to_json() );
        return ;
    }

    //删除此善举
    if( !_delete_kinddeed_record(id) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "delete failure .", ent.to_json());
        return;
    }

    _log_ok(__FILE__, __FUNCTION__, __LINE__, "delete", ent.to_json());
}

void Buddha::update_kinddeed() {
    const string& id = ctx->arg("id");
    const string& name = ctx->arg("name");
    const string& owner = ctx->initiator();
    const string& type = ctx->arg("type");
    const string& lasttime = ctx->arg("lasttime");
    const string& detail = ctx->arg("detail");
    const string& spec = ctx->arg("spec");

    if( id.empty() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "kinddeed id is empty .");
        return ;
    }

    if( name.empty() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "kinddeed name is empty .");
        return ;
    }

    if( type.empty() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "kinddeed type is empty .");
        return ;
    }

    if( lasttime.empty() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "kinddeed lasttime is empty .");
        return ;
    }

    //判断善举描述是否是数组
    auto detail_array = xchain::json::parse(detail);
    if (!detail_array.is_array() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "field 'detail' need to be array .");
        return;
    }
    
    if ( detail_array.empty() || detail_array.size() == 0) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "filed 'detail' empty .");
        return;
    }

    //判断善举规格是否是数组
    auto spec_array = xchain::json::parse(spec);
    if (!spec_array.is_array() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "field 'spec' need to be array .");
        return;
    }
    
    if ( spec_array.empty() || spec_array.size() == 0) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "filed 'spec' empty .");
        return;
    }

    //身份检查，判断是否是基金会成员，寺院，法师
    if( !is_founder() &&
        !is_temple() &&
        !is_master() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__,ctx->initiator() + " is not founder and master, have no authority to update kinddeed .");
        return ;
    }

    //判断善举是否存在
    kinddeed ent;
    if (_is_kinddeed_exist(id, ent))  {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "kinddeed " + id + " is exist .", ent.to_json());
        return ;
    }

    //判断善举类型是否存在
    kinddeedtype type_ent;
    if (!_is_kinddeedtype_exist(type, type_ent))  {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "kinddeedtype " + type + " is not exist .");
        return ;
    }

    //删除此善举的所有描述记录
    vector<kinddeeddetail> v_kinddeeddetail_ent;
    if (_is_kinddeeddetail_exist_by_kdid(id, v_kinddeeddetail_ent))  {
        if( !_delete_kinddeeddetail_records(id) ) {
            _log_error(__FILE__, __FUNCTION__, __LINE__, "delete failure .", ent.to_json());
            return;
        }
    }

    vector<kinddeedspec> v_kinddeedspec_ent;
    if (_is_kinddeedspec_exist_by_kdid(id, v_kinddeedspec_ent))  {
        //删除此善举的所有规格记录
        if( !_delete_kinddeedspec_records(id) ) {
            _log_error(__FILE__, __FUNCTION__, __LINE__, "delete failure .", ent.to_json());
            return;
        }
    }

    //添加善举描述列表
    for(int i = 0 ; i < detail_array.size() ; i++) {
        int64_t sequence = stoll(detail_array.at(i)["sequence"].template get<string>());
        string hash = detail_array.at(i)["hash"].template get<string>();

        kinddeeddetail ent;
        ent.set_kdid(id);
        ent.set_sequence(sequence);
        ent.set_hash(hash);

        if (!get_kinddeeddetail_table().put(ent) ) {
            _log_error(__FILE__, __FUNCTION__, __LINE__, "table put failure .", ent.to_json());
            return;
        }
    }
    
    //添加善举规格列表
    for(int i = 0 ; i < spec_array.size() ; i++) {
        int64_t sequence = stoll(spec_array.at(i)["sequence"].template get<string>());
        string desc = spec_array.at(i)["desc"].template get<string>();
        int64_t price = stoll(spec_array.at(i)["price"].template get<string>());

        kinddeedspec ent;
        ent.set_kdid(id);
        ent.set_sequence(sequence);
        ent.set_desc(desc);
        ent.set_price(price);

        if (!get_kinddeedspec_table().put(ent) ) {
            _log_error(__FILE__, __FUNCTION__, __LINE__, "table put failure .", ent.to_json());
            return;
        }
    }

    //添加善举
    ent.set_id(id);
    ent.set_name(name);
    ent.set_owner(ctx->initiator());
    ent.set_type(stoll(type));
    ent.set_lasttime(lasttime);
    ent.set_online(true);

    if (!get_kinddeed_table().put(ent) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "table put failure .", ent.to_json());
        return;
    }

    _log_ok(__FILE__, __FUNCTION__, __LINE__, "update", ent.to_json());
}

void Buddha::offline_kinddeed() {
    const string& id = ctx->arg("id");
    if( id.empty() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "kinddeed id is empty .");
        return ;
    }

    //判断是否是基金会成员
    if( !is_founder() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__,ctx->initiator() + " is not founder, have no authority to approve offline kinddeed .");
        return ;
    }

    //判断善举是否存在
    kinddeed ent;
    if (!_is_kinddeed_exist(id, ent))  {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "kinddeed " + id + " is not exist .");
        return ;
    }

    if (ent.online()==false){
        _log_error(__FILE__, __FUNCTION__, __LINE__, "kinddeed " + id + " is already offline .", ent.to_json() );
        return ;
    }

    //删除此善举
    if( !_delete_kinddeed_record(id) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "delete failure .", ent.to_json());
        return;
    }

    ent.set_online(false);
    if (!get_kinddeed_table().put(ent) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "table put failure .", ent.to_json());
        return;
    }

    _log_ok(__FILE__, __FUNCTION__, __LINE__, "offline kinddeed " + id + " success .", ent.to_json() );
}

void Buddha::is_kinddeed_online() {
    const string& id = ctx->arg("id");
    if( id.empty() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "kinddeed id is empty .");
        return ;
    }

    kinddeed ent;
    if (!get_kinddeed_table().find({{"id", id}}, &ent) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "kinddeed " + id  + " is not exist .");
        return;
    }

    if( ent.online() != true ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "kinddeed " + id  + " is offline .");
        return;
    }

    _log_ok(__FILE__, __FUNCTION__, __LINE__, "kinddeed " + id  + " is online .");
}    

void Buddha::find_kinddeed() {

    const string& id = ctx->arg("id");
    if( id.empty() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "kinddeed id is empty .");
        return ;
    }

    //判断善举是否存在
    kinddeed kinddeed_ent;
    if (!_is_kinddeed_exist(id, kinddeed_ent))  {
        _log_ok(__FILE__, __FUNCTION__, __LINE__, "kinddeed " + id + " is not exist .");
        return ;
    }

    //获取善举描述
    vector<kinddeeddetail> v_kinddeeddetail_ent;
    _is_kinddeeddetail_exist_by_kdid(id, v_kinddeeddetail_ent);
    xchain::json detail_json ;
    for(int i = 0 ; i < v_kinddeeddetail_ent.size() ; i++ ) {
        detail_json += v_kinddeeddetail_ent[i].to_json();
    }

    //获取善举规格
    vector<kinddeedspec> v_kinddeedspec_ent;
    _is_kinddeedspec_exist_by_kdid(id, v_kinddeedspec_ent);
    xchain::json spec_json ;
    for(int i = 0 ; i < v_kinddeedspec_ent.size() ; i++ ) {
        spec_json.push_back(v_kinddeedspec_ent[i].to_json());
    }

    xchain::json j = kinddeed_ent.to_json();
    j += {"detail", detail_json};
    j += {"spec", spec_json};

    _log_ok(__FILE__, __FUNCTION__, __LINE__, j);
}

void Buddha::list_kinddeed() {        
    //身份检查，部署者和基金会成员可以查看所有善举凭证
    //善举过多时，此时不安全，尽可能少调用
    if( is_deployer() ||
        is_founder() ) {
        xchain::json ja ;
        if(!_scan_kinddeed_by_id(ja,ctx->arg("id")) ) {
            _log_error(__FILE__, __FUNCTION__, __LINE__, "scan table failure .");
            return;
        }

        _log_ok(__FILE__, __FUNCTION__, __LINE__, "scan", ja);
        return ;
    }

    //身份检查，寺院和法师可以查看自己的所有善举凭证
    //善举过多时，此时不安全，不过一般不会太多。
    if( is_temple() ||
        is_master() ) {
        xchain::json ja ;
        if(!_scan_kinddeed_by_owner(ja,ctx->initiator()) ) {
            _log_error(__FILE__, __FUNCTION__, __LINE__, "scan table failure .");
            return;
        }
        
        _log_ok(__FILE__, __FUNCTION__, __LINE__, "scan", ja);
        return ;
    }

    _log_error(__FILE__, __FUNCTION__, __LINE__,ctx->initiator() + " have no authority to list kinddeed .");
}

void Buddha::list_kinddeeddetail() {
    //身份检查，部署者，基金会成员，寺院，法师具有权限
    if( !is_deployer() &&
        !is_founder() &&
        !is_temple() &&
        !is_master() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__,ctx->initiator() + " have no authority to list kinddeeddetail .");
        return ;
    }

    xchain::json ja ;
    if(!_scan_kinddeeddetail(ja, ctx->arg("kdid")) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "scan table failure .");
        return;
    }
    
    _log_ok(__FILE__, __FUNCTION__, __LINE__, "scan", ja);
}

void Buddha::list_kinddeedspec() {
    //身份检查，部署者，基金会成员，寺院，法师具有权限
    if( !is_deployer() &&
        !is_founder() &&
        !is_temple() &&
        !is_master() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__,ctx->initiator() + " have no authority to list kinddeedspec .");
        return ;
    }

    xchain::json ja ;
    if(!_scan_kinddeedspec(ja,ctx->arg("kdid")) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "scan table failure .");
        return;
    }

    _log_ok(__FILE__, __FUNCTION__, __LINE__, "scan", ja);
}



DEFINE_METHOD(Buddha, add_kinddeeddetail)       { self.add_kinddeeddetail();        }
DEFINE_METHOD(Buddha, add_kinddeedspec)         { self.add_kinddeedspec();          }
DEFINE_METHOD(Buddha, add_kinddeed)             { self.add_kinddeed();              }
DEFINE_METHOD(Buddha, update_kinddeed)          { self.update_kinddeed();           }
DEFINE_METHOD(Buddha, delete_kinddeed)          { self.delete_kinddeed();           }
DEFINE_METHOD(Buddha, offline_kinddeed)         { self.offline_kinddeed();          }
DEFINE_METHOD(Buddha, is_kinddeed_online)       { self.is_kinddeed_online();        }
DEFINE_METHOD(Buddha, find_kinddeed)            { self.find_kinddeed();             }
DEFINE_METHOD(Buddha, list_kinddeed)            { self.list_kinddeed();             }
DEFINE_METHOD(Buddha, list_kinddeeddetail)      { self.list_kinddeeddetail();       }
DEFINE_METHOD(Buddha, list_kinddeedspec)        { self.list_kinddeedspec();         }
