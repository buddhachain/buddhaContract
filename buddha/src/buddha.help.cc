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

bool Buddha::_is_proposal_exist(const string& key,proposal& ent) {
    if (!get_proposal_table().find({{"key", key}}, &ent))
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

bool Buddha::_scan_founder(xchain::json& v, const string& cond) {
    auto it = get_founder_table().scan({{"id",cond}});
    while(it->next()) {
        founder ent;
        if (!it->get(&ent)) {
            mycout << "founder table get failure : " << it->error(true) << endl;
            return false;
        }

        v.push_back(ent.to_json());
    }

    return true;
}

bool Buddha::_scan_proposal(xchain::json& v, const string& cond) {
    auto it = get_proposal_table().scan({{"key",cond}});
    while(it->next()) {
        proposal ent;
        if (!it->get(&ent)) {
            mycout << "proposal table get failure : " << it->error(true) << endl;
            return false;
        }

        v.push_back(ent.to_json());
    }

    return true;
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

bool Buddha::_delete_founder_record(const string& id) {
    founder ent;
    if (!_is_founder_exist(id, ent)){
        mycout << "founder " << id << " is not exist ." << endl ;
        return false;
    }

    if( !get_founder_table().del(ent) ) {
        mycout << "delete founder " << ent.to_string() << " failure ." << endl ;
        return false;
    }

    mycout << "delete founder " << ent.to_string() << " success ." << endl ;
    return true;
}


bool Buddha::_delete_proposal_record(const string& key) {
    proposal ent;
    if (!_is_proposal_exist(key, ent)){
        mycout << "proposal " << key << " is not exist ." << endl ;
        return false;
    }

    if( !get_proposal_table().del(ent) ) {
        mycout << "delete proposal " << ent.to_string() << " failure ." << endl ;
        return false;
    }

    mycout << "delete proposal " << ent.to_string() << " success ." << endl ;
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

bool Buddha::_delete_master_record(const string& id) {
    master ent;
    if (!_is_master_exist(id, ent)){
        mycout << "master " << id << " is not exist ." << endl ;
        return false;
    }

    if( !get_master_table().del(ent) ) {
        mycout << "delete master " << ent.to_string() << " failure ." << endl ;
        return false;
    }

    mycout << "delete master " << ent.to_string() << " success ." << endl ;
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
        mycout << "delete templemaster " << ent.to_string() << " failure ." << endl ;
        return false;
    }

    mycout << "delete templemaster " << ent.to_string() << " success ." << endl ;
    return true;
}

bool Buddha::_delete_kinddeedtype_record(const string& id) {
    kinddeedtype ent;
    if (!_is_kinddeedtype_exist(id, ent)){
        mycout << "kinddeedtype " << id << " is not exist ." << endl ;
        return false;
    }

    if( !get_kinddeedtype_table().del(ent) ) {
        mycout << "delete kinddeedtype " << ent.to_string() << " failure ." << endl ;
        return false;
    }

    mycout << "delete kinddeedtype " << ent.to_string() << " success ." << endl ;
    return true;
}


bool Buddha::_delete_kinddeed_record(const string& id) {
    kinddeed ent;
    if (!_is_kinddeed_exist(id, ent)){
        mycout << "kinddeed " << id << " is not exist ." << endl ;
        return false;
    }

    if( !get_kinddeed_table().del(ent) ) {
        mycout << "delete kinddeed " << ent.to_string() << " failure ." << endl ;
        return false;
    }

    //删除此善举的所有描述记录
    if( !_delete_kinddeeddetail_records(id) ) {
        mycout << "delete kinddeeddetail " << id << " failure ." << endl ;
        return false;
    }

    //删除此善举的所有规格记录
    if( !_delete_kinddeedspec_records(id) ) {
        mycout << "delete kinddeedspec " << id << " failure ." << endl ;
        return false;
    }

    mycout << "delete kinddeed " << ent.to_string() << " success ." << endl ;
    return true;
}

bool Buddha::_delete_kinddeeddetail_records(const string& id) {

    while(true) {
        kinddeeddetail ent;
        if (!get_kinddeeddetail_table().find({{"kdid", id}}, &ent))
            break;

        if( !get_kinddeeddetail_table().del(ent) ) {
            mycout << "delete kinddeeddetail " << ent.to_string() << " failure ." << endl ;
            return false;
        }
    }

    mycout << "delete kinddeeddetails success ." << endl ;
    return true;
}

bool Buddha::_delete_kinddeeddetail_record(const string& id, const string& sequence ) {
    kinddeeddetail ent;
    if (!get_kinddeeddetail_table().find({{"kdid", id},{"sequence",sequence}}, &ent)) {
        mycout << "not found kinddeeddetail " << id << "," << sequence << " failure ." << endl ;
        return false;
    }

    if( !get_kinddeeddetail_table().del(ent) ) {
        mycout << "delete kinddeeddetail " << ent.to_string() << " failure ." << endl ;
        return false;
    }

    mycout << "delete kinddeeddetail success ." << endl ;
    return true;
}

bool Buddha::_delete_kinddeedspec_records(const string& id) {
    while(true) {
        kinddeedspec ent;
        if (!get_kinddeedspec_table().find({{"kdid", id}}, &ent))
            break;

        if( !get_kinddeedspec_table().del(ent) ) {
            mycout << "delete kinddeedspec " << ent.to_string() << " failure ." << endl ;
            return false;
        }
    }

    mycout << "delete kinddeedspecs success ." << endl ;
    return true;
}

bool Buddha::_delete_kinddeedspec_record(const string& id, const string& sequence ) {
    kinddeedspec ent;
    if (!get_kinddeedspec_table().find({{"kdid", id},{"sequence",sequence}}, &ent)) {
        mycout << "not found kinddeedspec " << id << "," << sequence << " failure ." << endl ;
        return false;
    }

    if( !get_kinddeedspec_table().del(ent) ) {
        mycout << "delete kinddeedspec " << ent.to_string() << " failure ." << endl ;
        return false;
    }

    mycout << "delete kinddeedspec success ." << endl ;
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

bool Buddha::_delete_beforecomment_record(const string& kdid, const string& owner) {
    beforecomment ent;
    if (!_is_beforecomment_exist(kdid, owner, ent)){
        mycout << "beforecomment  " << owner << "," << kdid << " is not exist ." << endl ;
        return false;
    }

    if( !get_beforecomment_table().del(ent) ) {
        mycout << "delete beforecomment " << ent.to_string() << " failure ." << endl ;
        return false;
    }

    mycout << "delete beforecomment " << ent.to_string() << " success ." << endl ;
    return true;
}


bool Buddha::_delete_order_record(const string& id) {
    //判断订单是否存在
    order ent;
    if( !_is_order_exist(id, ent)){
        mycout << "order " << id << " is not exist ." << endl ;
        return false;
    }

    if( !get_order_table().del(ent)) {
        mycout << "delete order " << ent.to_string() << " failure ." << endl ;
        return false;
    }

    mycout << "delete order " << ent.to_string() << " success ." << endl ;
    return true;
}

bool Buddha::_delete_kinddeedproof_record(const string& orderid) {
    kinddeedproof ent;
    if (!_is_kinddeedproof_exist(orderid, ent)){
        mycout << "kinddeedproof " << orderid << " is not exist ." << endl ;
        return false;
    }

    if( !get_kinddeedproof_table().del(ent) ) {
        mycout << "delete kinddeedproof " << ent.to_string() << " failure ." << endl ;
        return false;
    }

    mycout << "delete kinddeedproof " << ent.to_string() << " success ." << endl ;
    return true;
}

bool Buddha::_delete_aftercomment_record(const string& orderid, const string& owner) {
    aftercomment ent;
    if (!_is_aftercomment_exist(orderid,owner,ent)){
        mycout << "aftercomment " << orderid << " is not exist ." << endl ;
        return false;
    }

    if( !get_aftercomment_table().del(ent) ) {
        mycout << "delete aftercomment " << ent.to_string() << " failure ." << endl ;
        return false;
    }

    mycout << "delete aftercomment " << ent.to_string() << " success ." << endl ;
    return true;
}

bool Buddha::_add_kinddeeddetail(const string& kdid,
                                 const string& sequence,
                                 const string& hash) {

    if( kdid.empty()) {
        mycout << "kdid is empty ." << endl;
        return false;
    }

    if( sequence.empty()) {
        mycout << "sequence is empty ." << endl;
        return false;
    }

    if( hash.empty()) {
        mycout << "hash is empty ." << endl;
        return false;
    }

    //删除在此善举已经存在的描述
    kinddeeddetail ent;
    if(_is_kinddeeddetail_exist(kdid, sequence, ent))
        if(!_delete_kinddeeddetail_record(kdid, sequence)) 
            return false;

    ent.set_kdid(kdid);
    ent.set_sequence(stoll(sequence));
    ent.set_hash(hash);

    mycout << ent.to_string() << endl;

    if (!get_kinddeeddetail_table().put(ent)) {
        mycout << "kinddeeddetail table put " << ent.to_string() << " failure ." << endl;
        return false;
    }

    return true ;
}

bool Buddha::_add_kinddeedspec(const string& kdid,
                               const string& sequence,
                               const string& desc,
                               const string& price) {

    if( kdid.empty()) {
        mycout << "kdid is empty ." << endl;
        return false;
    }

    if( sequence.empty()) {
        mycout << "sequence is empty ." << endl;
        return false;
    }

    if( desc.empty()) {
        mycout << "desc is empty ." << endl;
        return false;
    }

    if( price.empty()) {
        mycout << "price is empty ." << endl;
        return false;
    }

    //删除在此善举已经存在的规格
    kinddeedspec ent;
    if(_is_kinddeedspec_exist(kdid, sequence, ent))
        if(!_delete_kinddeedspec_record(kdid, sequence)) 
            return false;

    ent.set_kdid(kdid);
    ent.set_sequence(stoll(sequence));
    ent.set_desc(desc);
    ent.set_price(stoll(price));

    mycout << ent.to_string() << endl;

    if (!get_kinddeedspec_table().put(ent)) {
        mycout << "kinddeedspec table put " << ent.to_string() << " failure ." << endl;
        return false;
    }

    return true ;
}


bool Buddha::_transfer(const string& toid,
                    const string& toamount){
    //将抵押退还
    xchain::Account account = xchain::Account(toid);
    if( !account.transfer(toamount)) 
        return false;

    return true ;
}
