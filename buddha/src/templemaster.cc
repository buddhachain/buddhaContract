#include <inttypes.h>
#include "xchain/xchain.h"
#include "xchain/account.h"
#include "xchain/contract.pb.h"
#include "xchain/syscall.h"
#include "buddha.pb.h"
#include "buddha.h"

#include <iostream>
using namespace std;

xchain::json templemaster::to_json() {
    xchain::json j = {
        {"templeid", templeid()},
        {"masterid", masterid()},
        {"approved", approved()},
    };

    return j;
}

bool Buddha::_is_templemaster_exist(const string& templeid,
                                    const string& masterid,
                                    templemaster& ent){
    if (!get_templemaster_table().find({{"templeid", templeid},{"masterid", masterid}}, &ent))
        return false;

    return true;
}

bool Buddha::_is_in_temple(const string& templeid,
                           const string& masterid,
                           templemaster& ent){
    if (!get_templemaster_table().find({{"templeid", templeid},{"masterid", masterid}}, &ent))
        return false;

    return ent.approved();
}

bool Buddha::_scan_templemaster_by_templeid(xchain::json& ja, const string& cond) {
    auto it = get_templemaster_table().scan({{"templeid",cond}});
    while(it->next() ) {
        templemaster ent;
        if (!it->get(&ent) ) {
            mycout << "templemaster table get failure : " << it->error(true) << endl;
            return false;
        }

        ja.push_back(ent.to_json());
    }

    return true;
}

bool Buddha::_scan_templemaster_by_masterid(xchain::json& ja, const string& cond) {
    auto it = get_templemaster_table().scan({{"masterid",cond}});
    while(it->next() ) {
        templemaster ent;
        if (!it->get(&ent) ) {
            mycout << "templemaster table get failure : " << it->error(true) << endl;
            return false;
        }

        ja.push_back(ent.to_json());
    }

    return true;
}

bool Buddha::_delete_templemaster_record(const string& templeid,
                                         const string& masterid) {
    templemaster ent;
    if (!_is_templemaster_exist(templeid, masterid, ent)){
        mycout << "temple " << templeid << ", master " << masterid << " is not exist ." << endl ;
        return false;
    }

    if( !get_templemaster_table().del(ent) ) {
        mycout << "delete templemaster " << ent.to_json().dump() << " failure ." << endl ;
        return false;
    }

    mycout << "delete templemaster " << ent.to_json().dump() << " success ." << endl ;
    return true;
}

namespace 分界线{}

void Buddha::apply_join_temple(){
    const string& templeid = ctx->arg("templeid");
    if( templeid.empty() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "temple id is empty .");
        return ;
    }

    //法师申请加入寺院
    const string& masterid = ctx->initiator() ;

    //身份检查，判断是否是法师
    if( !is_master() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, masterid + " is not master, have no authority to apply join temple .");
        return ;
    }

    //身份检查，判断是否是寺院
    if( !_is_temple(templeid) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, templeid + " is not a temple .");
        return ;
    }

    templemaster ent;

    //判断是否法师是否已经入驻此寺院
    if( _is_in_temple(templeid, masterid, ent ) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, masterid + " is already join temple .");
        return;
    }

    //判断是否是否已经申请
    if( _is_templemaster_exist(templeid, masterid, ent ) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, masterid + " is applying .", ent.to_json() );
        return;
    }

    ent.set_templeid(templeid);
    ent.set_masterid(masterid);
    ent.set_approved(false);
    if (!get_templemaster_table().put(ent) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "table put failure .", ent.to_json());
        return;
    }

    _log_ok(__FILE__, __FUNCTION__, __LINE__, masterid + " apply join templemaster over, please wait for approve .", ent.to_json() );
}

void Buddha::approve_join_temple() {
    const string& masterid = ctx->arg("masterid");
    if( masterid.empty() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "master id is empty .");
        return ;
    }

    //判断是否是法师
    if( !_is_master(masterid) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, masterid + " is not a master .");
        return ;
    }

    const string& templeid = ctx->initiator();

    //判断是否法师是否已经入驻此寺院
    templemaster ent;
    if( _is_in_temple(templeid, masterid,ent) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, masterid + " is already join temple .", ent.to_json() );
        return ;
    }

    //删除此寺院法师记录
    if( !_delete_templemaster_record(templeid, masterid) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "delete failure .", ent.to_json());
        return;
    }

    //授权
    ent.set_approved(true);
    if (!get_templemaster_table().put(ent) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "table put failure .", ent.to_json());
        return;
    }

    _log_ok(__FILE__, __FUNCTION__, __LINE__, "approve templemaster " + masterid + " success .", ent.to_json() );
}

void Buddha::recusal_join_temple() {
    const string& masterid = ctx->arg("masterid");
    if( masterid.empty() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "master id is empty .");
        return ;
    }

    const string& templeid = ctx->initiator();

    //判断寺院法师记录是否存在
    templemaster ent;
    if( !_is_templemaster_exist(templeid, masterid,ent) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "temple " + templeid + ", master " + masterid + " is not exist .");
        return ;
    }

    //删除此寺院法师记录
    if( !_delete_templemaster_record(templeid, masterid) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "delete failure .", ent.to_json());
        return;
    }

    _log_ok(__FILE__, __FUNCTION__, __LINE__, "recusal templemaster " + masterid + " success .", ent.to_json() );
}

bool Buddha::is_in_temple() {
    const string& templeid = ctx->arg("templeid");
    if( templeid.empty() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "temple id is empty .");
        return false;
    }

    const string& masterid = ctx->initiator();

    //判断是否是法师
    if( !_is_master(masterid) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, masterid + " is not a master, have no authority to query in some temple .");
        return false;
    }

    //判断是否是寺院
    if( !_is_temple(templeid) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__,templeid + " is not a temple .");
        return false;
    }

    //判断是否法师是否已经入驻此寺院
    templemaster ent;
    if (!_is_in_temple(templeid, masterid, ent) ) {
        _log_ok(__FILE__, __FUNCTION__, __LINE__, masterid + " is not join temple .") ;
        return false;
    }

    _log_ok(__FILE__, __FUNCTION__, __LINE__, masterid + " is join temple .") ;
    return true;
}

void Buddha::list_temple_master() {
    const string& templeid = ctx->arg("templeid");

    //身份检查，部署者和基金会成员可以查看所有当前寺院的所有法师
    if( is_deployer() ||
        is_founder() ) {
        xchain::json ja ;
        if(!_scan_templemaster_by_templeid(ja,templeid) ) {
            _log_error(__FILE__, __FUNCTION__, __LINE__, "scan table failure .");
            return;
        }

        _log_ok(__FILE__, __FUNCTION__, __LINE__, "scan", ja);
        return ;
    }

    //身份检查，寺院可以查看自己寺院的所有法师
    if( is_temple() ) {
        xchain::json ja ;
        if(!_scan_templemaster_by_templeid(ja,ctx->initiator()) ) {
            _log_error(__FILE__, __FUNCTION__, __LINE__, "scan table failure .");
            return;
        }
        
        _log_ok(__FILE__, __FUNCTION__, __LINE__, "scan", ja);
        return ;
    }

    _log_error(__FILE__, __FUNCTION__, __LINE__,ctx->initiator() + " have no authority to list temple master .");
    return ;
}


DEFINE_METHOD(Buddha, apply_join_temple)        { self.apply_join_temple();         }
DEFINE_METHOD(Buddha, approve_join_temple)      { self.approve_join_temple();       }
DEFINE_METHOD(Buddha, recusal_join_temple)      { self.recusal_join_temple();       }
DEFINE_METHOD(Buddha, is_in_temple)             { self.is_in_temple();              }
DEFINE_METHOD(Buddha, list_temple_master)       { self.list_temple_master();        }
