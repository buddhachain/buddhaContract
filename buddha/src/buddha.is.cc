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

bool Buddha::_is_founder_exist(const string& id,founder& ent) {
    if (!get_founder_table().find({{"id", id}}, &ent))
        return false;

    return true;
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

bool Buddha::_is_master_exist(const string& id,master& ent){
    if (!get_master_table().find({{"id", id}}, &ent))
        return false;

    return true;
}

bool Buddha::_is_master_exist_by_proof(const string& proof,master& ent){
    if (!get_master_table().find({{"proof", proof}}, &ent))
        return false;

    return true;
}

bool Buddha::_is_templemaster_exist(const string& templeid,
                                    const string& masterid,
                                    templemaster& ent){
    if (!get_templemaster_table().find({{"templeid", templeid},{"masterid", masterid}}, &ent))
        return false;

    return true;
}

bool Buddha::_is_kinddeedtype_exist(const string& id,kinddeedtype& ent) {
    if (!get_kinddeedtype_table().find({{"id", id}}, &ent))
        return false;

    return true;
}

bool Buddha::_is_kinddeed_exist(const string& id,kinddeed& ent) {
    if (!get_kinddeed_table().find({{"id", id}}, &ent))
        return false;

    return true;
}

bool Buddha::_is_kinddeeddetail_exist(const string& kdid,
                                       const string& seq,
                                       kinddeeddetail& ent) {
    if (!get_kinddeeddetail_table().find({{"kdid", kdid},{"sequence",seq}}, &ent))
        return false;

    return true;
}


bool Buddha::_is_kinddeeddetail_exist_by_kdid(const string& kdid,vector<kinddeeddetail>& vent) {
    auto it = get_kinddeeddetail_table().scan({{"kdid",kdid}});
    while(it->next()) {
        kinddeeddetail ent;
        if (!it->get(&ent)) {
            if(it->error(true) == "success") 
                return false;
            mycout << "kinddeeddetail table get failure : " << it->error(true) << endl;
            return false;
        }
        vent.push_back(ent);
    }

    if( vent.size()==0)
        return false;

    return true;
}

bool Buddha::_is_kinddeedspec_exist(const string& kdid,
                                       const string& seq,
                                       kinddeedspec& ent) {
    if (!get_kinddeedspec_table().find({{"kdid", kdid},{"sequence",seq}}, &ent))
        return false;

    return true;
}

bool Buddha::_is_kinddeedspec_exist_by_kdid(const string& kdid,vector<kinddeedspec>& vent) {
    auto it = get_kinddeedspec_table().scan({{"kdid",kdid}});
    while(it->next()) {
        kinddeedspec ent;
        if (!it->get(&ent)) {
            if(it->error(true) == "success") 
                return false;
            mycout << "kinddeedspec table get failure : " << it->error(true) << endl;
            return false;
        }

        vent.push_back(ent);
    }

    if( vent.size()==0)
        return false;

    return true;
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
        if( !_is_commentlabel_exist(id,ent)) {
            mycout << "type " << id << " not exist in commentlabel table ." << endl;
            return false;
        }            
    }

    return true;
}

bool Buddha::_is_beforecomment_exist(const string& kdid, const string& owner,beforecomment& ent) {
    if (!get_beforecomment_table().find({{"kdid", kdid},{"owner", owner}}, &ent))
        return false;

    return true;
}

bool Buddha::_is_order_exist(const string& id,order& ent) {
    if (!get_order_table().find({{"id", id}}, &ent))
        return false;

    return true;
}

bool Buddha::_is_kinddeedproof_exist(const string& orderid,kinddeedproof& ent) {
    if (!get_kinddeedproof_table().find({{"orderid", orderid}}, &ent))
        return false;

    return true;
}

bool Buddha::_is_aftercomment_exist(const string& orderid, const string& owner, aftercomment& ent) {
    if (!get_aftercomment_table().find({{"orderid", orderid}, {"owner", owner}}, &ent))
        return false;

    return true;
}

bool Buddha::_is_kinddeed_online(const string& id){
    kinddeed ent;
    if (!get_kinddeed_table().find({{"id", id}}, &ent)) {
        mycout << "kinddeed " << id << " is not exist ." << endl;
        return false;
    }

    if( ent.applied() == true) {
        mycout << "kinddeed " << id << " is apply status change ." << endl;
        return false;
    }

    if( ent.online() != true ) {
        mycout << "kinddeed " << id << " is not online ." << endl;
        return false;
    }

    return true;

}



bool Buddha::_is_deployer(const string& id) {
    string deployer;
    if (!ctx->get_object("deployer", &deployer)) 
        return false;

    if (deployer != id )
        return false;

    return true ;
}

bool Buddha::_is_founder(const string& id) {
    founder ent;
    if (!_is_founder_exist(id, ent))
        return false;
    
    return ent.approved();
}

bool Buddha::_is_temple(const string& id) {
    temple ent;
    if (!_is_temple_exist(id, ent))
        return false;
    
    return ent.approved();
}

bool Buddha::_is_master(const string& id) {
    master ent;
    if (!_is_master_exist(id, ent))
        return false;

    return ent.approved();
}

bool Buddha::_is_in_temple(const string& templeid,
                           const string& masterid,
                           templemaster& ent){
    if (!get_templemaster_table().find({{"templeid", templeid},{"masterid", masterid}}, &ent))
        return false;

    return ent.approved();
}


bool Buddha::_is_user(const string& id) {
    if( _is_deployer(id)) 
        return false;

    if( _is_founder(id)) 
        return false;

    if( _is_temple(id)) 
        return false;

    if( _is_master(id)) 
        return false;

    return true ;
}

