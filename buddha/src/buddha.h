#ifndef _BUDDHA_H_
#define _BUDDHA_H_

#include "xchain/xchain.h"
#include "xchain/contract.pb.h"

#include "founder.h"
#include "temple.h"
#include "master.h"
#include "templemaster.h"
#include "kinddeed.h"
#include "comment.h"
#include "order.h"
#include "kinddeedproof.h"

#include <string>
using namespace std;

class Buddha : public xchain::Contract {
public:
    Buddha();

private:
    xchain::cdt::Table<founder>         _founder_table;
    xchain::cdt::Table<temple>          _temple_table;
    xchain::cdt::Table<master>          _master_table;
    xchain::cdt::Table<templemaster>    _templemaster_table;
    xchain::cdt::Table<kinddeedtype>    _kinddeedtype_table;
    xchain::cdt::Table<kinddeed>        _kinddeed_table;
    xchain::cdt::Table<kinddeeddetail>  _kinddeeddetail_table;
    xchain::cdt::Table<kinddeedspec>    _kinddeedspec_table;
    xchain::cdt::Table<commentlabel>    _commentlabel_table;
    xchain::cdt::Table<beforecomment>   _beforecomment_table;
    xchain::cdt::Table<order>           _order_table;
    xchain::cdt::Table<kinddeedproof>   _kinddeedproof_table;
    xchain::cdt::Table<aftercomment>    _aftercomment_table;

    xchain::Context* ctx;

public:
    decltype(_founder_table)& get_founder_table() {
        return _founder_table;
    }

    decltype(_temple_table)& get_temple_table() {
        return _temple_table;
    }

    decltype(_master_table)& get_master_table() {
        return _master_table;
    }

    decltype(_templemaster_table)& get_templemaster_table() {
        return _templemaster_table;
    }

    decltype(_kinddeed_table)& get_kinddeed_table() {
        return _kinddeed_table;
    }

    decltype(_kinddeedtype_table)& get_kinddeedtype_table() {
        return _kinddeedtype_table;
    }

    decltype(_kinddeeddetail_table)& get_kinddeeddetail_table() {
        return _kinddeeddetail_table;
    }

    decltype(_kinddeedspec_table)& get_kinddeedspec_table() {
        return _kinddeedspec_table;
    }

    decltype(_commentlabel_table)& get_commentlabel_table() {
        return _commentlabel_table;
    }

    decltype(_beforecomment_table)& get_beforecomment_table() {
        return _beforecomment_table;
    }

    decltype(_order_table)& get_order_table() {
        return _order_table;
    }

    decltype(_kinddeedproof_table)& get_kinddeedproof_table() {
        return _kinddeedproof_table;
    }

    decltype(_aftercomment_table)& get_aftercomment_table() {
        return _aftercomment_table;
    }




private:
    //辅助函数
    bool _is_founder_exist(const string& id,founder& ent);

    bool _is_temple_exist(const string& id,temple& ent);
    bool _is_temple_exist_by_unit(const string& unit,temple& ent);
    bool _is_temple_exist_by_creditcode(const string& creditcode,temple& ent);
    bool _is_temple_exist_by_address(const string& address,temple& ent);
    bool _is_temple_exist_by_proof(const string& proof,temple& ent);

    bool _is_master_exist(const string& id,master& ent);
    bool _is_master_exist_by_proof(const string& proof,master& ent);

    bool _is_templemaster_exist(const string& templeid,
                                const string& masterid,
                                templemaster& ent);

    bool _is_kinddeedtype_exist(const string& id,kinddeedtype& ent);

    bool _is_kinddeed_exist(const string& id,kinddeed& ent);
    bool _is_kinddeeddetail_exist(const string& kdid, const string& seq, kinddeeddetail& ent);
    bool _is_kinddeeddetail_exist_by_kdid(const string& kdid,vector<kinddeeddetail>& vent);
    bool _is_kinddeedspec_exist(const string& kdid, const string& seq, kinddeedspec& ent);
    bool _is_kinddeedspec_exist_by_kdid(const string& kdid,vector<kinddeedspec>& vent);
    bool _is_commentlabel_exist(const string& id,commentlabel& ent);
    bool _is_all_types_exist_in_commentlabel(const xchain::json& label_array);
    bool _is_beforecomment_exist(const string& userid, const string& kdid,beforecomment& ent);
    bool _is_order_exist(const string& id,order& ent);
    bool _is_kinddeedproof_exist_by_order(const string& id,kinddeedproof& ent);
    bool _is_kinddeedproof_exist_by_proof(const string& proof,kinddeedproof& ent);
    bool _is_aftercomment_exist(const string& orderid,aftercomment& ent);

    bool _get_kinddeed(const string& id,kinddeed& ent);
    bool _is_kinddeed_online(const string& kdid) ;

    bool _is_deployer(const string& id);
    bool _is_founder(const string& id);
    bool _is_temple(const string& id);
    bool _is_master(const string& id);
    bool _is_in_temple(const string& templeid, const string& masterid,templemaster& ent );
    bool _is_user(const string& id);

    bool _delete_founder_record(const string& id);
    bool _delete_temple_record(const string& id);
    bool _delete_master_record(const string& id);
    bool _delete_templemaster_record(const string& templeid, const string& masterid);
    bool _delete_kinddeedtype_record(const string& id);
    bool _delete_kinddeed_record(const string& id);
    bool _delete_kinddeeddetail_record(const string& id);
    bool _delete_kinddeedspec_record(const string& id);
    bool _delete_commentlabel_record(const string& id);
    bool _delete_beforecomment_record(const string& userid, const string& kdid);
    bool _delete_order_record(const string& id);
    bool _delete_kinddeedproof_record(const string& orderid);
    bool _delete_aftercomment_record(const string& orderid);

    bool _transfer(const string& id,
                   const string& amount);

public:
    //对外的辅助接口

    void initialize();              //合约部署者
    void get_deployer();            //合约部署者，基金会成员。
    bool is_deployer();             //所有角色，判断自己是否是合约部署者


    //update无对应函数


    //申请成为基金会成员
    void apply_founder();           //用户,法师，寺院，合约部署者也可以
    void approve_founder();         //合约部署者
    void recusal_founder();         //合约部署者
    bool is_founder();              //所有角色，判断自己是否是基金会成员
    void list_founder();            //合约部署着，基金会成员

    //申请成为寺院
    void apply_temple();            //用户,法师
    void approve_temple();          //基金会成员
    void recusal_temple();          //基金会成员
    bool is_temple();               //所有角色，判断自己是否是寺院
    void list_temple();             //合约部署着，基金会成员

    //申请成为法师
    void apply_master();            //用户
    void approve_master();          //基金会成员
    void recusal_master();          //基金会成员
    bool is_master();               //所有角色，判断自己是否是法师
    void list_master();             //所有角色

    //法师申请加入寺院
    void apply_join_temple();       //法师
    void approve_join_temple();     //基金会成员
    void recusal_join_temple();     //基金会成员
    bool is_in_temple();            //法师
    void list_temple_master();      //合约部署着，基金会成员,寺院自己

    //添加删除修改善举类型
    void add_kinddeedtype();        //基金会成员
    void delete_kinddeedtype();     //基金会成员
    void update_kinddeedtype();     //基金会成员
    void find_kinddeedtype();       //所有用户
    void list_kinddeedtype();       //基金会成员

    //添加删除修改善举    
    void add_kinddeed();            //基金会成员、寺院、法师
    void delete_kinddeed();         //基金会成员、寺院、法师
    void update_kinddeed();         //基金会成员、寺院、法师，只要修改善举，就需要重新审核上架
    void find_kinddeed();           //所有用户
    void list_kinddeed();           //部署者、基金会成员、寺院、法师。这个接口是列举自己曾经的所有善举活动。尽可能的少的调用。会消耗大量的gas

    //申请善举上架下架    
    void apply_online_kinddeed();   //寺院、法师
    void apply_offline_kinddeed();  //寺院、法师
    void approve_online_kinddeed(); //基金会成员
    void approve_offline_kinddeed();//基金会成员

    //添加删除修改点评标签
    void add_commentlabel();        //所有用户
    void delete_commentlabel();     //所有用户
    void update_commentlabel();     //所有用户
    void find_commentlabel();       //所有用户
    void list_commentlabel();       //基金会成员

    //添加删除修改祈求善举前点评
    void add_beforecomment();       //所有用户
    void delete_beforecomment();    //所有者，基金会成员
    void update_beforecomment();    //所有者
    void find_beforecomment();      //所有者，基金会成员，善举所有者(法师或寺院)
    void list_beforecomment();      //基金会成员，善举所有者(法师或寺院)

    //会员祈求善举
    void pray_kinddeed();           //所有会员
    void find_pray_kinddeed();      //所有会员
    void list_pray_kinddeed();      //部署者、基金会成员、寺院、法师
    bool is_user();                 //所有用户

    //基金会成员授权法师或寺院上传的善举凭证
    void upload_kinddeedproof();   //法师
    void approve_kinddeedproof();  //基金会成员
    void refuse_kinddeedproof();   //基金会成员
    void find_kinddeedproof();     //部署者、基金会成员  
    void list_kinddeedproof();     //部署者、基金会成员  

    //添加删除修改祈求善举后点评
    void add_aftercomment();       //所有用户
    void delete_aftercomment();    //所有者，基金会成员
    void update_aftercomment();    //所有者
    void find_aftercomment();      //所有者，基金会成员，善举所有者(法师或寺院)
    void list_aftercomment();      //基金会成员，善举所有者(法师或寺院)

};
#endif // _BUDDHA_H_