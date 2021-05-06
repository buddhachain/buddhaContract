#ifndef _MAIN_H_
#define _MAIN_H_

#include "xchain/xchain.h"
#include "xchain/json/json.h"
#include "xchain/contract.pb.h"

#include "identity.h"
#include "visitor.h"
#include "user.h"
#include "identifyuser.h"
#include "master.h"
#include "temple.h"
#include "templemaster.h"
#include "thedead.h"

#include <string>
using namespace std;

#define mycout cout << __FILE__ << "(" << __LINE__ << ") [" << __FUNCTION__ << "] " 

class Main : public xchain::Contract {
public:
    Main();

private:
    xchain::cdt::Table<BIdentity>      _identity_table;
    xchain::cdt::Table<BVisitor>       _visitor_table;
    xchain::cdt::Table<BUser>          _user_table;
    xchain::cdt::Table<BIdentifyUser>  _identifyuser_table;
    xchain::cdt::Table<BMaster>        _master_table;
    xchain::cdt::Table<BTemple>        _temple_table;
    xchain::cdt::Table<BTempleMaster>  _templemaster_table;
    xchain::cdt::Table<BTheDead>       _thedead_table;

    xchain::Context* ctx;

public:

    decltype(_identity_table)& get_identity_table() {
        return _identity_table;
    }

    decltype(_visitor_table)& get_visitor_table() {
        return _visitor_table;
    }

    decltype(_user_table)& get_user_table() {
        return _user_table;
    }

    decltype(_identifyuser_table)& get_identifyuser_table() {
        return _identifyuser_table;
    }

    decltype(_master_table)& get_master_table() {
        return _master_table;
    }

    decltype(_temple_table)& get_temple_table() {
        return _temple_table;
    }

    decltype(_templemaster_table)& get_templemaster_table() {
        return _templemaster_table;
    }

    decltype(_thedead_table)& get_thedead_table() {
        return _thedead_table;
    }

private:
    //辅助函数

    void _log_error(const string&, const string&, const int, const string& ="") ;
    void _log_error(const string&, const string&, const int, const string&, const xchain::json&) ;
    void _log_ok(const string&, const string&, const int, const string& ="") ;
    void _log_ok(const string&, const string&, const int, const string&, const xchain::json&) ;

    bool _is_deployer(const string&);
    bool _is_founder(const string&);
    bool _is_visitor(const string&);
    bool _is_user(const string&);
    bool _is_identifyuser(const string&);
    bool _is_master(const string&);
    bool _is_temple(const string&);
    bool _is_thedead(const string&);

    bool _is_identity_exist(BIdentity&, const string&);
    bool _is_visitor_exist(BVisitor&, const string&);
    bool _is_user_exist(BUser&, const string&);
    bool _is_identifyuser_exist(BIdentifyUser&, const string&);
    bool _is_master_exist(BMaster&, const string&);
    bool _is_temple_exist(BTemple&, const string&);
    bool _is_templemaster_exist(BTempleMaster&, const string&, const string&);
    bool _is_in_temple(BTempleMaster&, const string&, const string&);
    bool _is_thedead_exist(BTheDead&, const string&);

    bool _scan_identity(xchain::json&,
                        const string& ="");

    bool _scan_visitor(xchain::json&,
                       const string& ="",
                       const string& ="",
                       const string& ="");

    bool _scan_user(xchain::json&, const string& ="");
    bool _scan_identifyuser(xchain::json&, const string& ="");
    bool _scan_master(xchain::json&,
                      const string& ="",
                      const string& ="",
                      const string& ="",
                      const string& ="");
    bool _scan_temple(xchain::json&, const string& ="");
    bool _scan_templemaster_by_templeid(xchain::json&, const string& ="");
    bool _scan_templemaster_by_masterid(xchain::json&, const string& ="");
    bool _scan_thedead(xchain::json&, const string& ="");

    bool _add_identity(const string&,const string&);
    bool _add_visitor(const string&,const string&,const string&,const string&);
    bool _add_user(const string&,const string&,const string&,const string&);
    bool _add_identifyuser(const string&,const string&,const string&,const string&);
    bool _add_master(const string&,const string&,const string&,const string&);
    bool _add_temple(const string&,const string&,const string&,const string&);
    bool _add_thedead(const string&,const string&,const string&,const string&);

    bool _delete_identity_record(const string&);
    bool _delete_visitor_record(const string&);
    bool _delete_user_record(const string&);
    bool _delete_identifyuser_record(const string&);
    bool _delete_master_record(const string&);
    bool _delete_temple_record(const string&);
    bool _delete_templemaster_record(const string&, const string&);
    bool _delete_thedead_record(const string&);

    bool _clear_identity();
    bool _clear_visitor();
    bool _clear_user();
    bool _clear_identifyuser();
    bool _clear_master();
    bool _clear_temple();
    bool _clear_templemaster();
    bool _clear_thedead();

    bool _transfer(const string&,const string&);

public:
    //对外的辅助接口

    void initialize();              //合约部署者
    void get_deployer();            //合约部署者，基金会成员。
    bool is_deployer();             //任意身份，判断自己是否是合约部署者

    bool is_founder();              //所有角色，判断自己是否是基金会成员

    //update无对应函数

    //所有的list函数，尽可能key:value中的value不为空，缩小scan范围，提高效率

    bool find_identity();           //任意身份
    void list_identity();           //基金会成员

    bool is_visitor();              //任意身份
    void list_visitor();            //基金会成员

    bool is_user();                 //任意身份
    void list_user();               //基金会成员

    bool is_identifyuser();        //任意身份
    void list_identifyuser();      //基金会成员

    bool is_master();               //任意身份
    void list_master();             //基金会成员

    bool is_temple();               //任意身份
    void list_temple();             //基金会成员

    bool is_thedead();           //任意身份
    void list_thedead();           //基金会成员


    //添加身份
    void add_identity();             //任意身份

    //添加游客
    void add_visitor();             //任意身份
    
    //添加用户
    void add_user();                //任意身份

    //申请成为认证用户
    void apply_identifyuser();     //用户，游客
    void approve_identifyuser();   //基金会成员
    void recusal_identifyuser();   //基金会成员

    //申请成为法师
    void apply_master();            //用户
    void approve_master();          //基金会成员
    void recusal_master();          //基金会成员

    //申请成为寺院
    void apply_temple();            //用户,法师
    void approve_temple();          //基金会成员
    void recusal_temple();          //基金会成员

    //法师申请加入寺院
    void apply_join_temple();       //法师
    void approve_join_temple();     //基金会成员
    void recusal_join_temple();     //基金会成员
    bool is_in_temple();            //法师
    void list_my_master();          //寺院
    void list_temple_master();      //基金会成员
    
    //添加逝者
    void add_thedead();                //任意身份
};
#endif // _MAIN_H_