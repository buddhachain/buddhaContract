#include <inttypes.h>
#include "xchain/xchain.h"
#include "xchain/account.h"
#include "xchain/contract.pb.h"
#include "xchain/syscall.h"
#include "buddha.pb.h"
#include "buddha.h"

#include <iostream>
using namespace std;

xchain::json BCommentLabel::to_json() const {
    xchain::json j = {
        {"id", id()},
        {"desc", desc()},
    };

    return j;
}

bool Main::_is_commentlabel_exist(commentlabel& ent, const string& id) {
    if (!get_commentlabel_table().find({{"id", id}}, &ent))
        return false;

    return true;
}

bool Main::_is_all_types_exist_in_commentlabel(const xchain::json& label_array) {
    for(int i = 0 ; i < label_array.size() ; i++) {
        string id = label_array.at(i).template get<string>();
        commentlabel ent;
        if( !_is_commentlabel_exist(ent, id) ) {
            mycout << "type " << id << " not exist in commentlabel table ." << endl;
            return false;
        }            
    }

    return true;
}

bool Main::_scan_commentlabel(xchain::json& ja, const string& cond) {
    auto it = get_commentlabel_table().scan({{"id",cond}});
    while(it->next() ) {
        commentlabel ent;
        if (!it->get(&ent) ) {
            mycout << "commentlabel table get failure : " << it->error(true) << endl;
            return false;
        }

        ja.push_back(ent.to_json());
    }

    return true;
}

bool Main::_delete_commentlabel_record(const string& id) {
    commentlabel ent;
    if (!_is_commentlabel_exist(ent, id)){
        mycout << "commentlabel " << id << " is not exist ." << endl ;
        return false;
    }

    if( !get_commentlabel_table().del(ent) ) {
        mycout << "delete commentlabel " << ent.to_json().dump() << " failure ." << endl ;
        return false;
    }

    mycout << "delete commentlabel " << ent.to_json().dump() << " success ." << endl ;
    return true;
}

namespace 分界线{}


void Main::add_commentlabel() {
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
    if( _is_commentlabel_exist(ent, id) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "commentlabel " + id + " is exist .", ent.to_json() );
        return ;
    }

    ent.set_id(stoll(id));
    ent.set_desc(desc);
    if (!get_commentlabel_table().put(ent) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "commentlabel table put failure .", ent.to_json());
        return;
    }

    _log_ok(__FILE__, __FUNCTION__, __LINE__, "create", ent.to_json());
}

void Main::delete_commentlabel() {
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
    if( !_is_commentlabel_exist(ent, id) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "kindeed type " + id + " is not exist .");
        return ;
    }

    //删除此善举标签
    if( !_delete_commentlabel_record(id) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "delete failure .", ent.to_json());
        return;
    }

    _log_ok(__FILE__, __FUNCTION__, __LINE__, "delete", ent.to_json());
}

void Main::update_commentlabel() {
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
    if( !_is_commentlabel_exist(ent, id) ) {
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
        _log_error(__FILE__, __FUNCTION__, __LINE__, "commentlabel table put failure .", ent.to_json());
        return;
    }

    _log_ok(__FILE__, __FUNCTION__, __LINE__, "update", ent.to_json());
}

void Main::find_commentlabel() {
    const string& id = ctx->arg("id");
    if( id.empty() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "commentlabel id is empty .");
        return ;
    }

    //判断评论标签是否存在
    commentlabel ent;
    if (!_is_commentlabel_exist(ent, id))  {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "commentlabel " + id + " is not exist .");
        return ;
    }

    _log_ok(__FILE__, __FUNCTION__, __LINE__, "find", ent.to_json());
}

void Main::list_commentlabel() {
    xchain::json ja ;
    if(!_scan_beforecomment(ja) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "scan table failure .");
        return;
    }

    _log_ok(__FILE__, __FUNCTION__, __LINE__, "scan", ja);
}


DEFINE_METHOD(Main, add_commentlabel)         { self.add_commentlabel();          }
DEFINE_METHOD(Main, delete_commentlabel)      { self.delete_commentlabel();       }
DEFINE_METHOD(Main, update_commentlabel)      { self.update_commentlabel();       }
DEFINE_METHOD(Main, find_commentlabel)        { self.find_commentlabel();         }
DEFINE_METHOD(Main, list_commentlabel)        { self.list_commentlabel();         }