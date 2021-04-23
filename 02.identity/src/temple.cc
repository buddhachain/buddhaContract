#include <inttypes.h>
#include "xchain/xchain.h"
#include "xchain/account.h"
#include "xchain/contract.pb.h"
#include "xchain/syscall.h"
#include "buddha.pb.h"
#include "buddha.h"

#include <iostream>
using namespace std;

xchain::json BTemple::to_json() {
    xchain::json j = {
        {"id", id()},
        {"unit", unit()},
        {"creditcode", creditcode()},
        {"address", address()},
        {"proof", proof()},
        {"approved", approved()},
    };

    return j;
}

bool Main::_is_temple_exist(temple& ent, const string& id){
    if (!get_temple_table().find({{"id", id}}, &ent))
        return false;

    return true;
}

bool Main::_is_temple_exist_by_unit(temple& ent, const string& unit){
    if (!get_temple_table().find({{"unit", unit}}, &ent))
        return false;

    return true;
}

bool Main::_is_temple_exist_by_creditcode(temple& ent, const string& creditcode){
    if (!get_temple_table().find({{"creditcode", creditcode}}, &ent))
        return false;

    return true;
}

bool Main::_is_temple_exist_by_address(temple& ent, const string& address){
    if (!get_temple_table().find({{"address", address}}, &ent))
        return false;

    return true;
}

bool Main::_is_temple_exist_by_proof(temple& ent, const string& proof){
    if (!get_temple_table().find({{"proof", proof}}, &ent))
        return false;

    return true;
}

bool Main::_is_temple(const string& id) {
    temple ent;
    if (!_is_temple_exist(ent, id))
        return false;
    
    return ent.approved();
}

bool Main::_scan_temple(xchain::json& ja, const string& cond) {
    auto it = get_temple_table().scan({{"id",cond}});
    while(it->next() ) {
        temple ent;
        if (!it->get(&ent) ) {
            mycout << "temple table get failure : " << it->error(true) << endl;
            return false;
        }

        ja.push_back(ent.to_json());
    }

    return true;
}

bool Main::_delete_temple_record(const string& id) {
    temple ent;
    if (!_is_temple_exist(ent, id)){
        mycout << "temple " << id << " is not exist ." << endl ;
        return false;
    }

    if( !get_temple_table().del(ent) ) {
        mycout << "delete temple " << ent.to_json().dump() << " failure ." << endl ;
        return false;
    }

    mycout << "delete temple " << ent.to_json().dump() << " success ." << endl ;
    return true;
}

namespace 分界线{}

void Main::apply_temple(){
    const string& unit = ctx->arg("unit");
    if( unit.empty() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "unit is empty .");
        return ;
    }
    
    const string& creditcode = ctx->arg("creditcode");
    if( creditcode.empty() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "creditcode is empty .");
        return ;
    }
    
    const string& address = ctx->arg("address");
    if( address.empty() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "address is empty .");
        return ;
    }
    
    const string& proof = ctx->arg("proof");
    if( proof.empty() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "proof is empty .");
        return ;
    }

    //身份检查，用户和法师可以申请成为寺院
    if( !is_user() &&
        !is_master() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__,ctx->initiator() + " is not user or master, have no authority to apply  temple .");
        return ;
    }

    //判断是否已经是寺院
    if( is_temple() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__,ctx->initiator() + " is already temple .");
        return ;
    }

    //判断此寺院是否存在
    temple ent;
    if( _is_temple_exist(ent, ctx->initiator()) ) {
        _log_ok(__FILE__, __FUNCTION__, __LINE__, "temple " + ctx->initiator() + " is applying .", ent.to_json() );
        return ;
    }

    ent.set_id(ctx->initiator());
    ent.set_unit(unit);
    ent.set_creditcode(creditcode);
    ent.set_address(address);
    ent.set_proof(proof);
    ent.set_approved(false);
    if (!get_temple_table().put(ent) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "table put failure .", ent.to_json());
        return;
    }

    _log_ok(__FILE__, __FUNCTION__, __LINE__, ctx->initiator() + " apply temple over, please wait for approve .", ent.to_json() );
}

void Main::approve_temple() {
    const string& id = ctx->arg("id");
    if( id.empty() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "temple id is empty .");
        return ;
    }

    //判断是否是基金会成员
    if( !is_founder() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__,ctx->initiator() + " is not founder, have no authority to approve temple .");
        return ;
    }

    //判断此寺院是否存在
    temple ent;
    if( !_is_temple_exist(ent, id) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "temple " + id + " is not exist .");
        return ;
    }

    //判断是否是寺院
    if( _is_temple(id) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, id + " is already temple .", ent.to_json() );
        return ;
    }

    //删除此寺院
    if( !_delete_temple_record(id) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "delete failure .", ent.to_json());
        return;
    }

    //授权
    ent.set_approved(true);
    if (!get_temple_table().put(ent) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "table put failure .", ent.to_json());
        return;
    }

    _log_ok(__FILE__, __FUNCTION__, __LINE__, "approve temple " + id + " success .", ent.to_json() );
}

void Main::recusal_temple() {
    const string& id = ctx->arg("id");
    if( id.empty() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "temple id is empty .");
        return ;
    }

    //判断是否是基金会成员
    if( !is_founder() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__,ctx->initiator() + " is not founder, have no authority to recusal temple .");
        return ;
    }

    //判断此寺院是否存在
    temple ent;
    if( !_is_temple_exist(ent, id) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "temple " + id + " is not exist .");
        return ;
    }

    //删除此寺院
    if( !_delete_temple_record(id) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "delete failure .", ent.to_json());
        return;
    }

    _log_ok(__FILE__, __FUNCTION__, __LINE__, "delete", ent.to_json() );
}

bool Main::is_temple() {
    if (!_is_temple(ctx->initiator()) ) {
        _log_ok(__FILE__, __FUNCTION__, __LINE__, ctx->initiator() + " is not temple .") ;
        return false;
    }
    
    _log_ok(__FILE__, __FUNCTION__, __LINE__, ctx->initiator() + " is temple .") ;
    return true;
}

void Main::list_temple() {
    //身份检查，部署者和基金会成员具有权限
    if( !is_deployer() &&
        !is_founder() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__,ctx->initiator() + " is not deployer nor founder, have no authority to list temple .");
        return ;
    }

    //获取所有的寺院
    xchain::json ja;
    if(!_scan_temple(ja) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "scan temple failure .");
        return;
    }

    _log_ok(__FILE__, __FUNCTION__, __LINE__, "scan", ja);
}



DEFINE_METHOD(Buddha, apply_temple)             { self.apply_temple();              }
DEFINE_METHOD(Buddha, approve_temple)           { self.approve_temple();            }
DEFINE_METHOD(Buddha, recusal_temple)           { self.recusal_temple();            }
DEFINE_METHOD(Buddha, is_temple)                { self.is_temple();                 }
DEFINE_METHOD(Buddha, list_temple)              { self.list_temple();               }
