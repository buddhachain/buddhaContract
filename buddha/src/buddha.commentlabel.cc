#include <inttypes.h>
#include "xchain/xchain.h"
#include "xchain/account.h"
#include "xchain/contract.pb.h"
#include "xchain/syscall.h"
#include "buddha.pb.h"
#include "buddha.h"

#include <iostream>
using namespace std;

void Buddha::add_commentlabel() {
    const string& id = ctx->arg("id");
    if( id.empty()) {
        _log_error(__FUNCTION__, __LINE__, "commentlabel id is empty .");
        return ;
    }

    const string& desc = ctx->arg("desc");
    if( desc.empty()) {
        _log_error(__FUNCTION__, __LINE__, "commentlabel desc is empty .");
        return ;
    }

    if( !is_founder() ) {
        _log_error(__FUNCTION__, __LINE__,ctx->initiator() + " is not founder, have no authority to add commentlabel .");
        return ;
    }

    //判断评论标签是否存在
    commentlabel ent;
    if( _is_commentlabel_exist(id,ent)) {
        _log_error(__FUNCTION__, __LINE__, "commentlabel " + id + " is exist .");
        return ;
    }

    ent.set_id(stoll(id));
    ent.set_desc(desc);
    if (!get_commentlabel_table().put(ent)) {
        _log_error(__FUNCTION__, __LINE__, "table put failure .", ent.to_json());
        return;
    }

    _log_ok(__FUNCTION__, __LINE__, "create success .", ent.to_json());
}

void Buddha::delete_commentlabel() {
    const string& id = ctx->arg("id");
    if( id.empty()) {
        _log_error(__FUNCTION__, __LINE__, "commentlabel id is empty .");
        return ;
    }

    if( !is_founder() ) {
        _log_error(__FUNCTION__, __LINE__,ctx->initiator() + " is not founder, have no authority to delete commentlabel .");
        return ;
    }

    //判断评论标签是否存在
    commentlabel ent;
    if( !_is_commentlabel_exist(id,ent)) {
        _log_error(__FUNCTION__, __LINE__, "kindeed type " + id + " is not exist .");
        return ;
    }

    //删除此善举标签
    if( !_delete_commentlabel_record(id) ) {
        _log_error(__FUNCTION__, __LINE__, "delete failure .", ent.to_json());
        return;
    }

    _log_ok(__FUNCTION__, __LINE__, "create success .", ent.to_json());
}

void Buddha::update_commentlabel() {
    const string& id = ctx->arg("id");
    if( id.empty()) {
        _log_error(__FUNCTION__, __LINE__, "commentlabel id is empty .");
        return ;
    }

    const string& desc = ctx->arg("desc");
    if( desc.empty()) {
        _log_error(__FUNCTION__, __LINE__, "commentlabel desc is empty .");
        return ;
    }

    if( !is_founder() ) {
        _log_error(__FUNCTION__, __LINE__,ctx->initiator() + " is not founder, have no authority to update commentlabel .");
        return ;
    }

    //判断评论标签是否存在
    commentlabel ent;
    if( !_is_commentlabel_exist(id,ent)) {
        _log_error(__FUNCTION__, __LINE__, "commentlabel " + id + " is not exist .");
        return ;
    }

    //删除此善举标签
    if( !_delete_commentlabel_record(id) ) {
        _log_error(__FUNCTION__, __LINE__, "delete failure .", ent.to_json());
        return;
    }

    ent.set_id(stoll(id));
    ent.set_desc(desc);
    if (!get_commentlabel_table().put(ent)) {
        _log_error(__FUNCTION__, __LINE__, "table put failure .", ent.to_json());
        return;
    }

    _log_ok(__FUNCTION__, __LINE__, "create success .", ent.to_json());
}

void Buddha::find_commentlabel() {
    const string& id = ctx->arg("id");
    if( id.empty()) {
        _log_error(__FUNCTION__, __LINE__, "commentlabel id is empty .");
        return ;
    }

    //判断评论标签是否存在
    commentlabel ent;
    if (!_is_commentlabel_exist(id, ent))  {
        _log_error(__FUNCTION__, __LINE__, "commentlabel " + id + " is not exist .");
        return ;
    }

    _log_ok(__FUNCTION__, __LINE__, ent.to_string());
}

void Buddha::list_commentlabel() {
    auto it = get_commentlabel_table().scan({{"id",""}});
    int i = 0;
    string ret;
    while(it->next()) {
        commentlabel ent;
        if (!it->get(&ent)) {
            _log_error(__FUNCTION__, __LINE__, "commentlabel table get failure : " + it->error(true));
            return;
        }

        i++;
        ret += ent.to_string();
    }
    _log_ok(__FUNCTION__, __LINE__, v);
}


DEFINE_METHOD(Buddha, add_commentlabel)         { self.add_commentlabel();          }
DEFINE_METHOD(Buddha, delete_commentlabel)      { self.delete_commentlabel();       }
DEFINE_METHOD(Buddha, update_commentlabel)      { self.update_commentlabel();       }
DEFINE_METHOD(Buddha, find_commentlabel)        { self.find_commentlabel();         }
DEFINE_METHOD(Buddha, list_commentlabel)        { self.list_commentlabel();         }