#ifndef _MEMORIAL_HALL_H_
#define _MEMORIAL_HALL_H_

#include "xchain/xchain.h"
#include "xchain/json/json.h"
#include "xchain/contract.pb.h"

#include <string>
using namespace std;

#define mycout cout << __FILE__ << "(" << __LINE__ << ") [" << __FUNCTION__ << "] " 

class Main : public xchain::Contract {
public:
    Main();

private:
    xchain::cdt::Table<guaranty>     _guaranty_table;
    xchain::cdt::Table<log>          _log_table;

    xchain::Context* ctx;

public:

    decltype(_guaranty_table)& get_guaranty_table() {
        return _guaranty_table;
    }

    decltype(_log_table)& get_log_table() {
        return _log_table;
    }

private:
    //辅助函数

    void _log_error(const string&, const string&, const int, const string& ="") ;
    void _log_error(const string&, const string&, const int, const string&, const xchain::json&) ;
    void _log_ok(const string&, const string&, const int, const string& ="") ;
    void _log_ok(const string&, const string&, const int, const string&, const xchain::json&) ;

    bool _is_guaranty_exist(guaranty&, const string&);
    bool _is_log_exist(log&, const string&);

    bool _is_deployer(const string&);
    bool _is_founder(const string&);
    bool _is_visitor(const string&);
    bool _is_user(const string&);
    bool _is_identifyuser(const string&);
    bool _is_master(const string&);
    bool _is_temple(const string&);
    bool _is_thedead(const string&);

    bool _scan_guaranty(xchain::json&, const string& ="");
    bool _scan_log(xchain::json&, const string& ="");

    bool _add_guaranty(const string&,const string&,const string&);
    bool _add_log(const string&,const string&,const string&,const string&);

    bool _delete_guaranty_record(const string&);
    bool _delete_log_record(const string&);

    bool _clear_guaranty();
    bool _clear_log();

    bool _transfer(const string&,const string&);

public:
    //对外的辅助接口

    void initialize();              //合约部署者
    void get_deployer();            //合约部署者，基金会成员。
    bool is_deployer();             //任意身份，判断自己是否是合约部署者

    //update无对应函数

    //发布卖单
    void publish();                 //卖家账户，任意身份
    void buy();                     //买家账户，任意身份
    void comfirm();                 //卖家账户，任意身份
    void redeem();                  //卖家账户，任意身份

    void find_guaranty();           //任意身份，根据id查找
    void list_guaranty();           //任意身份，根据id查所有，id可为空，安全

    bool find_log();                //任意身份，判断自己是否是法师
    void list_log();                //合约部署者，基金会成员，根据id查所有，id可为空，基本安全，

    //法师申请加入寺院
    void apply_join_guaranty();       //法师
    void approve_join_guaranty();     //基金会成员
    void recusal_join_guaranty();     //基金会成员
    bool is_in_guaranty();            //法师
    void list_guaranty_log();      //合约部署者，基金会成员,寺院自己，根据guarantyid查所有，guarantyid为空时基本安全，guarantyid不为空时，安全

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
#endif // _MEMORIAL_HALL_H_