#ifndef _BUDDHA_H_
#define _BUDDHA_H_

#include "xchain/xchain.h"
#include "xchain/json/json.h"
#include "xchain/contract.pb.h"

#include "founder.h"
#include "proposal.h"
#include "temple.h"
#include "master.h"
#include "templemaster.h"
#include "kinddeed.h"
#include "comment.h"
#include "order.h"
#include "kinddeedproof.h"
#include "credit.h"
#include "creditranking.h"
#include "merit.h"
#include "meritranking.h"

#include <string>
using namespace std;

#define mycout cout << __FILE__ << "(" << __LINE__ << ") [" << __FUNCTION__ << "] " 

class Buddha : public xchain::Contract {
public:
    Buddha();

private:
    xchain::cdt::Table<founder>         _founder_table;
    xchain::cdt::Table<proposal>        _proposal_table;
    xchain::cdt::Table<kinddeedtype>    _kinddeedtype_table;
    xchain::cdt::Table<kinddeed>        _kinddeed_table;
    xchain::cdt::Table<kinddeeddetail>  _kinddeeddetail_table;
    xchain::cdt::Table<kinddeedspec>    _kinddeedspec_table;
    xchain::cdt::Table<commentlabel>    _commentlabel_table;
    xchain::cdt::Table<beforecomment>   _beforecomment_table;
    xchain::cdt::Table<order>           _order_table;
    xchain::cdt::Table<kinddeedproof>   _kinddeedproof_table;
    xchain::cdt::Table<aftercomment>    _aftercomment_table;
    xchain::cdt::Table<credit>          _credit_table;
    xchain::cdt::Table<creditranking>   _creditranking_table;
    xchain::cdt::Table<merit>           _merit_table;
    xchain::cdt::Table<meritranking>    _meritranking_table;

    xchain::Context* ctx;

public:

    decltype(_founder_table)& get_founder_table() {
        return _founder_table;
    }

    decltype(_proposal_table)& get_proposal_table() {
        return _proposal_table;
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

    decltype(_credit_table)& get_credit_table() {
        return _credit_table;
    }

    decltype(_creditranking_table)& get_creditranking_table() {
        return _creditranking_table;
    }

    decltype(_merit_table)& get_merit_table() {
        return _merit_table;
    }

    decltype(_meritranking_table)& get_meritranking_table() {
        return _meritranking_table;
    }





private:
    //辅助函数

    void _log_error(const string&, const string&, const int, const string& ="") ;
    void _log_error(const string&, const string&, const int, const string&, const xchain::json&) ;
    void _log_ok(const string&, const string&, const int, const string& ="") ;
    void _log_ok(const string&, const string&, const int, const string&, const xchain::json&) ;

    bool _is_founder_exist(founder&, const string&);
    bool _is_proposal_exist(proposal&, const string&);
    bool _is_kinddeedtype_exist(kinddeedtype&, const string&);
    bool _is_kinddeed_exist(kinddeed&, const string&);
    bool _is_kinddeeddetail_exist(kinddeeddetail&, const string&, const string&);
    bool _is_kinddeedspec_exist(kinddeedspec&, const string&, const string& seq);
    bool _is_commentlabel_exist(commentlabel&, const string&);
    bool _is_all_types_exist_in_commentlabel(const xchain::json& label_array);
    bool _is_beforecomment_exist(beforecomment&, const string&, const string&);
    bool _is_order_exist(order&, const string&);
    bool _is_kinddeedproof_exist(kinddeedproof&, const string&);
    bool _is_aftercomment_exist(aftercomment&, const string&, const string&);
    bool _is_credit_exist(credit&, const string&);
    bool _is_creditranking_exist(creditranking&, const string&);
    bool _is_merit_exist(merit&, const string&);
    bool _is_meritranking_exist(meritranking&, const string&);
    bool _is_kinddeed_online(const string&) ;

    bool _is_deployer(const string&);
    bool _is_founder(const string&);

    bool _scan_founder(xchain::json&, const string& ="");
    bool _scan_proposal(xchain::json&, const string& ="");
    bool _scan_kinddeedtype(xchain::json&, const string& ="");
    bool _scan_kinddeed_by_id(xchain::json&, const string& ="");
    bool _scan_kinddeed_by_owner(xchain::json&, const string& ="");
    bool _scan_kinddeed_by_idowner(xchain::json&, const string& ="");
    bool _scan_kinddeeddetail(vector<kinddeeddetail>&, const string& ="");
    bool _scan_kinddeeddetail(xchain::json&, const string& ="");
    bool _scan_kinddeedspec(vector<kinddeedspec>&, const string& ="");
    bool _scan_kinddeedspec(xchain::json&, const string& ="");
    bool _scan_commentlabel(xchain::json&, const string& ="");
    bool _scan_beforecomment(xchain::json&, const string& ="");
    bool _scan_order_by_id(xchain::json&, const string& ="");
    bool _scan_order_by_kdowner(xchain::json&, const string& ="");    
    bool _scan_kinddeedproof_by_orderid(xchain::json&, const string& ="");
    bool _scan_kinddeedproof_by_owner(xchain::json&, const string& ="");
    bool _scan_kinddeedproof_by_owner_orderid(xchain::json&, const string& ="", const string& ="");    
    bool _scan_aftercomment_by_orderid(xchain::json&, const string& ="");
    bool _scan_credit(xchain::json&, const string&);
    bool _scan_creditranking(xchain::json&, const string& ="");
    bool _scan_creditranking(vector<creditranking>&, const string& ="");
    bool _scan_merit(xchain::json&, const string&);
    bool _scan_meritranking(xchain::json&, const string& ="");
    bool _scan_meritranking(vector<meritranking>&, const string& ="");

    bool _add_kinddeeddetail(const string&,const string&,const string&);
    bool _add_kinddeedspec(const string&,const string&,const string&,const string&);
    bool _add_credit(const string&, const int64_t, int64_t&);
    bool _add_creditranking(const string&, const int64_t);
    bool _add_merit(const string&, const int64_t, int64_t&);
    bool _add_meritranking(const string&, const int64_t);

    bool _delete_founder_record(const string&);
    bool _delete_proposal_record(const string&);
    bool _delete_kinddeedtype_record(const string&);
    bool _delete_kinddeed_record(const string&);
    bool _delete_kinddeeddetail_record(const string&, const string& ="");
    bool _delete_kinddeedspec_record(const string&, const string& ="");
    bool _delete_commentlabel_record(const string&);
    bool _delete_beforecomment_record(const string&, const string&);
    bool _delete_order_record(const string&);
    bool _delete_kinddeedproof_record(const string&);
    bool _delete_aftercomment_record(const string&, const string&);
    bool _delete_credit_record(const string&);
    bool _delete_creditranking_record(const string&);
    bool _delete_merit_record(const string&);
    bool _delete_meritranking_record(const string&);

    bool _clear_creditranking();
    bool _clear_meritranking();

    bool _transfer(const string&,const string&);

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
    void list_founder();            //合约部署者，基金会成员，根据id查所有，id可为空，安全，

    //提案
    void make_proposal();           //基金会成员
    void delete_proposal();         //基金会成员
    void update_proposal();         //基金会成员
    void approve_proposal();        //基金会成员
    //void recusal_proposal();        //基金会成员
    void find_proposal();           //基金会成员
    void list_proposal();           //基金会成员


    //添加删除修改善举类型
    void add_kinddeedtype();        //基金会成员
    void delete_kinddeedtype();     //基金会成员
    void update_kinddeedtype();     //基金会成员
    void find_kinddeedtype();       //所有用户
    void list_kinddeedtype();       //所有用户，根据id查所有，安全，

    //添加删除修改善举    
    void add_kinddeeddetail();
    void delete_kinddeeddetail();
    void list_kinddeeddetail();     //部署者，基金会成员，列举所有善举，根据id查所有，id为空时不安全，id不为空时基本安全，支持模糊查询
                                    //寺院，法师。列举所有者所有善举，根据owner查匹配，基本安全

    void add_kinddeedspec();
    void delete_kinddeedspec();
    void list_kinddeedspec();       //部署者，基金会成员，列举所有善举，根据id查所有，id为空时不安全，id不为空时基本安全，支持模糊查询
                                    //寺院，法师。列举所有者所有善举，根据owner查匹配，基本安全

    void add_kinddeed();            //基金会成员，寺院，法师
    void delete_kinddeed();         //基金会成员，寺院，法师
    void update_kinddeed();         //基金会成员，寺院，法师，只要修改善举，就需要重新审核上架
    void find_kinddeed();           //所有用户
    void list_kinddeed();           //部署者，基金会成员，列举所有善举，根据id查所有，id为空时不安全，id不为空时基本安全，支持模糊查询
                                    //寺院，法师。列举所有者所有善举，根据owner查匹配，基本安全

    //善举下架    
    void offline_kinddeed();        //基金会成员
    void is_kinddeed_online();      //所有用户

    //添加删除修改点评标签
    void add_commentlabel();        //基金会成员
    void delete_commentlabel();     //基金会成员
    void update_commentlabel();     //基金会成员
    void find_commentlabel();       //所有用户
    void list_commentlabel();       //所有用户，根据id查所有，安全，

    //添加删除修改祈求善举前点评
    void add_beforecomment();       //所有用户
    void delete_beforecomment();    //所有者，基金会成员
    void update_beforecomment();    //所有者
    void find_beforecomment();      //所有者，基金会成员，善举所有者(法师或寺院)
    void list_beforecomment();      //所有用户，点评本来就是给所有人看的，根据kdid查匹配，安全，

    //用户祈求善举，即订单
    void pray_kinddeed();           //所有用户
    void delete_pray_kinddeed();    //部署者，基金会成员,寺院，法师(善举所有者),订单所有者
    void find_pray_kinddeed();      //部署者，基金会成员，寺院，法师，所有者
    void list_pray_kinddeed();      //部署者，基金会成员，根据id查所有，id为空时不安全，id不为空时基本安全，支持模糊查询
                                    //寺院，法师(善举发布者,只查看自己发布的所有善举的订单)，根据kdowner查匹配，基本安全
    bool is_user();                 //所有用户

    //基金会成员授权法师或寺院上传的善举凭证
    void upload_kinddeedproof();   //基金会成员，寺院，法师
    void approve_kinddeedproof();  //基金会成员
    void refuse_kinddeedproof();   //基金会成员
    void find_kinddeedproof();     //部署者，基金会成员，善举凭证所有者
    void list_kinddeedproof();     //部署者，基金会成员，根据orderid查所有，orderid为空时不安全，orderid不为空时基本安全，支持模糊查询
                                   //寺院，法师(善举凭证所有者,只查看自己发布的所有善举凭证),根据owner查匹配，根据orderid查所有，orderid为空时不安全，orderid不为空时基本安全，支持模糊查询

    //添加删除修改祈求善举后点评
    void add_aftercomment();       //善举的购买者
    void delete_aftercomment();    //所有者，基金会成员
    void update_aftercomment();    //所有者
    void find_aftercomment();      //所有者，基金会成员，善举所有者(法师或寺院)
    void list_aftercomment();      //部署者，基金会成员，根据orderid查匹配，orderid为空时极不安全，orderid不为空时基本安全
                                   //其他，点评本来就是给所有人看的，根据orderid查匹配，安全，

    void find_credit();             //所有用户
    void list_credit();             //部署者，基金会成员，数据量过大时不安全
    void list_creditranking();      //获取前100所有的信用值排名
    void get_creditranking();       //查看第n名的情况

    void find_merit();             //所有用户
    void list_merit();             //部署者，基金会成员，数据量过大时不安全
    void list_meritranking();      //获取前100所有的信用值排名
    void get_meritranking();       //查看第n名的情况

};
#endif // _BUDDHA_H_