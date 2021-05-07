#include <inttypes.h>
#include "xchain/xchain.h"
#include "xchain/account.h"
#include "xchain/contract.pb.h"
#include "xchain/syscall.h"
#include "buddha.pb.h"
#include "buddha.h"

#include <iostream>
using namespace std;

// 订单所有者的比例分成随前二者变动而变动 
// ratio_for_kinddeed_owner = 100 - ratio_for_burn - ratio_for_some_contract;
static int64_t ratio_for_burn           = 10 ; //默认给0账户的燃烧值比是10%
static int64_t ratio_for_some_contract  = 10 ; //默认给某合约账户的比例是10%
// static int64_t ratio_for_kinddeed_owner = 80 ; //默认给订单所有者账户的比例是80%
static string some_contract             = "buddha"; //某个默认的收款合约账户


xchain::json BKinddeedProof::to_json() const {
    xchain::json j = {
        {"orderid", orderid()},
        {"owner", owner()},
        {"proof", proof()},
        {"timestamp", timestamp()},
        {"approved", approved()},
    };

    return j;
}

bool Main::_is_kinddeedproof_exist(kinddeedproof& ent, const string& orderid) {
    if (!get_kinddeedproof_table().find({{"orderid", orderid}}, &ent))
        return false;

    return true;
}

bool Main::_scan_kinddeedproof_by_orderid(xchain::json& ja, const string& cond) {
    auto it = get_kinddeedproof_table().scan({{"orderid",cond}});
    while(it->next() ) {
        kinddeedproof ent;
        if (!it->get(&ent) ) {
            mycout << "kinddeedproof table get failure : " << it->error(true) << endl;
            return false;
        }

        ja.push_back(ent.to_json());
    }

    return true;
}

bool Main::_scan_kinddeedproof_by_owner(xchain::json& ja, const string& cond) {
    auto it = get_kinddeedproof_table().scan({{"owner",cond}});
    while(it->next() ) {
        kinddeedproof ent;
        if (!it->get(&ent) ) {
            mycout << "kinddeedproof table get failure : " << it->error(true) << endl;
            return false;
        }

        ja.push_back(ent.to_json());
    }

    return true;
}

bool Main::_scan_kinddeedproof_by_owner_orderid(xchain::json& ja, const string& owner, const string& orderid) {
    auto it = get_kinddeedproof_table().scan({{"owner",owner},{"orderid",orderid}});
    while(it->next() ) {
        kinddeedproof ent;
        if (!it->get(&ent) ) {
            mycout << "kinddeedproof table get failure : " << it->error(true) << endl;
            return false;
        }

        ja.push_back(ent.to_json());
    }

    return true;
}

bool Main::_delete_kinddeedproof_record(const string& orderid) {
    kinddeedproof ent;
    if (!_is_kinddeedproof_exist(ent, orderid)){
        mycout << "kinddeedproof " << orderid << " is not exist ." << endl ;
        return false;
    }

    if( !get_kinddeedproof_table().del(ent) ) {
        mycout << "delete kinddeedproof " << ent.to_json().dump() << " failure ." << endl ;
        return false;
    }

    mycout << "delete kinddeedproof " << ent.to_json().dump() << " success ." << endl ;
    return true;
}

namespace 分界线{}

void Main::upload_kinddeedproof() {
    const string& orderid = ctx->arg("orderid");
    if( orderid.empty() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "kinddeedproof orderid is empty .");
        return ;
    }

    const string& proof = ctx->arg("proof");
    if( proof.empty() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "kinddeedproof hash is empty .");
        return ;
    }

    const string& timestamp = ctx->arg("timestamp");
    if( timestamp.empty() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "kinddeedproof timestamp is empty .");
        return ;
    }

    //判断善举凭证是否已经存在
    kinddeedproof ent;
    if (_is_kinddeedproof_exist(ent, orderid))  {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "kinddeedproof " + orderid + " is exist .", ent.to_json() );
        return ;
    }

    //判断订单是否存在
    order od;
    if (!_is_order_exist(od, orderid) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "order and suborder lost, kinddeedproof " + orderid + " be delete .");
        return ;
    }
    
    if( od.kdowner() != ctx->initiator() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__,ctx->initiator() + " is not the right kinddeed owner, it should be " + od.kdowner());
        return ;
    }

    ent.set_orderid(orderid);
    ent.set_owner(ctx->initiator());
    ent.set_proof(proof);
    ent.set_timestamp(timestamp);
    ent.set_approved(false);
    if (!get_kinddeedproof_table().put(ent) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "kinddeedproof table put " + orderid + " failure .", ent.to_json() );
        return;
    }

    _log_ok(__FILE__, __FUNCTION__, __LINE__, "apply kinddeed " + orderid + " proof over, please wait for approve .", ent.to_json());
}

void Main::approve_kinddeedproof() {
    const string& orderid = ctx->arg("orderid");
    if( orderid.empty() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "kinddeedproof orderid is empty .");
        return ;
    }

    //判断是否是基金会成员
    if( !is_founder() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__,ctx->initiator() + " is not founder, have no authority to approve kinddeedproof .");
        return ;
    }

    //判断善举凭证是否已经存在
    kinddeedproof ent;
    if (!_is_kinddeedproof_exist(ent, orderid))  {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "kinddeedproof " + orderid + " is not exist .");
        return ;
    }

    //判断订单是否存在
    order od;
    if (!_is_order_exist(od, orderid) ) {
        //删除此善举凭证
        _delete_kinddeedproof_record(orderid);
        _log_error(__FILE__, __FUNCTION__, __LINE__, "order and suborder lost, kinddeedproof " + orderid + " be delete .");
        return ;
    }

    if (ent.approved())  {
        _log_ok(__FILE__, __FUNCTION__, __LINE__, "kinddeedproof " + orderid + " has approved yet .");
        return ;
    }

    //判断善举是否存在
    kinddeed kd;
    if( !_is_kinddeed_exist(kd, od.kdid()) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "kinddeed " + od.kdid() + " is not exist .");
        return ;
    }

    if( ent.owner() != od.kdowner() &&
        ent.owner() != kd.owner() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, ent.owner() +","+ od.kdowner() + "," + kd.owner() + " failure .");
        return ;
    }

    //计算分成

    {//判断是否已经存在这个ratio_for_burn这个提案
        proposal pps;
        if(_is_proposal_exist(pps, "ratio_for_burn") ) {
            mycout << "proposal ratio_for_burn=" << pps.value() << endl ;
            ratio_for_burn = stoll(pps.value());
        } else
            mycout << "proposal ratio_for_burn is not exist ." << endl ;
    }

    {//判断是否已经存在这个ratio_for_some_contract这个提案
        proposal pps;
        if(_is_proposal_exist(pps, "ratio_for_some_contract") ) {
            mycout << "proposal ratio_for_some_contract=" << pps.value() << endl ;
            ratio_for_some_contract = stoll(pps.value());
        } else
            mycout << "proposal ratio_for_some_contract is not exist ." << endl ;
    }

    {//判断是否已经存在这个some_contract这个提案
        proposal pps;
        if(_is_proposal_exist(pps, "some_contract") ) {
            mycout << "proposal some_contract=" << pps.value() << endl ;
            some_contract = pps.value();
        } else
            mycout << "proposal some_contract is not exist ." << endl ;
    }

    //如果分成给0账户和某合约账户的总分成超过100，说明数值存在错误。
    if( ratio_for_burn + ratio_for_some_contract > 100 ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__,
            "ratio error : ratio_for_burn=" + to_string(ratio_for_burn) + ", ratio_for_some_contract=" + to_string(ratio_for_some_contract),
            ent.to_json());
        return;
    }

    //删除此善举凭证
    if( !_delete_kinddeedproof_record(orderid) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "delete failure .", ent.to_json());
        return;
    }

    //授权
    ent.set_approved(true);
    if (!get_kinddeedproof_table().put(ent) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "kinddeedproof table put " + orderid + " failure .", ent.to_json());
        return;
    }

    //执行分成

    //转账给0账户
    int64_t amount_for_burn = (int64_t)(ratio_for_burn*od.amount()/100);
    if( !_transfer("000000000000000000000000000000000", to_string(amount_for_burn)) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "transfer to 0 account " +  to_string(amount_for_burn) + " failure .");
        return ;
    }

    //转账给some_contract,无需判断此账户是否存在
    int64_t amount_for_some_contract = (int64_t)(ratio_for_some_contract*od.amount()/100);
    if ( some_contract != "buddha" ) {
        if( !_transfer(some_contract, to_string(amount_for_some_contract)) ) {
            _log_error(__FILE__, __FUNCTION__, __LINE__, "transfer to some account " +  to_string(amount_for_some_contract) + " failure .");
            return ;
        }
    }

    //转账给订单所有者
    int64_t amount_for_kinddeed_owner = od.amount()-amount_for_burn - amount_for_some_contract;
    if( !_transfer(ent.owner(), to_string(amount_for_kinddeed_owner)) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "transfer to " + ent.owner() + " " +  to_string(amount_for_kinddeed_owner) + " failure .");
        return ;
    }

    //记录善举所有者的信用值
    int64_t credit_total_value ;
    if ( !_add_credit(ent.owner(), od.amount(), credit_total_value) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, od.owner() + " add credit " + to_string(od.amount()) + " failure .");
        return ;
    }
    //添加到信用值排名表
    if ( !_add_creditranking(ent.owner(), credit_total_value) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, od.owner() + " add creditranking value " + to_string(credit_total_value) + " failure .");
        return ;
    }

    //记录用户的功德值
    int64_t merit_total_value ;
    if ( !_add_merit(od.owner(), od.amount(), merit_total_value) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, od.owner() + " add merit " + to_string(od.amount()) + " failure .");
        return ;
    }
    //排序用户的功德值排名
    if ( !_add_meritranking(od.owner(), merit_total_value) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, od.owner() + " add meritranking value " + to_string(merit_total_value) + " failure .");
        return ;
    }

    _log_ok(__FILE__, __FUNCTION__, __LINE__, "approve kinddeed " + orderid + " proof success .", ent.to_json());
}

void Main::refuse_kinddeedproof() {
    const string& orderid = ctx->arg("orderid");
    if( orderid.empty() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "kinddeedproof orderid is empty .");
        return ;
    }

    //判断是否是基金会成员
    if( !is_founder() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__,ctx->initiator() + " is not founder, have no authority to approve kinddeedproof .");
        return ;
    }

    //判断善举凭证是否已经存在
    kinddeedproof ent;
    if (!_is_kinddeedproof_exist(ent, orderid))  {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "kinddeedproof " + orderid + " is not exist .");
        return ;
    }

    //判断订单是否存在
    order od;
    if (!_is_order_exist(od, orderid) ) {
        //删除此善举凭证
        _delete_kinddeedproof_record(orderid);
        _log_error(__FILE__, __FUNCTION__, __LINE__, "order lost, kinddeedproof " + orderid + " be delete .");
        return ;
    }

    if (ent.approved())  {
        _log_ok(__FILE__, __FUNCTION__, __LINE__, "kinddeedproof " + orderid + " has approved yet .");
        return ;
    }

    //删除此善举凭证
    if( !_delete_kinddeedproof_record(orderid) ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "delete failure .", ent.to_json());
        return;
    }

    _log_ok(__FILE__, __FUNCTION__, __LINE__, "refuse kinddeed " + orderid + " proof success .", ent.to_json());
}

void Main::find_kinddeedproof() {
    const string& orderid = ctx->arg("orderid");

    if( orderid.empty() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "kinddeedproof hash and orderid is empty .");
        return ;
    }

    //判断订单是否存在
    order od;        
    if (!_is_order_exist(od, orderid))  {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "order " + orderid + " is not exist .");
        return ;
    }

    //判断善举凭证是否已经存在
    kinddeedproof ent;
    if (!_is_kinddeedproof_exist(ent, orderid))  {
        _log_error(__FILE__, __FUNCTION__, __LINE__, "kinddeedproof " + orderid + " is not exist .");
        return ;
    }

    //身份检查，部署者，基金会成员，凭证所有者具有权限
    if( !is_deployer() &&
        !is_founder() &&
        ent.owner() != ctx->initiator() ) {
        _log_error(__FILE__, __FUNCTION__, __LINE__,ctx->initiator() + " have no authority to find kinddeedproof .");
        return ;
    }

    _log_ok(__FILE__, __FUNCTION__, __LINE__, "find", ent.to_json());
}

void Main::list_kinddeedproof() {
    //身份检查，部署者和基金会成员可以查看所有善举凭证
    if( is_deployer() ||
        is_founder() ) {
        xchain::json ja ;
        if(!_scan_kinddeedproof_by_orderid(ja,ctx->arg("orderid")) ) {
            _log_error(__FILE__, __FUNCTION__, __LINE__, "scan table failure .");
            return;
        }

        _log_ok(__FILE__, __FUNCTION__, __LINE__, "scan", ja);
        return;
    }

    //身份检查，寺院和法师只能查看属于自己善举的所有订单id的善举凭证
    if( is_temple() || 
        is_master() ) {
        xchain::json ja ;
        if(!_scan_kinddeedproof_by_owner_orderid(ja,ctx->initiator(),ctx->arg("orderid")) ) {
            _log_error(__FILE__, __FUNCTION__, __LINE__, "scan table failure .");
            return;
        }

        _log_ok(__FILE__, __FUNCTION__, __LINE__, "scan", ja);
        return;
    }

    _log_error(__FILE__, __FUNCTION__, __LINE__,ctx->initiator() + " have no authority to list kinddeedproof .");
    return ;
}


DEFINE_METHOD(Main, upload_kinddeedproof)     { self.upload_kinddeedproof();      }
DEFINE_METHOD(Main, approve_kinddeedproof)    { self.approve_kinddeedproof();     }
DEFINE_METHOD(Main, refuse_kinddeedproof)     { self.refuse_kinddeedproof();      }
DEFINE_METHOD(Main, find_kinddeedproof)       { self.find_kinddeedproof();        }
DEFINE_METHOD(Main, list_kinddeedproof)       { self.list_kinddeedproof();        }
