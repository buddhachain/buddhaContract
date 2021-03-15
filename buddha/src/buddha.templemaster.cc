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

void Buddha::apply_join_temple(){
    // const string& id = ctx->arg("id");
    // if( id.empty()) {
    //     _log_error(__FUNCTION__, __LINE__,"id is empty .");
    //     return ;
    // }

    const string& templeid = ctx->arg("templeid");
    if( templeid.empty()) {
        _log_error(__FUNCTION__, __LINE__,"temple id is empty .");
        return ;
    }

    const string& masterid = ctx->initiator() ;

    if( !is_master()) {
        _log_error(__FUNCTION__, __LINE__, masterid + " is not master, have no authority to apply join temple .");
        return ;
    }

    //判断是否是寺院
    if( !_is_temple(templeid)) {
        _log_error(__FUNCTION__, __LINE__, templeid + " is not a temple .");
        return ;
    }

    //判断是否法师是否已经入驻此寺院
    templemaster ent;
    if( _is_in_temple(templeid, masterid, ent )) {
        _log_error(__FUNCTION__, __LINE__,masterid + " is already join temple .");
        return;
    }
    
    _delete_templemaster_record(templeid, masterid);
    
    // ent.set_id(id);
    ent.set_templeid(templeid);
    ent.set_masterid(masterid);
    ent.set_approved(false);
    if (!get_templemaster_table().put(ent)) {
        _log_error(__FUNCTION__, __LINE__,"templemaster table put " + ent.to_string() + " failure .");
        return;
    }

    _log_ok(__FUNCTION__, __LINE__, ent.to_string() + " apply join templemaster over, please wait for approve .");
}

void Buddha::approve_join_temple() {
    const string& templeid = ctx->arg("templeid");
    if( templeid.empty()) {
        _log_error(__FUNCTION__, __LINE__,"temple id is empty .");
        return ;
    }

    const string& masterid = ctx->arg("masterid");
    if( masterid.empty()) {
        _log_error(__FUNCTION__, __LINE__,"master id is empty .");
        return ;
    }

    if( !is_founder()) {
        _log_error(__FUNCTION__, __LINE__,ctx->initiator() + " is not founder, have no authority to approve master .");
        return ;
    }

    //判断是否是法师
    if( !_is_master(masterid)) {
        _log_error(__FUNCTION__, __LINE__, masterid + " is not a master .");
        return ;
    }

    //判断是否是寺院
    if( !_is_temple(templeid)) {
        _log_error(__FUNCTION__, __LINE__, templeid + " is not a temple .");
        return ;
    }

    //判断是否法师是否已经入驻此寺院
    templemaster ent;
    if( _is_in_temple(templeid, masterid,ent)) {
        _log_error(__FUNCTION__, __LINE__,ent.to_string() + " is already join temple .");
        return ;
    }

    //删除此寺院法师记录
    if( !_delete_templemaster_record(templeid, masterid) ) {
        _log_error(__FUNCTION__, __LINE__,"delete templemaster " + ent.to_string() + " failure .");
        return;
    }

    ent.set_approved(true);
    if (!get_templemaster_table().put(ent)) {
        _log_error(__FUNCTION__, __LINE__,"templemaster table put " + ent.to_string() + " failure .");
        return;
    }

    _log_ok(__FUNCTION__, __LINE__, "approve templemaster " + ent.to_string() + " success .");
}

void Buddha::recusal_join_temple() {
    const string& templeid = ctx->arg("templeid");
    if( templeid.empty()) {
        _log_error(__FUNCTION__, __LINE__,"temple id is empty .");
        return ;
    }

    const string& masterid = ctx->arg("masterid");
    if( masterid.empty()) {
        _log_error(__FUNCTION__, __LINE__,"master id is empty .");
        return ;
    }
    
    if( !is_founder()) {
        _log_error(__FUNCTION__, __LINE__,ctx->initiator() + " is not founder, have no authority to recusal master .");
        return ;
    }

    //判断寺院法师记录是否存在
    templemaster ent;
    if( !_is_templemaster_exist(templeid, masterid,ent)) {
        _log_error(__FUNCTION__, __LINE__,"temple " + templeid + ", master " + masterid + " is not exist .");
        return ;
    }

    //删除此寺院法师记录
    if( !_delete_templemaster_record(templeid, masterid) ) {
        _log_error(__FUNCTION__, __LINE__,"delete templemaster " + ent.to_string() + " failure .");
        return;
    }

    _log_ok(__FUNCTION__, __LINE__, "recusal templemaster " + ent.to_string() + " success .");
}

bool Buddha::is_in_temple() {
    const string& templeid = ctx->arg("templeid");
    if( templeid.empty()) {
        _log_error(__FUNCTION__, __LINE__,"temple id is empty .");
        return false;
    }

    const string& masterid = ctx->initiator();

    //判断是否是法师
    if( !_is_master(masterid)) {
        _log_error(__FUNCTION__, __LINE__, masterid + " is not a master, have no authority to query in some temple .");
        return false;
    }

    //判断是否是寺院
    if( !_is_temple(templeid)) {
        _log_error(__FUNCTION__, __LINE__,templeid + " is not a temple .");
        return false;
    }

    //判断是否法师是否已经入驻此寺院
    templemaster ent;
    if (!_is_in_temple(templeid, masterid, ent)) {
        _log_ok(__FUNCTION__, __LINE__, masterid + " is not join temple .") ;
        return false;
    }

    _log_ok(__FUNCTION__, __LINE__, masterid + " is join temple .") ;
    return true;
}

void Buddha::list_temple_master() {
    const string& templeid = ctx->arg("templeid");

    if( is_deployer() ||
        is_founder()) {
        auto it = get_templemaster_table().scan({{"templeid",templeid}});
        int i = 0;
        string ret;
        while(it->next()) {
            templemaster ent;
            if (!it->get(&ent)) {
                _log_error(__FUNCTION__, __LINE__, "templemaster table get failure : " + it->error(true));
                return;
            }

            i++;
            ret += ent.to_string();
        }
        _log_ok(__FUNCTION__, __LINE__, "size=" + to_string(i) + " " + ret);

        return ;
    }

    if( is_temple() ) {

        auto it = get_templemaster_table().scan({{"templeid",ctx->initiator()}});
        int i = 0;
        string ret;
        while(it->next()) {
            templemaster ent;
            if (!it->get(&ent)) {
                _log_error(__FUNCTION__, __LINE__, "templemaster table get failure : " + it->error(true));
                return;
            }

            i++;
            ret += ent.to_string();
        }
        _log_ok(__FUNCTION__, __LINE__, "size=" + to_string(i) + " " + ret);
        return ;
    }

    _log_error(__FUNCTION__, __LINE__,ctx->initiator() + " have no authority to list temple master .");
    return ;
}


DEFINE_METHOD(Buddha, apply_join_temple)        { self.apply_join_temple();         }
DEFINE_METHOD(Buddha, approve_join_temple)      { self.approve_join_temple();       }
DEFINE_METHOD(Buddha, recusal_join_temple)      { self.recusal_join_temple();       }
DEFINE_METHOD(Buddha, is_in_temple)             { self.is_in_temple();              }
DEFINE_METHOD(Buddha, list_temple_master)       { self.list_temple_master();        }
