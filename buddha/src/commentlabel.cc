#include <inttypes.h>
#include "xchain/xchain.h"
#include "xchain/account.h"
#include "xchain/contract.pb.h"
#include "xchain/syscall.h"
#include "buddha.pb.h"
#include "buddha.h"

#include <iostream>
using namespace std;

string commentlabel::to_string() {
    string str ;
    str += "{" ;
    str += std::to_string(id()) + ",";
    str += desc();
    str += "}";
    return str;
}

xchain::json commentlabel::to_json() {
    xchain::json j = {
        {"id", id()},
        {"desc", desc()},
    };

    return j;
}

bool Buddha::_is_commentlabel_exist(const string& id,commentlabel& ent) {
    if (!get_commentlabel_table().find({{"id", id}}, &ent))
        return false;

    return true;
}

bool Buddha::_is_all_types_exist_in_commentlabel(const xchain::json& label_array) {
    for(int i = 0 ; i < label_array.size() ; i++) {
        string id = label_array.at(i).template get<string>();
        commentlabel ent;
        if( !_is_commentlabel_exist(id,ent) ) {
            mycout << "type " << id << " not exist in commentlabel table ." << endl;
            return false;
        }            
    }

    return true;
}

bool Buddha::_scan_commentlabel(xchain::json& v, const string& cond) {
    auto it = get_commentlabel_table().scan({{"id",cond}});
    while(it->next() ) {
        commentlabel ent;
        if (!it->get(&ent) ) {
            mycout << "commentlabel table get failure : " << it->error(true) << endl;
            return false;
        }

        v.push_back(ent.to_json());
    }

    return true;
}

bool Buddha::_delete_commentlabel_record(const string& id) {
    commentlabel ent;
    if (!_is_commentlabel_exist(id, ent)){
        mycout << "commentlabel " << id << " is not exist ." << endl ;
        return false;
    }

    if( !get_commentlabel_table().del(ent) ) {
        mycout << "delete commentlabel " << ent.to_string() << " failure ." << endl ;
        return false;
    }

    mycout << "delete commentlabel " << ent.to_string() << " success ." << endl ;
    return true;
}

namespace 分界线{}


void Buddha::add_commentlabel() {
    const string& id = ctx->arg("id");
    if( id.empty() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "commentlabel id is empty .");
        return ;
    }

    const string& desc = ctx->arg("desc");
    if( desc.empty() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "commentlabel desc is empty .");
        return ;
    }

    //身份检查，基金会成员具有权限
    if( !is_founder() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__,ctx->initiator() + " is not founder, have no authority to add commentlabel .");
        return ;
    }

    //判断评论标签是否存在
    commentlabel ent;
    if( _is_commentlabel_exist(id,ent) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "commentlabel " + id + " is exist .", ent.to_json() );
        return ;
    }

    ent.set_id(stoll(id));
    ent.set_desc(desc);
    if (!get_commentlabel_table().put(ent) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "table put failure .", ent.to_json());
        return;
    }

    _log_ok(__FILE__, __FUNCTION__, __LINE__, "create success .", ent.to_json());
}

void Buddha::delete_commentlabel() {
    const string& id = ctx->arg("id");
    if( id.empty() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "commentlabel id is empty .");
        return ;
    }

    //身份检查，基金会成员具有权限
    if( !is_founder() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__,ctx->initiator() + " is not founder, have no authority to delete commentlabel .");
        return ;
    }

    //判断评论标签是否存在
    commentlabel ent;
    if( !_is_commentlabel_exist(id,ent) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "kindeed type " + id + " is not exist .");
        return ;
    }

    //删除此善举标签
    if( !_delete_commentlabel_record(id) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "delete failure .", ent.to_json());
        return;
    }

    _log_ok(__FILE__, __FUNCTION__, __LINE__, "create success .", ent.to_json());
}

void Buddha::update_commentlabel() {
    const string& id = ctx->arg("id");
    if( id.empty() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "commentlabel id is empty .");
        return ;
    }

    const string& desc = ctx->arg("desc");
    if( desc.empty() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "commentlabel desc is empty .");
        return ;
    }

    //身份检查，基金会成员具有权限
    if( !is_founder() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__,ctx->initiator() + " is not founder, have no authority to update commentlabel .");
        return ;
    }

    //判断评论标签是否存在
    commentlabel ent;
    if( !_is_commentlabel_exist(id,ent) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "commentlabel " + id + " is not exist .");
        return ;
    }

    //删除此善举标签
    if( !_delete_commentlabel_record(id) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "delete failure .", ent.to_json());
        return;
    }

    ent.set_id(stoll(id));
    ent.set_desc(desc);
    if (!get_commentlabel_table().put(ent) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "table put failure .", ent.to_json());
        return;
    }

    _log_ok(__FILE__, __FUNCTION__, __LINE__, "create success .", ent.to_json());
}

void Buddha::find_commentlabel() {
    const string& id = ctx->arg("id");
    if( id.empty() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "commentlabel id is empty .");
        return ;
    }

    //判断评论标签是否存在
    commentlabel ent;
    if (!_is_commentlabel_exist(id, ent))  {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "commentlabel " + id + " is not exist .");
        return ;
    }

    _log_ok(__FILE__, __FUNCTION__, __LINE__, ent.to_string());
}

void Buddha::list_commentlabel() {
    xchain::json v ;
    if(!_scan_beforecomment(v) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "scan table failure .");
        return;
    }

    _log_ok(__FILE__, __FUNCTION__, __LINE__, v);
}


DEFINE_METHOD(Buddha, add_commentlabel)         { self.add_commentlabel();          }
DEFINE_METHOD(Buddha, delete_commentlabel)      { self.delete_commentlabel();       }
DEFINE_METHOD(Buddha, update_commentlabel)      { self.update_commentlabel();       }
DEFINE_METHOD(Buddha, find_commentlabel)        { self.find_commentlabel();         }
DEFINE_METHOD(Buddha, list_commentlabel)        { self.list_commentlabel();         }