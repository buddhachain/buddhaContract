#include <inttypes.h>
#include "xchain/xchain.h"
#include "xchain/account.h"
#include "xchain/contract.pb.h"
#include "xchain/syscall.h"
#include "buddha.pb.h"
#include "buddha.h"

#include <iostream>
using namespace std;

xchain::json BKinddeedType::to_json() {
    xchain::json j = {
        {"id", id()},
        {"desc", desc()},
    };

    return j;
}


bool Main::_is_kinddeedtype_exist(kinddeedtype& ent, const string& id) {
    if (!get_kinddeedtype_table().find({{"id", id}}, &ent))
        return false;

    return true;
}

bool Main::_scan_kinddeedtype(xchain::json& ja, const string& cond) {
    auto it = get_kinddeedtype_table().scan({{"id",cond}});
    while(it->next() ) {
        kinddeedtype ent;
        if (!it->get(&ent) ) {
            mycout << "kinddeedtype table get failure : " << it->error(true) << endl;
            return false;
        }

        ja.push_back(ent.to_json());
    }

    return true;
}

bool Main::_delete_kinddeedtype_record(const string& id) {
    kinddeedtype ent;
    if (!_is_kinddeedtype_exist(ent, id)){
        mycout << "kinddeedtype " << id << " is not exist ." << endl ;
        return false;
    }

    if( !get_kinddeedtype_table().del(ent) ) {
        mycout << "delete kinddeedtype " << ent.to_json().dump() << " failure ." << endl ;
        return false;
    }

    mycout << "delete kinddeedtype " << ent.to_json().dump() << " success ." << endl ;
    return true;
}

namespace 分界线{}

void Main::add_kinddeedtype() {
    const string& id = ctx->arg("id");
    if( id.empty() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "kinddeedtype id is empty .");
        return ;
    }

    const string& desc = ctx->arg("desc");
    if( desc.empty() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "kinddeedtype desc is empty .");
        return ;
    }

    //判断是否是基金会成员
    if( !is_founder() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__,ctx->initiator() + " is not founder, have no authority to add kinddeedtype .");
        return ;
    }

    //判断善举类型是否存在
    kinddeedtype ent;
    if( _is_kinddeedtype_exist(ent, id) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "kinddeedtype " + id + " is exist .", ent.to_json());
        return ;
    }

    ent.set_id(stoll(id));
    ent.set_desc(desc);
    if (!get_kinddeedtype_table().put(ent) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "table put failure .", ent.to_json());
        return;
    }

    _log_ok(__FILE__, __FUNCTION__, __LINE__, "create", ent.to_json());
}

void Main::delete_kinddeedtype() {
    const string& id = ctx->arg("id");
    if( id.empty() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "kinddeedtype id is empty .");
        return ;
    }

    //判断是否是基金会成员
    if( !is_founder() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__,ctx->initiator() + " is not founder, have no authority to delete kinddeedtype .");
        return ;
    }

    //判断善举类型是否存在
    kinddeedtype ent;
    if( !_is_kinddeedtype_exist(ent, id) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "kindeed type " + id + " is not exist .");
        return ;
    }

    //删除此善举类型
    if( !_delete_kinddeedtype_record(id) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "delete failure .", ent.to_json());
        return;
    }

    _log_ok(__FILE__, __FUNCTION__, __LINE__, "delete", ent.to_json());
}

void Main::update_kinddeedtype() {
    const string& id = ctx->arg("id");
    if( id.empty() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "kinddeedtype id is empty .");
        return ;
    }

    const string& desc = ctx->arg("desc");
    if( desc.empty() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "kinddeedtype desc is empty .");
        return ;
    }

    //判断是否是基金会成员
    if( !is_founder() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__,ctx->initiator() + " is not founder, have no authority to update kinddeedtype .");
        return ;
    }

    //判断善举类型是否存在
    kinddeedtype ent;
    if( !_is_kinddeedtype_exist(ent, id) ) {
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
    if (!get_kinddeedtype_table().put(ent) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "table put failure .", ent.to_json());
        return;
    }

    _log_ok(__FILE__, __FUNCTION__, __LINE__, "update", ent.to_json());
}

void Main::find_kinddeedtype() {
    const string& id = ctx->arg("id");
    if( id.empty() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "kinddeedtype id is empty .");
        return ;
    }

    //判断善举类型是否存在
    kinddeedtype ent;
    if (!_is_kinddeedtype_exist(ent, id))  {
        _log_ok(__FILE__, __FUNCTION__, __LINE__, "kinddeedtype " + id + " is not exist .");
        return ;
    }

    _log_ok(__FILE__, __FUNCTION__, __LINE__, "find", ent.to_json());
}

void Main::list_kinddeedtype() {
    xchain::json ja ;
    if(!_scan_kinddeedtype(ja) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "scan table failure .");
        return;
    }
    _log_ok(__FILE__, __FUNCTION__, __LINE__, "scan", ja);
}



DEFINE_METHOD(Buddha, add_kinddeedtype)         { self.add_kinddeedtype();          }
DEFINE_METHOD(Buddha, delete_kinddeedtype)      { self.delete_kinddeedtype();       }
DEFINE_METHOD(Buddha, update_kinddeedtype)      { self.update_kinddeedtype();       }
DEFINE_METHOD(Buddha, find_kinddeedtype)        { self.find_kinddeedtype();         }
DEFINE_METHOD(Buddha, list_kinddeedtype)        { self.list_kinddeedtype();         }

