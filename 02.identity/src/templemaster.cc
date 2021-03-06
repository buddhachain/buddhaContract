#include <inttypes.h>
#include "xchain/xchain.h"
#include "xchain/account.h"
#include "xchain/contract.pb.h"
#include "xchain/syscall.h"
#include "templemaster.h"
#include "main.h"

#include <iostream>
using namespace std;

xchain::json BTempleMaster::to_json() const {
    xchain::json j = {
        {"templeid", templeid()},
        {"masterid", masterid()},
        {"approved", approved()},
    };

    return j;
}

bool Main::_is_templemaster_exist(BTempleMaster& ent,
                                    const string& templeid,
                                    const string& masterid){
    if (!get_templemaster_table().find({{"templeid", templeid},{"masterid", masterid}}, &ent))
        return false;

    return true;
}

bool Main::_is_in_temple(BTempleMaster& ent,
                           const string& templeid,
                           const string& masterid){
    if (!get_templemaster_table().find({{"templeid", templeid},{"masterid", masterid}}, &ent))
        return false;

    return ent.approved();
}

bool Main::_scan_templemaster_by_templeid(xchain::json& ja, const string& templeid) {
    auto it = get_templemaster_table().scan({{"templeid", templeid}});
    while(it->next() ) {
        BTempleMaster ent;
        if (!it->get(&ent) ) {
            mycout << "templemaster table get failure : " << it->error(true) << endl;
            return false;
        }

        ja.push_back(ent.to_json());
    }

    return true;
}

bool Main::_scan_templemaster_by_masterid(xchain::json& ja, const string& masterid) {
    auto it = get_templemaster_table().scan({{"masterid", masterid}});
    while(it->next() ) {
        BTempleMaster ent;
        if (!it->get(&ent) ) {
            mycout << "templemaster table get failure : " << it->error(true) << endl;
            return false;
        }

        ja.push_back(ent.to_json());
    }

    return true;
}

bool Main::_delete_templemaster_record(const BTempleMaster& ent) {
    if( !get_templemaster_table().del(ent) ) {
        mycout << "delete templemaster " << ent.to_json().dump() << " failure ." << endl ;
        return false;
    }

    mycout << "delete templemaster " << ent.to_json().dump() << " success ." << endl ;
    return true;
}

bool Main::_delete_templemaster(const string& templeid,
                                const string& masterid) {
    BTempleMaster ent;
    if (!_is_templemaster_exist(ent, templeid, masterid)){
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

void Main::apply_join_temple(){
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

    BTempleMaster ent;

    //判断是否法师是否已经入驻此寺院
    if( _is_in_temple(ent, templeid, masterid) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, masterid + " is already join temple .");
        return;
    }

    //判断是否是否已经申请
    if( _is_templemaster_exist(ent, templeid, masterid) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, masterid + " is applying .", ent.to_json() );
        return;
    }

    ent.set_templeid(templeid);
    ent.set_masterid(masterid);
    ent.set_approved(false);
    if (!get_templemaster_table().put(ent) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "templemaster table put failure .", ent.to_json());
        return;
    }

    _log_ok(__FILE__, __FUNCTION__, __LINE__, masterid + " apply join templemaster over, please wait for approve .", ent.to_json() );
}

void Main::approve_join_temple() {
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
    BTempleMaster ent;
    if( _is_in_temple(ent, templeid, masterid) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, masterid + " is already join temple .", ent.to_json() );
        return ;
    }

    //删除此寺院法师记录
    if( !_delete_templemaster_record(ent) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "delete failure .", ent.to_json());
        return;
    }

    //授权
    ent.set_approved(true);
    if (!get_templemaster_table().put(ent) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "templemaster table put failure .", ent.to_json());
        return;
    }

    _log_ok(__FILE__, __FUNCTION__, __LINE__, "approve templemaster " + masterid + " success .", ent.to_json() );
}

void Main::recusal_join_temple() {
    const string& masterid = ctx->arg("masterid");
    if( masterid.empty() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "master id is empty .");
        return ;
    }

    const string& templeid = ctx->initiator();

    //判断寺院法师记录是否存在
    BTempleMaster ent;
    if( !_is_templemaster_exist(ent, templeid, masterid) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "temple " + templeid + ", master " + masterid + " is not exist .");
        return ;
    }

    //删除此寺院法师记录
    if( !_delete_templemaster_record(ent) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "delete failure .", ent.to_json());
        return;
    }

    _log_ok(__FILE__, __FUNCTION__, __LINE__, "delete", ent.to_json() );
}

bool Main::is_in_temple() {
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
    BTempleMaster ent;
    if (!_is_in_temple(ent, templeid, masterid) ) {
        _log_ok(__FILE__, __FUNCTION__, __LINE__, masterid + " is not join temple .") ;
        return false;
    }

    _log_ok(__FILE__, __FUNCTION__, __LINE__, masterid + " is join temple .") ;
    return true;
}

void Main::list_temple_master() {
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


DEFINE_METHOD(Main, apply_join_temple)        { self.apply_join_temple();         }
DEFINE_METHOD(Main, approve_join_temple)      { self.approve_join_temple();       }
DEFINE_METHOD(Main, recusal_join_temple)      { self.recusal_join_temple();       }
DEFINE_METHOD(Main, is_in_temple)             { self.is_in_temple();              }
DEFINE_METHOD(Main, list_temple_master)       { self.list_temple_master();        }
