#include <inttypes.h>
#include "xchain/xchain.h"
#include "xchain/account.h"
#include "xchain/contract.pb.h"
#include "xchain/syscall.h"
#include "buddha.pb.h"
#include "buddha.h"

#include <iostream>
using namespace std;

string kinddeedtype::to_string() {
    string str ;
    str += "{" ;
    str += std::to_string(id()) + ",";
    str += desc();
    str += "}";
    return str;
}


xchain::json kinddeedtype::to_json() {
    xchain::json j = {
        {"id", id()},
        {"desc", desc()},
    };

    return j;
}


bool Buddha::_is_kinddeedtype_exist(const string& id,kinddeedtype& ent) {
    if (!get_kinddeedtype_table().find({{"id", id}}, &ent))
        return false;

    return true;
}

bool Buddha::_scan_kinddeedtype(xchain::json& v, const string& cond) {
    auto it = get_kinddeedtype_table().scan({{"id",cond}});
    while(it->next()) {
        kinddeedtype ent;
        if (!it->get(&ent)) {
            mycout << "kinddeedtype table get failure : " << it->error(true) << endl;
            return false;
        }

        v.push_back(ent.to_json());
    }

    return true;
}

bool Buddha::_delete_kinddeedtype_record(const string& id) {
    kinddeedtype ent;
    if (!_is_kinddeedtype_exist(id, ent)){
        mycout << "kinddeedtype " << id << " is not exist ." << endl ;
        return false;
    }

    if( !get_kinddeedtype_table().del(ent) ) {
        mycout << "delete kinddeedtype " << ent.to_string() << " failure ." << endl ;
        return false;
    }

    mycout << "delete kinddeedtype " << ent.to_string() << " success ." << endl ;
    return true;
}

namespace 分界线{}

void Buddha::add_kinddeedtype() {
    const string& id = ctx->arg("id");
    if( id.empty()) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "kinddeedtype id is empty .");
        return ;
    }

    const string& desc = ctx->arg("desc");
    if( desc.empty()) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "kinddeedtype desc is empty .");
        return ;
    }

    if( !is_founder() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__,ctx->initiator() + " is not founder, have no authority to add kinddeedtype .");
        return ;
    }

    //判断善举类型是否存在
    kinddeedtype ent;
    if( _is_kinddeedtype_exist(id,ent)) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "kinddeedtype " + id + " is exist .");
        return ;
    }

    ent.set_id(stoll(id));
    ent.set_desc(desc);
    if (!get_kinddeedtype_table().put(ent)) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "table put failure .", ent.to_json());
        return;
    }

    _log_ok(__FILE__, __FUNCTION__, __LINE__, "create success .", ent.to_json());
}

void Buddha::delete_kinddeedtype() {
    const string& id = ctx->arg("id");
    if( id.empty()) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "kinddeedtype id is empty .");
        return ;
    }

    if( !is_founder() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__,ctx->initiator() + " is not founder, have no authority to delete kinddeedtype .");
        return ;
    }

    //判断善举类型是否存在
    kinddeedtype ent;
    if( !_is_kinddeedtype_exist(id,ent)) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "kindeed type " + id + " is not exist .");
        return ;
    }

    //删除此善举类型
    if( !_delete_kinddeedtype_record(id) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "delete failure .", ent.to_json());
        return;
    }

    _log_ok(__FILE__, __FUNCTION__, __LINE__, "create success .", ent.to_json());
}

void Buddha::update_kinddeedtype() {
    const string& id = ctx->arg("id");
    if( id.empty()) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "kinddeedtype id is empty .");
        return ;
    }

    const string& desc = ctx->arg("desc");
    if( desc.empty()) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "kinddeedtype desc is empty .");
        return ;
    }

    if( !is_founder() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__,ctx->initiator() + " is not founder, have no authority to update kinddeedtype .");
        return ;
    }

    //判断善举类型是否存在
    kinddeedtype ent;
    if( !_is_kinddeedtype_exist(id,ent)) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "kindeedtype " + id + " is not exist .");
        return ;
    }

    //删除此善举类型
    if( !_delete_kinddeedtype_record(id) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "delete failure .", ent.to_json());
        return;
    }

    ent.set_id(stoll(id));
    ent.set_desc(desc);
    if (!get_kinddeedtype_table().put(ent)) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "table put failure .", ent.to_json());
        return;
    }

    _log_ok(__FILE__, __FUNCTION__, __LINE__, ent.to_json());
}

void Buddha::find_kinddeedtype() {
    const string& id = ctx->arg("id");
    if( id.empty()) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "kinddeedtype id is empty .");
        return ;
    }

    //判断善举类型是否存在
    kinddeedtype ent;
    if (!_is_kinddeedtype_exist(id, ent))  {
        _log_ok(__FILE__, __FUNCTION__, __LINE__, "kinddeedtype " + id + " is not exist .");
        return ;
    }

    _log_ok(__FILE__, __FUNCTION__, __LINE__, ent.to_string());
}

void Buddha::list_kinddeedtype() {
    xchain::json v ;
    if(!_scan_kinddeedtype(v) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "scan table failure .");
        return;
    }
    _log_ok(__FILE__, __FUNCTION__, __LINE__, v);
}



DEFINE_METHOD(Buddha, add_kinddeedtype)         { self.add_kinddeedtype();          }
DEFINE_METHOD(Buddha, delete_kinddeedtype)      { self.delete_kinddeedtype();       }
DEFINE_METHOD(Buddha, update_kinddeedtype)      { self.update_kinddeedtype();       }
DEFINE_METHOD(Buddha, find_kinddeedtype)        { self.find_kinddeedtype();         }
DEFINE_METHOD(Buddha, list_kinddeedtype)        { self.list_kinddeedtype();         }

