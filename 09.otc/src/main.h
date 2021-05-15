#ifndef _MAIN_H_
#define _MAIN_H_

#include "xchain/xchain.h"
#include "xchain/json/json.h"
#include "xchain/contract.pb.h"

#include "sell.h"

#include <string>
using namespace std;

#define mycout cout << __FILE__ << "(" << __LINE__ << ") [" << __FUNCTION__ << "] " 

class Main : public xchain::Contract {
public:
    Main();

private:
    xchain::cdt::Table<BBSell>          _sell_table;
    xchain::cdt::Table<BBRedeemSell>    _redeemsell_table;
    xchain::cdt::Table<order>        _order_table;

    xchain::Context* ctx;

public:

    decltype(_sell_table)& get_sell_table() {
        return _sell_table;
    }

    decltype(_redeemsell_table)& get_redeemsell_table() {
        return _redeemsell_table;
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
    bool _is_identifyuser(const string&);
    bool _is_master(const string&);
    bool _is_temple(const string&);
    bool _is_thedead(const string&);

    bool _is_sell_exist(sell&, const string&);
    bool _is_redeemsell_exist(order&, const string&);
    bool _is_order_exist(order&, const string&);

    bool _scan_sell(xchain::json&, const string& ="");
    bool _scan_redeem(xchain::json&, const string& ="");
    bool _scan_order(xchain::json&, const string& ="");

    bool _add_sell(const string&,const string&,const string&);
    bool _add_redeem(const string&,const string&,const string&,const string&);
    bool _add_order(const string&,const string&,const string&,const string&);

    bool _delete_sell_record(const string&);
    bool _delete_redeemsell_record(const string&);
    bool _delete_order_record(const string&);

    bool _clear_sell();
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

    void find_sell();           //任意身份
    void list_sell();           //任意身份，根据身份id查所有，id可为空，安全

    bool find_redeem();             //任意身份
    void list_redeem();             //任意身份，根据身份id查所有，id可为空，安全

    bool find_order();              //任意身份
    void list_order();              //任意身份，根据身份id查所有，id可为空，安全
};
#endif // _MAIN_H_