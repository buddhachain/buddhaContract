#include <inttypes.h>
#include "xchain/xchain.h"
#include "xchain/account.h"
#include "xchain/contract.pb.h"
#include "xchain/syscall.h"
#include "buddha.pb.h"
#include "buddha.h"

#include <iostream>
using namespace std;


void Buddha::add_beforecomment() {
    const string& kdid = ctx->arg("kdid");
    if( kdid.empty()) {
        _log_error(__FUNCTION__, __LINE__, "beforecomment kdid is empty .");
        return ;
    }

    const string& satisfaction = ctx->arg("satisfaction");
    if( satisfaction.empty()) {
        _log_error(__FUNCTION__, __LINE__, "beforecomment satisfaction is empty .");
        return ;
    }

    const string& labels = ctx->arg("labels");
    xchain::json label_array = xchain::json::parse(labels);
    // mycout << label_array.dump() << endl ;
    if (!label_array.is_array()) {
        _log_error(__FUNCTION__, __LINE__, "field 'labels' need to be array .");
        return;
    }
    
    if ( label_array.empty() || label_array.size() == 0) {
        _log_error(__FUNCTION__, __LINE__, "filed 'labels' empty .");
        return;
    }

    //判断所有标签类型都在评论标签表中
    if( !_is_all_types_exist_in_commentlabel(label_array)) {
        _log_error(__FUNCTION__, __LINE__, "beforecomment type failure .");
        return ;
    }

    const string& comment = ctx->arg("comment");
    if( comment.empty()) {
        _log_error(__FUNCTION__, __LINE__, "beforecomment comment is empty .");
        return ;
    }

    const string& timestamp = ctx->arg("timestamp");
    if( timestamp.empty()) {
        _log_error(__FUNCTION__, __LINE__, "beforecomment timestamp is empty .");
        return ;
    }

    const string& owner = ctx->initiator() ;

    //判断售前点评是否存在
    beforecomment ent;
    if( _is_beforecomment_exist(kdid,owner,ent)) {
        _log_error(__FUNCTION__, __LINE__, "beforecomment " + kdid + " is exist .");
        return ;
    }

    ent.set_owner(owner);
    ent.set_kdid(kdid);
    ent.set_satisfaction(stoll(satisfaction));
    ent.set_labels(labels);    
    ent.set_comment(comment);
    ent.set_timestamp(timestamp);
    if (!get_beforecomment_table().put(ent)) {
        _log_error(__FUNCTION__, __LINE__, "table put failure .", ent.to_json());
        return;
    }

    _log_ok(__FUNCTION__, __LINE__, "create success .", ent.to_json());
}

void Buddha::delete_beforecomment() {
    const string& kdid = ctx->arg("kdid");
    if( kdid.empty()) {
        _log_error(__FUNCTION__, __LINE__, "beforecomment kdid is empty .");
        return ;
    }

    const string& owner = ctx->initiator();

    //判断售前点评是否存在
    beforecomment ent;
    if( !_is_beforecomment_exist(kdid,owner,ent)) {
        _log_error(__FUNCTION__, __LINE__, "beforecomment " + kdid + " is not exist .");
        return ;
    }

    if( !is_founder() &&
        ent.owner() != owner) {
        _log_error(__FUNCTION__, __LINE__,ctx->initiator() + " is not founder nor owner, have no authority to delete the comment .");
        return ;
    }

    //删除此售前点评
    if( !_delete_beforecomment_record(kdid,owner) ) {
        _log_error(__FUNCTION__, __LINE__, "delete failure .", ent.to_json());
        return;
    }

    _log_ok(__FUNCTION__, __LINE__, "create success .", ent.to_json());
}

void Buddha::update_beforecomment() {
    const string& kdid = ctx->arg("kdid");
    if( kdid.empty()) {
        _log_error(__FUNCTION__, __LINE__, "beforecomment kdid is empty .");
        return ;
    }

    const string& satisfaction = ctx->arg("satisfaction");
    if( satisfaction.empty()) {
        _log_error(__FUNCTION__, __LINE__, "beforecomment satisfaction is empty .");
        return ;
    }

    const string& labels = ctx->arg("labels");
    auto label_array = xchain::json::parse(labels);
    // mycout << label_array.dump() << endl ;
    if (!label_array.is_array()) {
        _log_error(__FUNCTION__, __LINE__, "field 'labels' need to be array .");
        return;
    }
    
    if ( label_array.empty() || label_array.size() == 0) {
        _log_error(__FUNCTION__, __LINE__, "filed 'labels' empty .");
        return;
    }

    //判断所有标签类型都在评论标签表中
    if( !_is_all_types_exist_in_commentlabel(label_array)) {
        _log_error(__FUNCTION__, __LINE__, "beforecomment type failure .");
        return ;
    }

    const string& comment = ctx->arg("comment");
    if( comment.empty()) {
        _log_error(__FUNCTION__, __LINE__, "beforecomment comment is empty .");
        return ;
    }

    const string& timestamp = ctx->arg("timestamp");
    if( timestamp.empty()) {
        _log_error(__FUNCTION__, __LINE__, "beforecomment timestamp is empty .");
        return ;
    }

    const string& owner = ctx->initiator() ;

    //判断售前点评是否存在
    beforecomment ent;
    if( !_is_beforecomment_exist(kdid,owner,ent)) {
        _log_error(__FUNCTION__, __LINE__, "beforecomment " + kdid + " is not exist .");
        return ;
    }

    if( ent.owner() != owner) {
        _log_error(__FUNCTION__, __LINE__,ctx->initiator() + " is not owner, have no authority to update the comment .");
        return ;
    }

    //删除此售前点评
    if( !_delete_beforecomment_record(kdid,owner) ) {
        _log_error(__FUNCTION__, __LINE__, "delete failure .", ent.to_json());
        return;
    }

    ent.set_owner(owner);
    ent.set_kdid(kdid);
    ent.set_satisfaction(stoll(satisfaction));
    ent.set_labels(labels);    
    ent.set_comment(comment);
    ent.set_timestamp(timestamp);
    if (!get_beforecomment_table().put(ent)) {
        _log_error(__FUNCTION__, __LINE__, "table put failure .", ent.to_json());
        return;
    }

    _log_ok(__FUNCTION__, __LINE__, "create success .", ent.to_json());
}

void Buddha::find_beforecomment() {
    const string& kdid = ctx->arg("kdid");
    if( kdid.empty()) {
        _log_error(__FUNCTION__, __LINE__, "beforecomment kdid is empty .");
        return ;
    }

    //判断善举是否存在
    kinddeed kd;
    if (!_is_kinddeed_exist(kdid, kd))  {
        _log_error(__FUNCTION__, __LINE__, "kinddeed " + kdid + " is not exist .");
        return ;
    }

    const string& owner = ctx->arg("owner");

    if( !owner.empty()) {
        //判断售前点评是否存在
        beforecomment ent;
        if (!_is_beforecomment_exist(kdid,owner,ent))  {
            _log_ok(__FUNCTION__, __LINE__, "create success .", ent.to_json());
            return ;
        }

        if( is_founder() ||                      //基金会成员
            owner == ctx->initiator() ||        //点评的所有者
            kd.owner() == ctx->initiator() ) { //善举所有者
            _log_ok(__FUNCTION__, __LINE__, ent.to_string());
            return ;
        }

        _log_error(__FUNCTION__, __LINE__,ctx->initiator() + " is not founder nor owner, have no authority to delete the comment .");
        return ;

    }

    //owner字段为空的情况
    //此时如果是基金会成员和善举所有者调用，报错
    if( is_founder() ||                          //基金会成员
        kd.owner() == ctx->initiator() ) {      //善举所有者
        _log_error(__FUNCTION__, __LINE__, "beforecomment owner should be empty .");
        return ;
    }

    //点评所有者调用，直接查询
    //判断售前点评是否存在
    beforecomment ent;
    if (!_is_beforecomment_exist(kdid,ctx->initiator(),ent))  {
        _log_ok(__FUNCTION__, __LINE__, "beforecomment " + kdid + " is not exist .");
        return ;
    }
    _log_ok(__FUNCTION__, __LINE__, "create success .", ent.to_json());
}

void Buddha::list_beforecomment() {
    const string& kdid = ctx->arg("kdid");
    if( kdid.empty()) {
        _log_error(__FUNCTION__, __LINE__, "beforecomment kdid is empty .");
        return ;
    }

    //判断善举是否存在
    kinddeed kd;
    if (!_is_kinddeed_exist(kdid, kd))  {
        _log_error(__FUNCTION__, __LINE__, "kinddeed " + kdid + " is not exist .");
        return ;
    }

    auto it = get_beforecomment_table().scan({{"kdid",kdid}});
    int i = 0;
    string ret;
    while(it->next()) {
        beforecomment ent;
        if (!it->get(&ent)) {
            _log_error(__FUNCTION__, __LINE__, "beforecomment table get failure : " + it->error(true));
            return;
        }

        i++;
        ret += ent.to_string();
    }
    _log_ok(__FUNCTION__, __LINE__, v);
}


DEFINE_METHOD(Buddha, add_beforecomment)        { self.add_beforecomment();         }
DEFINE_METHOD(Buddha, delete_beforecomment)     { self.delete_beforecomment();      }
DEFINE_METHOD(Buddha, update_beforecomment)     { self.update_beforecomment();      }
DEFINE_METHOD(Buddha, find_beforecomment)       { self.find_beforecomment();        }
DEFINE_METHOD(Buddha, list_beforecomment)       { self.list_beforecomment();        }
