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


void Buddha::add_kinddeedtype() {
    const string& id = ctx->arg("id");
    if( id.empty()) {
        _log_error(__FUNCTION__, __LINE__,"kinddeedtype id is empty .");
        return ;
    }

    const string& desc = ctx->arg("desc");
    if( desc.empty()) {
        _log_error(__FUNCTION__, __LINE__,"kinddeedtype desc is empty .");
        return ;
    }

    if( !is_founder() ) {
        _log_error(__FUNCTION__, __LINE__,ctx->initiator() + " is not founder, have no authority to add kinddeedtype .");
        return ;
    }

    //判断善举类型是否存在
    kinddeedtype ent;
    if( _is_kinddeedtype_exist(id,ent)) {
        _log_error(__FUNCTION__, __LINE__,"kinddeedtype " + id + " is exist .");
        return ;
    }

    ent.set_id(stoll(id));
    ent.set_desc(desc);
    if (!get_kinddeedtype_table().put(ent)) {
        _log_error(__FUNCTION__, __LINE__,"kinddeedtype table put " + ent.to_string() + " failure .");
        return;
    }

    _log_ok(__FUNCTION__, __LINE__, "add kinddeedtype " + ent.to_string() + " success .");
}

void Buddha::delete_kinddeedtype() {
    const string& id = ctx->arg("id");
    if( id.empty()) {
        _log_error(__FUNCTION__, __LINE__,"kinddeedtype id is empty .");
        return ;
    }

    if( !is_founder() ) {
        _log_error(__FUNCTION__, __LINE__,ctx->initiator() + " is not founder, have no authority to delete kinddeedtype .");
        return ;
    }

    //判断善举类型是否存在
    kinddeedtype ent;
    if( !_is_kinddeedtype_exist(id,ent)) {
        _log_error(__FUNCTION__, __LINE__,"kindeed type " + id + " is not exist .");
        return ;
    }

    //删除此善举类型
    if( !_delete_kinddeedtype_record(id) ) {
        _log_error(__FUNCTION__, __LINE__,"delete kinddeedtype " + ent.to_string() + " failure .");
        return;
    }

    _log_ok(__FUNCTION__, __LINE__, "delete kinddeedtype " + ent.to_string() + " success .");
}

void Buddha::update_kinddeedtype() {
    const string& id = ctx->arg("id");
    if( id.empty()) {
        _log_error(__FUNCTION__, __LINE__,"kinddeedtype id is empty .");
        return ;
    }

    const string& desc = ctx->arg("desc");
    if( desc.empty()) {
        _log_error(__FUNCTION__, __LINE__,"kinddeedtype desc is empty .");
        return ;
    }

    if( !is_founder() ) {
        _log_error(__FUNCTION__, __LINE__,ctx->initiator() + " is not founder, have no authority to update kinddeedtype .");
        return ;
    }

    //判断善举类型是否存在
    kinddeedtype ent;
    if( !_is_kinddeedtype_exist(id,ent)) {
        _log_error(__FUNCTION__, __LINE__,"kindeedtype " + id + " is not exist .");
        return ;
    }

    //删除此善举类型
    if( !_delete_kinddeedtype_record(id) ) {
        _log_error(__FUNCTION__, __LINE__,"delete kinddeedtype " + ent.to_string() + " failure .");
        return;
    }

    ent.set_id(stoll(id));
    ent.set_desc(desc);
    if (!get_kinddeedtype_table().put(ent)) {
        _log_error(__FUNCTION__, __LINE__,"kinddeedtype table put " + ent.to_string() + " failure .");
        return;
    }

    _log_ok(__FUNCTION__, __LINE__, "update kinddeedtype " + ent.to_string() + " success .");
}

void Buddha::find_kinddeedtype() {
    const string& id = ctx->arg("id");
    if( id.empty()) {
        _log_error(__FUNCTION__, __LINE__,"kinddeedtype id is empty .");
        return ;
    }

    //判断善举类型是否存在
    kinddeedtype ent;
    if (!_is_kinddeedtype_exist(id, ent))  {
        _log_ok(__FUNCTION__, __LINE__, "kinddeedtype " + id + " is not exist .");
        return ;
    }

    _log_ok(__FUNCTION__, __LINE__, ent.to_string());
}

void Buddha::list_kinddeedtype() {
    auto it = get_kinddeedtype_table().scan({{"id",""}});
    int i = 0;
    string ret;
    while(it->next()) {
        kinddeedtype ent;
        if (!it->get(&ent)) {
            _log_error(__FUNCTION__, __LINE__, "kinddeedtype table get failure : " + it->error(true));
            return;
        }

        i++;
        ret += ent.to_string();
    }
    _log_ok(__FUNCTION__, __LINE__, "size=" + to_string(i) + " " + ret);
}



DEFINE_METHOD(Buddha, add_kinddeedtype)         { self.add_kinddeedtype();          }
DEFINE_METHOD(Buddha, delete_kinddeedtype)      { self.delete_kinddeedtype();       }
DEFINE_METHOD(Buddha, update_kinddeedtype)      { self.update_kinddeedtype();       }
DEFINE_METHOD(Buddha, find_kinddeedtype)        { self.find_kinddeedtype();         }
DEFINE_METHOD(Buddha, list_kinddeedtype)        { self.list_kinddeedtype();         }

