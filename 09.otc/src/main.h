#ifndef _OTC_H_
#define _OTC_H_

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
    xchain::cdt::Table<redeem>       _redeem_table;
    xchain::cdt::Table<order>        _order_table;

    xchain::Context* ctx;

public:

    decltype(_guaranty_table)& get_guaranty_table() {
        return _guaranty_table;
    }

    decltype(_redeem_table)& get_redeem_table() {
        return _redeem_table;
    }

    decltype(_order_table)& get_order_table() {
        return _order_table;
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

    bool _is_guaranty_exist(guaranty&, const string&);
    bool _is_redeem_exist(order&, const string&);
    bool _is_order_exist(order&, const string&);

    bool _scan_guaranty(xchain::json&, const string& ="");
    bool _scan_redeem(xchain::json&, const string& ="");
    bool _scan_order(xchain::json&, const string& ="");

    bool _add_guaranty(const string&,const string&,const string&);
    bool _add_redeem(const string&,const string&,const string&,const string&);
    bool _add_order(const string&,const string&,const string&,const string&);

    bool _delete_guaranty_record(const string&);
    bool _delete_redeem_record(const string&);
    bool _delete_order_record(const string&);

    bool _clear_guaranty();
    bool _clear_redeem();
    bool _clear_order();

    bool _transfer(const string&,const string&);

public:
    //对外的辅助接口

    void initialize();              //合约部署者
    void get_deployer();            //合约部署者，基金会成员。
    bool is_deployer();             //任意身份，判断自己是否是合约部署者

    //update无对应函数

    //发布卖单
    void publish();                 //卖家账户，任意身份
    void redeem();                  //卖家账户，任意身份
    void buy();                     //买家账户，任意身份
    void comfirm();                 //卖家账户，任意身份

    void find_guaranty();           //任意身份
    void list_guaranty();           //任意身份，根据身份id查所有，id可为空，安全

    bool find_redeem();             //任意身份
    void list_redeem();             //任意身份，根据身份id查所有，id可为空，安全

    bool find_order();              //任意身份
    void list_order();              //任意身份，根据身份id查所有，id可为空，安全
};
#endif // _OTC_H_