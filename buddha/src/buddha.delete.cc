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

    if( !_delete_kinddeeddetail_records(id) ) {
        mycout << "delete kinddeeddetail " << id << " failure ." << endl ;
        return false;
    }

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
        _log_error(__FUNCTION__, __LINE__,"kdid is empty .");
        return false;
    }

    if( sequence.empty()) {
        _log_error(__FUNCTION__, __LINE__,"sequence is empty .");
        return false;
    }

    if( hash.empty()) {
        _log_error(__FUNCTION__, __LINE__,"hash is empty .");
        return false;
    }

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
        _log_error(__FUNCTION__, __LINE__,"kdid is empty .");
        return false;
    }

    if( sequence.empty()) {
        _log_error(__FUNCTION__, __LINE__,"sequence is empty .");
        return false;
    }

    if( desc.empty()) {
        _log_error(__FUNCTION__, __LINE__,"desc is empty .");
        return false;
    }

    if( price.empty()) {
        _log_error(__FUNCTION__, __LINE__,"price is empty .");
        return false;
    }

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
