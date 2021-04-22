#ifndef _MAIN_H_
#define _MAIN_H_

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
    xchain::cdt::Table<identity>     _identity_table;
    xchain::cdt::Table<visitor>       _visitor_table;
    xchain::cdt::Table<user>        _user_table;

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
    bool _is_identity_user(const string&);
    bool _is_master(const string&);
    bool _is_temple(const string&);
    bool _is_thedead(const string&);

    bool _is_identity_exist(identity&, const string&);
    bool _is_visitor_exist(user&, const string&);
    bool _is_user_exist(user&, const string&);
    bool _is_identity_user_exist(user&, const string&);
    bool _is_master_exist(user&, const string&);
    bool _is_temple_exist(user&, const string&);
    bool _is_the_dead_exist(user&, const string&);

    bool _scan_identity(xchain::json&, const string& ="");
    bool _scan_visitor(xchain::json&, const string& ="");
    bool _scan_user(xchain::json&, const string& ="");
    bool _scan_identity_user(xchain::json&, const string& ="");
    bool _scan_master(xchain::json&, const string& ="");
    bool _scan_temple(xchain::json&, const string& ="");
    bool _scan_the_dead(xchain::json&, const string& ="");

    bool _add_identity(const string&,const string&,const string&);
    bool _add_visitor(const string&,const string&,const string&,const string&);
    bool _add_user(const string&,const string&,const string&,const string&);
    bool _add_identity_user(const string&,const string&,const string&,const string&);
    bool _add_master(const string&,const string&,const string&,const string&);
    bool _add_temple(const string&,const string&,const string&,const string&);
    bool _add_the_dead(const string&,const string&,const string&,const string&);

    bool _delete_identity_record(const string&);
    bool _delete_visitor_record(const string&);
    bool _delete_user_record(const string&);
    bool _delete_identity_user_record(const string&);
    bool _delete_master_record(const string&);
    bool _delete_temple_record(const string&);
    bool _delete_the_dead_record(const string&);

    bool _clear_identity();
    bool _clear_visitor();
    bool _clear_user();
    bool _clear_identity_user();
    bool _clear_master();
    bool _clear_temple();
    bool _clear_the_dead();

    bool _transfer(const string&,const string&);

public:
    //对外的辅助接口

    void initialize();              //合约部署者
    void get_deployer();            //合约部署者，基金会成员。
    bool is_deployer();             //任意身份，判断自己是否是合约部署者

    //update无对应函数

    //发布卖单

    void find_identity();           //任意身份
    void list_identity();           //任意身份，根据身份id查所有，id可为空，安全

    bool find_visitor();             //任意身份
    void list_visitor();             //任意身份，根据身份id查所有，id可为空，安全

    bool find_user();              //任意身份
    void list_user();              //任意身份，根据身份id查所有，id可为空，安全

    bool find_identity_user();              //任意身份
    void list_identity_user();              //任意身份，根据身份id查所有，id可为空，安全

    bool find_master();              //任意身份
    void list_master();              //任意身份，根据身份id查所有，id可为空，安全

    bool find_temple();              //任意身份
    void list_temple();              //任意身份，根据身份id查所有，id可为空，安全

    bool find_the_dead();              //任意身份
    void list_the_dead();              //任意身份，根据身份id查所有，id可为空，安全
};
#endif // _MAIN_H_