#include <inttypes.h>
#include "xchain/xchain.h"
#include "xchain/account.h"
#include "xchain/contract.pb.h"
#include "xchain/syscall.h"
#include "buddha.pb.h"
#include "buddha.h"

#include <iostream>
using namespace std;

xchain::json BKinddeed::to_json() {
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

xchain::json BKinddeedDetail::to_json() {
    xchain::json j = {
        {"kdid", kdid()},
        {"sequence", sequence()},
        {"hash", hash()},
    };

    return j;
}

xchain::json BKinddeedSpec::to_json() {
    xchain::json j = {
        {"kdid", kdid()},
        {"sequence", sequence()},
        {"desc", desc()},
        {"price", price()},
    };

    return j;
}


bool Main::_is_kinddeed_exist(kinddeed& ent, const string& id) {
    if (!get_kinddeed_table().find({{"id", id}}, &ent))
        return false;

    return true;
}

bool Main::_is_kinddeeddetail_exist(kinddeeddetail& ent,
                                      const string& kdid,
                                      const string& seq) {
    if (!get_kinddeeddetail_table().find({{"kdid", kdid},{"sequence",seq}}, &ent))
        return false;

    return true;
}

bool Main::_is_kinddeedspec_exist(kinddeedspec& ent,
                                    const string& kdid,
                                    const string& seq) {
    if (!get_kinddeedspec_table().find({{"kdid", kdid},{"sequence",seq}}, &ent))
        return false;

    return true;
}

bool Main::_is_kinddeed_online(const string& id){
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

bool Main::_scan_kinddeed_by_id(xchain::json& ja, const string& cond) {
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

bool Main::_scan_kinddeed_by_owner(xchain::json& ja, const string& cond) {
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

bool Main::_scan_kinddeeddetail(vector<kinddeeddetail>& v, const string& cond) {
    auto it = get_kinddeeddetail_table().scan({{"kdid",cond}});
    while(it->next() ) {
        kinddeeddetail ent;
        if (!it->get(&ent) ) {
            mycout << "kinddeeddetail " << ent.to_json().dump()  << endl ;
            if(it->error(true) == "success") 
                return false;
            mycout << "kinddeeddetail table get failure : " << it->error() << endl;
            return false;
        }
    
        mycout << "found kinddeeddetail " << ent.to_json().dump()  << endl ;

        v.push_back(ent);
    }

    if( v.size()==0)
        return false;

    return true;
}

bool Main::_scan_kinddeeddetail(xchain::json& ja, const string& cond) {
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

bool Main::_scan_kinddeedspec(vector<kinddeedspec>& v, const string& cond) {
    auto it = get_kinddeedspec_table().scan({{"kdid",cond}});
    while(it->next() ) {
        kinddeedspec ent;
        if (!it->get(&ent) ) {
            if(it->error(true) == "success") 
                break;
            mycout << "kinddeedspec table get failure : " << it->error(true) << endl;
            return false;
        }

        v.push_back(ent);
    }

    if( v.size()==0)
        return false;

    return true;
}


bool Main::_scan_kinddeedspec(xchain::json& ja, const string& cond) {
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

bool Main::_delete_kinddeed_record(const string& id) {
    kinddeed ent;
    if (!_is_kinddeed_exist(ent, id)){
        mycout << "kinddeed " << id << " is not exist ." << endl ;
        return false;
    }

    if( !get_kinddeed_table().del(ent) ) {
        mycout << "delete kinddeed " << ent.to_json().dump() << " failure ." << endl ;
        return false;
    }

    //删除此善举的所有描述记录
    if( !_delete_kinddeeddetail_record(id) ) {
        mycout << "delete kinddeeddetail " << id << " failure ." << endl ;
        return false;
    }

    //删除此善举的所有规格记录
    if( !_delete_kinddeedspec_record(id) ) {
        mycout << "delete kinddeedspec " << id << " failure ." << endl ;
        return false;
    }

    mycout << "delete kinddeed " << ent.to_json().dump() << " success ." << endl ;
    return true;
}

bool Main::_delete_kinddeeddetail_record(const string& id, const string& sequence ) {
    if( sequence.empty() ) {

        auto it = get_kinddeeddetail_table().scan({{"kdid",id}});
        while(it->next() ) {
            kinddeeddetail ent;
            if (!it->get(&ent) ) {
                mycout << "kinddeeddetail table get failure : " << it->error(true) << endl;
                return false;
            }

            if( !get_kinddeeddetail_table().del(ent) ) {
                mycout << "delete kinddeeddetail " << ent.to_json().dump() << " failure ." << endl ;
                return false;
            }

            mycout << "delete kinddeeddetail " << ent.to_json().dump() << " success ." << endl ;
        }

        mycout << "delete kinddeeddetails success ." << endl ;
        return true;
    }

    kinddeeddetail ent;
    if (!get_kinddeeddetail_table().find({{"kdid", id},{"sequence",sequence}}, &ent) ) {
        mycout << "not found kinddeeddetail " << id << "," << sequence << " failure ." << endl ;
        return false;
    }

    if( !get_kinddeeddetail_table().del(ent) ) {
        mycout << "delete kinddeeddetail " << ent.to_json().dump() << " failure ." << endl ;
        return false;
    }

    mycout << "delete kinddeeddetail " << ent.to_json() << " success ." << endl ;
    return true;
}

bool Main::_delete_kinddeedspec_record(const string& id, const string& sequence ) {
    if( sequence.empty() ) {
        auto it = get_kinddeedspec_table().scan({{"kdid",id}});
        while(it->next() ) {
            kinddeedspec ent;
            if (!it->get(&ent) ) {
                mycout << "kinddeedspec table get failure : " << it->error(true) << endl;
                return false;
            }

            if( !get_kinddeedspec_table().del(ent) ) {
                mycout << "delete kinddeedspec " << ent.to_json().dump() << " failure ." << endl ;
                return false;
            }

            mycout << "delete kinddeedspec " << ent.to_json().dump() << " success ." << endl ;
        }

        mycout << "delete kinddeedspecs success ." << endl ;
        return true;
    }

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

bool Main::_add_kinddeeddetail(const string& kdid,
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

    // //删除在此善举已经存在的描述
    // _delete_kinddeeddetail_record(kdid, sequence);

    kinddeeddetail ent;
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

bool Main::_add_kinddeedspec(const string& kdid,
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
    if(_is_kinddeedspec_exist(ent, kdid, sequence))
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

void Main::add_kinddeeddetail() {
    const string& kinddeed = ctx->arg("kinddeed");
    const string& sequence = ctx->arg("sequence");
    const string& hash = ctx->arg("hash");

    if( kinddeed.empty() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "kinddeed is empty .");
        return ;
    }

    if( sequence.empty() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "sequence is empty .");
        return ;
    }

    if( hash.empty() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "hash is empty .");
        return ;
    }

    if (!_add_kinddeeddetail(kinddeed,sequence,hash) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "_add_kinddeeddetail " + kinddeed + " failure .");
        return;
    }

    _log_ok(__FILE__, __FUNCTION__, __LINE__, "create");
}

void Main::delete_kinddeeddetail() {
    const string& kinddeed = ctx->arg("kinddeed");
    if( kinddeed.empty() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "kinddeed is empty .");
        return ;
    }

    //身份检查，部署者，基金会成员，寺院，法师具有权限
    if( !is_deployer() &&
        !is_founder() &&
        !is_temple() &&
        !is_master() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__,ctx->initiator() + " have no authority to delete kinddeeddetail .");
        return ;
    }

    //判断善举描述是否存在
    xchain::json ja ;
    if (!_scan_kinddeeddetail(ja, kinddeed))  {
        _log_ok(__FILE__, __FUNCTION__, __LINE__, "kinddeed " + kinddeed + " kinddeeddetail is not exist ." );
        return ;
    }

    //删除此善举的所有描述记录
    if( !_delete_kinddeeddetail_record(kinddeed) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "delete kinddeeddetail " + kinddeed + " failure ." );
        return;
    }

    _log_ok(__FILE__, __FUNCTION__, __LINE__, "delete", ja);
}

void Main::list_kinddeeddetail() {
    //身份检查，部署者，基金会成员，寺院，法师具有权限
    if( !is_deployer() &&
        !is_founder() &&
        !is_temple() &&
        !is_master() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__,ctx->initiator() + " have no authority to list kinddeeddetail .");
        return ;
    }

    xchain::json ja ;
    if(!_scan_kinddeeddetail(ja, ctx->arg("kinddeed")) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "scan table failure .");
        return;
    }

    _log_ok(__FILE__, __FUNCTION__, __LINE__, "scan", ja);
}

void Main::add_kinddeedspec() {
    const string& kinddeed = ctx->arg("kinddeed");    
    const string& sequence = ctx->arg("sequence");
    const string& desc = ctx->arg("desc");
    const string& price = ctx->arg("price");

    if( kinddeed.empty() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "kinddeed is empty .");
        return ;
    }

    if( sequence.empty() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "sequence is empty .");
        return ;
    }

    if( desc.empty() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "desc is empty .");
        return ;
    }
    
    if( price.empty() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "kinddeed price is empty .");
        return ;
    }
    
    if (!_add_kinddeedspec(kinddeed,sequence,desc,price) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "_add_kinddeedspec " + kinddeed + " failure .");
        return;
    }

    _log_ok(__FILE__, __FUNCTION__, __LINE__, "create");
}

void Main::delete_kinddeedspec() {
    const string& kinddeed = ctx->arg("kinddeed");
    if( kinddeed.empty() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "kinddeed is empty .");
        return ;
    }

    //身份检查，部署者，基金会成员，寺院，法师具有权限
    if( !is_deployer() &&
        !is_founder() &&
        !is_temple() &&
        !is_master() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__,ctx->initiator() + " have no authority to list kinddeedspec .");
        return ;
    }

    //判断善举描述是否存在
    xchain::json ja ;
    if (!_scan_kinddeedspec(ja, kinddeed))  {
        _log_ok(__FILE__, __FUNCTION__, __LINE__, "kinddeed " + kinddeed + " kinddeedspec is not exist ." );
        return ;
    }

    //删除此善举的所有描述记录
    if( !_delete_kinddeedspec_record(kinddeed) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "delete kinddeedspec " + kinddeed + " failure ." );
        return;
    }

    _log_ok(__FILE__, __FUNCTION__, __LINE__, "delete", ja);
}

void Main::list_kinddeedspec() {
    //身份检查，部署者，基金会成员，寺院，法师具有权限
    if( !is_deployer() &&
        !is_founder() &&
        !is_temple() &&
        !is_master() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__,ctx->initiator() + " have no authority to list kinddeedspec .");
        return ;
    }

    xchain::json ja ;
    if(!_scan_kinddeedspec(ja,ctx->arg("kinddeed")) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "scan table failure .");
        return;
    }

    _log_ok(__FILE__, __FUNCTION__, __LINE__, "scan", ja);
}

void Main::add_kinddeed() {
    const string& id = ctx->arg("id");
    const string& name = ctx->arg("name");
    const string& owner = ctx->initiator();
    const string& type = ctx->arg("type");
    const string& lasttime = ctx->arg("lasttime");
    const string& detail = ctx->arg("detail");
    const string& spec = ctx->arg("spec");

    if( id.empty() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "id is empty .");
        return ;
    }

    if( name.empty() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "name is empty .");
        return ;
    }

    if( type.empty() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "type is empty .");
        return ;
    }

    if( lasttime.empty() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "lasttime is empty .");
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

    // //判断善举是否存在
    kinddeed ent;
    if (_is_kinddeed_exist(ent, id))  {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "kinddeed " + id + " is exist .", ent.to_json());
        return ;
    }

    // //判断善举类型是否存在
    kinddeedtype type_ent;
    if (!_is_kinddeedtype_exist(type_ent, type))  {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "kinddeedtype " + type + " is not exist .");
        return ;
    }

    //删除此善举的所有描述记录
    if( !_delete_kinddeeddetail_record(id) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "delete kinddeeddetail " + id + " failure ." );
        return;
    }

    //删除此善举的所有规格记录
    if( !_delete_kinddeedspec_record(id) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "delete kinddeedspec " + id + " failure ." );
        return;
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


    _log_ok(__FILE__, __FUNCTION__, __LINE__, "111111111111111111111111" );
    return ;

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


    // ent.set_id(id);
    // ent.set_name(name);
    // ent.set_owner(ctx->initiator());
    // ent.set_type(stoll(type));
    // ent.set_lasttime(lasttime);
    // ent.set_online(true);

    // if (!get_kinddeed_table().put(ent) ) {
    //     _log_error(__FILE__, __FUNCTION__, __LINE__, "table put failure .", ent.to_json());
    //     return;
    // }


    // _log_ok(__FILE__, __FUNCTION__, __LINE__, "create", ent.to_json());
}

void Main::delete_kinddeed() {

    const string& id = ctx->arg("id");
    if( id.empty() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "kinddeed id is empty .");
        return ;
    }

    //判断善举是否存在
    kinddeed ent;
    if (!_is_kinddeed_exist(ent, id))  {
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

void Main::update_kinddeed() {
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
    if (!_is_kinddeed_exist(ent, id))  {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "kinddeed " + id + " is not exist .", ent.to_json());
        return ;
    }

    //判断善举类型是否存在
    kinddeedtype type_ent;
    if (!_is_kinddeedtype_exist(type_ent, type))  {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "kinddeedtype " + type + " is not exist .");
        return ;
    }

    // //删除此善举的所有描述记录
    // vector<kinddeeddetail> v_kinddeeddetail_ent;
    // if (_scan_kinddeeddetail(v_kinddeeddetail_ent, id))  {
    //     if( !_delete_kinddeeddetail_record(id) ) {
    //         _log_error(__FILE__, __FUNCTION__, __LINE__, "delete failure .", ent.to_json());
    //         return;
    //     }
    // }

    // vector<kinddeedspec> v_kinddeedspec_ent;
    // if (_scan_kinddeedspec(v_kinddeedspec_ent, id))  {
    //     //删除此善举的所有规格记录
    //     if( !_delete_kinddeedspec_record(id) ) {
    //         _log_error(__FILE__, __FUNCTION__, __LINE__, "delete failure .", ent.to_json());
    //         return;
    //     }
    // }

    _delete_kinddeeddetail_record(id);
    _delete_kinddeedspec_record(id);

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

void Main::offline_kinddeed() {
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
    if (!_is_kinddeed_exist(ent, id))  {
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

void Main::is_kinddeed_online() {
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

void Main::find_kinddeed() {

    const string& id = ctx->arg("id");
    if( id.empty() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "kinddeed id is empty .");
        return ;
    }

    //判断善举是否存在
    kinddeed kinddeed_ent;
    if (!_is_kinddeed_exist(kinddeed_ent, id))  {
        _log_ok(__FILE__, __FUNCTION__, __LINE__, "kinddeed " + id + " is not exist .");
        return ;
    }


    //获取善举描述
    xchain::json detail_json ;
    if (!_scan_kinddeeddetail(detail_json, id))  {
        _log_ok(__FILE__, __FUNCTION__, __LINE__, "kinddeed " + id + " kinddeeddetail is not exist ." );
        return ;
    }


    //获取善举规格
    xchain::json spec_json ;
    if (!_scan_kinddeedspec(spec_json, id))  {
        _log_ok(__FILE__, __FUNCTION__, __LINE__, "kinddeed " + id + " kinddeedspec is not exist ." );
        return ;
    }


    xchain::json j = kinddeed_ent.to_json();
    j += {"detail", detail_json};
    j += {"spec", spec_json};

    _log_ok(__FILE__, __FUNCTION__, __LINE__, "find", j);
}

void Main::list_kinddeed() {        
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




DEFINE_METHOD(Main, add_kinddeeddetail)       { self.add_kinddeeddetail();        }
DEFINE_METHOD(Main, delete_kinddeeddetail)    { self.delete_kinddeeddetail();     }
DEFINE_METHOD(Main, list_kinddeeddetail)      { self.list_kinddeeddetail();       }

DEFINE_METHOD(Main, add_kinddeedspec)         { self.add_kinddeedspec();          }
DEFINE_METHOD(Main, delete_kinddeedspec)      { self.delete_kinddeedspec();       }
DEFINE_METHOD(Main, list_kinddeedspec)        { self.list_kinddeedspec();         }

DEFINE_METHOD(Main, add_kinddeed)             { self.add_kinddeed();              }
DEFINE_METHOD(Main, update_kinddeed)          { self.update_kinddeed();           }
DEFINE_METHOD(Main, delete_kinddeed)          { self.delete_kinddeed();           }
DEFINE_METHOD(Main, offline_kinddeed)         { self.offline_kinddeed();          }
DEFINE_METHOD(Main, is_kinddeed_online)       { self.is_kinddeed_online();        }
DEFINE_METHOD(Main, find_kinddeed)            { self.find_kinddeed();             }
DEFINE_METHOD(Main, list_kinddeed)            { self.list_kinddeed();             }
