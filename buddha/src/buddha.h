#ifndef _BUDDHA_H_
#define _BUDDHA_H_

class Buddha : public xchain::Contract {
public:
    Buddha();

private:
    xchain::cdt::Table<founder>         _founder_table;
    xchain::cdt::Table<master>          _master_table;
    xchain::cdt::Table<member>          _member_table;
    xchain::cdt::Table<kinddeed>        _kinddeed_table;
    xchain::cdt::Table<kinddeeddetail>  _kinddeed_detail_table;
    xchain::cdt::Table<kinddeedspec>    _kinddeed_spec_table;
    xchain::cdt::Table<commentlabel>    _comment_label_table;
    xchain::cdt::Table<beforecomment>   _before_comment_table;
    xchain::cdt::Table<order>           _order_table;
    xchain::cdt::Table<kinddeedproof>   _kinddeed_proof_table;
    xchain::cdt::Table<aftercomment>    _after_comment_table;

    xchain::Context* ctx;

private:
    decltype(_founder_table)& get_founder_table();
    decltype(_master_table)& get_master_table();
    decltype(_member_table)& get_member_table();
    decltype(_kinddeed_table)& get_kinddeed_table();
    decltype(_kinddeed_detail_table)& get_kinddeed_detail_table();
    decltype(_kinddeed_spec_table)& get_kinddeed_spec_table();
    decltype(_comment_label_table)& get_comment_label_table();
    decltype(_before_comment_table)& get_before_comment_table();
    decltype(_order_table)& get_order_table();
    decltype(_kinddeed_proof_table)& get_kinddeed_proof_table();
    decltype(_after_comment_table)& get_after_comment_table();

private:
    //辅助函数
    bool _is_founder_exist_by_id(const std::string& id,founder& ent);

    bool _is_master_exist_by_id(const std::string& id,master& ent);
    bool _is_master_exist_by_unit(const std::string& unit,master& ent);
    bool _is_master_exist_by_creditcode(const std::string& creditcode,master& ent);
    bool _is_master_exist_by_address(const std::string& address,master& ent);
    bool _is_master_exist_by_deedplaceproof(const std::string& deedplaceproof,master& ent);

    bool _is_member_exist_by_id(const std::string& id,member& ent);
    bool _is_kinddeed_exist_by_id(const std::string& id,kinddeed& ent);
    bool _is_kinddeed_detail_exist_by_kdid(const std::string& kdid,kinddeeddetail& ent);
    bool _is_kinddeed_spec_exist_by_kdid(const std::string& kdid,kinddeedspec& ent);
    bool _is_comment_label_exist_by_id(const std::string& id,commentlabel& ent);
    bool _is_before_comment_exist_by_id(const std::string& id,beforecomment& ent);
    bool _is_order_exist_by_id(const std::string& id,order& ent);
    bool _is_kinddeed_proof_exist_by_orderid(const std::string& id,kinddeedproof& ent);
    bool _is_after_comment_exist_by_orderid(const std::string& id,aftercomment& ent);

    void _get_kinddeed(const std::string& id,kinddeed& ent);
    bool _is_kinddeed_online(const std::string& kdid) ;

    bool _is_deployer(const std::string& id);
    bool _is_founder(const std::string& id);
    bool _is_master(const std::string& id);
    bool _is_member(const std::string& id);
    bool _is_user(const std::string& id);

    bool _delete_founder_record(const std::string& id);
    bool _delete_master_record(const std::string& id);
    bool _delete_member_record(const std::string& id);
    bool _delete_kinddeed_record(const std::string& id);
    bool _delete_kinddeed_detail_record(const std::string& id);
    bool _delete_kinddeed_spec_record(const std::string& id);
    bool _delete_comment_label_record(const std::string& id);
    bool _delete_before_comment_record(const std::string& id);
    bool _delete_order_record(const std::string& id);
    bool _delete_kinddeed_proof_record(const std::string& orderid);
    bool _delete_after_comment_record(const std::string& id);

    bool _transfer(const std::string& id,
                   const std::string& amount);

public:
    //对外的辅助接口

    void initialize();      //合约部署者
    void get_deployer();    //所有角色
    bool is_deployer();     //所有角色


    //update无对应函数


    //申请成为基金会成员
    void apply_founder();   //用户,法师，寺院
    void approve_founder(); //合约部署者
    void recusal_founder(); //合约部署者
    bool is_founder();      //自己
    void list_founder();    //合约部署着，基金会成员

    //申请成为寺院
    void apply_temple();    //用户,法师
    void approve_temple();  //基金会成员
    void recusal_temple();  //基金会成员
    bool is_temple();       //自己
    void list_temple();     //合约部署着，基金会成员

    //申请成为法师
    void apply_master();    //用户
    void approve_master();  //基金会成员
    void recusal_master();  //基金会成员
    bool is_master();       //自己
    void list_master();     //所有角色

    //法师申请加入寺院
    void apply_join_temple();    //用户,会员
    void approve_join_temple();  //基金会成员
    void recusal_join_temple();  //基金会成员
    bool is_in_temple();         //法师自己
    void list_temple_master();   //合约部署着，基金会成员

    //添加删除修改善举    
    void add_kinddeed();    //基金会成员、法师
    void delete_kinddeed(); //基金会成员、法师
    void update_kinddeed(); //基金会成员、法师
    void find_kinddeed();   //所有用户
    void list_kinddeed();   //所有用户。这个接口是列举自己曾经的所有善举活动。尽可能的少的调用。会消耗大量的gas

    //申请善举上架下架    
    void apply_online_kinddeed();   //法师
    void apply_offline_kinddeed();  //法师
    void approve_online_kinddeed(); //基金会成员
    void approve_offline_kinddeed();//基金会成员

    //注册会员
    void apply_member();    //所有用户
    bool is_member();       //所有用户

    //会员祈求善举
    void pray_kinddeed();       //所有会员
    void find_pray_kinddeed();  //所有会员
    void list_pray_kinddeed();  //所有会员

    //基金会成员授权法师或寺院上传的善举凭证
    void upload_kinddeed_proof();   //法师
    void approve_kinddeed_proof();  //基金会成员
    void refuse_kinddeed_proof();   //基金会成员
    void list_kinddeed_proof();     //所有会员    

    void is_user();         //所有用户
};
#endif // _BUDDHA_H_