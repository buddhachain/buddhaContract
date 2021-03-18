#include <inttypes.h>
#include "xchain/xchain.h"
#include "xchain/account.h"
#include "xchain/contract.pb.h"
#include "xchain/syscall.h"
#include "buddha.pb.h"
#include "buddha.h"

#include <iostream>
using namespace std;

string temple::to_string() {
    string str ;
    str += "{" ;
    str += id() + ",";
    str += unit() + ",";
    str += creditcode() + ",";
    str += address() + ",";
    str += proof() + ",";
    str += std::to_string(approved());
    str += "}";
    return str;
}

xchain::json temple::to_json() {
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

bool Buddha::_is_temple_exist(const string& id,temple& ent){
    if (!get_temple_table().find({{"id", id}}, &ent))
        return false;

    return true;
}

bool Buddha::_is_temple_exist_by_unit(const string& unit,temple& ent){
    if (!get_temple_table().find({{"unit", unit}}, &ent))
        return false;

    return true;
}

bool Buddha::_is_temple_exist_by_creditcode(const string& creditcode,temple& ent){
    if (!get_temple_table().find({{"creditcode", creditcode}}, &ent))
        return false;

    return true;
}

bool Buddha::_is_temple_exist_by_address(const string& address,temple& ent){
    if (!get_temple_table().find({{"address", address}}, &ent))
        return false;

    return true;
}

bool Buddha::_is_temple_exist_by_proof(const string& proof,temple& ent){
    if (!get_temple_table().find({{"proof", proof}}, &ent))
        return false;

    return true;
}

bool Buddha::_is_temple(const string& id) {
    temple ent;
    if (!_is_temple_exist(id, ent))
        return false;
    
    return ent.approved();
}

bool Buddha::_scan_temple(xchain::json& v, const string& cond) {
    auto it = get_temple_table().scan({{"id",cond}});
    while(it->next()) {
        temple ent;
        if (!it->get(&ent)) {
            mycout << "temple table get failure : " << it->error(true) << endl;
            return false;
        }

        v.push_back(ent.to_json());
    }

    return true;
}

bool Buddha::_delete_temple_record(const string& id) {
    temple ent;
    if (!_is_temple_exist(id, ent)){
        mycout << "temple " << id << " is not exist ." << endl ;
        return false;
    }

    if( !get_temple_table().del(ent) ) {
        mycout << "delete temple " << ent.to_string() << " failure ." << endl ;
        return false;
    }

    mycout << "delete temple " << ent.to_string() << " success ." << endl ;
    return true;
}

namespace 分界线{}

void Buddha::apply_temple(){
    const string& unit = ctx->arg("unit");
    if( unit.empty()) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "unit is empty .");
        return ;
    }
    
    const string& creditcode = ctx->arg("creditcode");
    if( creditcode.empty()) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "creditcode is empty .");
        return ;
    }
    
    const string& address = ctx->arg("address");
    if( address.empty()) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "address is empty .");
        return ;
    }
    
    const string& proof = ctx->arg("proof");
    if( proof.empty()) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "proof is empty .");
        return ;
    }

    //用户和法师可以申请成为寺院
    if( !is_user() &&
        !is_master()) {
        _log_error(__FILE__, __FUNCTION__, __LINE__,ctx->initiator() + " is not user or master, have no authority to apply  temple .");
        return ;
    }

    if( is_temple()) {
        _log_error(__FILE__, __FUNCTION__, __LINE__,ctx->initiator() + " is already temple .");
        return ;
    }

    _delete_temple_record(ctx->initiator());

    temple ent;
    ent.set_id(ctx->initiator());
    ent.set_unit(unit);
    ent.set_creditcode(creditcode);
    ent.set_address(address);
    ent.set_proof(proof);
    ent.set_approved(false);
    if (!get_temple_table().put(ent)) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "table put failure .", ent.to_json());
        return;
    }

    _log_ok(__FILE__, __FUNCTION__, __LINE__, ent.to_string() + " apply  temple over, please wait for approve .");
}

void Buddha::approve_temple() {
    const string& id = ctx->arg("id");
    if( id.empty()) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "temple id is empty .");
        return ;
    }

    if( !is_founder()) {
        _log_error(__FILE__, __FUNCTION__, __LINE__,ctx->initiator() + " is not founder, have no authority to approve temple .");
        return ;
    }

    //判断此寺院是否存在
    temple ent;
    if( !_is_temple_exist(id,ent)) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "temple " + id + " is not exist .");
        return ;
    }

    //判断是否是寺院
    if( _is_temple(id)) {
        _log_error(__FILE__, __FUNCTION__, __LINE__,ent.to_string() + " is already temple .");
        return ;
    }

    //删除此寺院
    if( !_delete_temple_record(id) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "delete failure .", ent.to_json());
        return;
    }

    ent.set_approved(true);
    if (!get_temple_table().put(ent)) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "table put failure .", ent.to_json());
        return;
    }

    _log_ok(__FILE__, __FUNCTION__, __LINE__, "approve temple " + ent.to_string() + " success .");
}

void Buddha::recusal_temple() {
    const string& id = ctx->arg("id");
    if( id.empty()) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "temple id is empty .");
        return ;
    }
    
    if( !is_founder()) {
        _log_error(__FILE__, __FUNCTION__, __LINE__,ctx->initiator() + " is not founder, have no authority to recusal temple .");
        return ;
    }

    //判断此寺院是否存在
    temple ent;
    if( !_is_temple_exist(id,ent)) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "temple " + id + " is not exist .");
        return ;
    }

    //删除此寺院
    if( !_delete_temple_record(id) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "delete failure .", ent.to_json());
        return;
    }

    _log_ok(__FILE__, __FUNCTION__, __LINE__, "recusal temple " + ent.to_string() + " success .");
}

bool Buddha::is_temple() {
    if (!_is_temple(ctx->initiator())) {
        _log_ok(__FILE__, __FUNCTION__, __LINE__, ctx->initiator() + " is not temple .") ;
        return false;
    }
    
    _log_ok(__FILE__, __FUNCTION__, __LINE__, ctx->initiator() + " is temple .") ;
    return true;
}

void Buddha::list_temple() {
    if( !is_deployer() &&
        !is_founder()) {
        _log_error(__FILE__, __FUNCTION__, __LINE__,ctx->initiator() + " is not deployer nor founder, have no authority to list temple .");
        return ;
    }

    //获取所有的寺院
    xchain::json vtemple;
    if(!_scan_temple(vtemple) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "scan temple failure .");
        return;
    }

    _log_ok(__FILE__, __FUNCTION__, __LINE__, "size=" + to_string(vtemple.size()) + " " + vtemple.dump());
}



DEFINE_METHOD(Buddha, apply_temple)             { self.apply_temple();              }
DEFINE_METHOD(Buddha, approve_temple)           { self.approve_temple();            }
DEFINE_METHOD(Buddha, recusal_temple)           { self.recusal_temple();            }
DEFINE_METHOD(Buddha, is_temple)                { self.is_temple();                 }
DEFINE_METHOD(Buddha, list_temple)              { self.list_temple();               }
