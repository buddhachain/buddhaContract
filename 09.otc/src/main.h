#ifndef _MAIN_H_
#define _MAIN_H_

#include "xchain/xchain.h"
#include "xchain/json/json.h"
#include "xchain/contract.pb.h"

#include "sell.h"
#include "redeem_sell.h"
#include "buy_order.h"

#include <string>
using namespace std;

#define mycout cout << __FILE__ << "(" << __LINE__ << ") [" << __FUNCTION__ << "] " 

class Main : public xchain::Contract {
public:
    Main();

private:
    xchain::cdt::Table<BBSell>          _sell_table;
    xchain::cdt::Table<BBRedeemSell>    _redeemsell_table;
    xchain::cdt::Table<BCBuyOrder>      _buyorder_table;

    xchain::Context* ctx;

public:

    decltype(_sell_table)& get_sell_table() {
        return _sell_table;
    }

    decltype(_redeemsell_table)& get_redeemsell_table() {
        return _redeemsell_table;
    }

    decltype(_buyorder_table)& get_buyorder_table() {
        return _buyorder_table;
    }

private:
    //辅助函数

    void _log_error(const string&, const string&, const int, const string& ="") ;
    void _log_error(const string&, const string&, const int, const string&, const xchain::json&) ;
    void _log_ok(const string&, const string&, const int, const string& ="") ;
    void _log_ok(const string&, const string&, const int, const string&, const xchain::json&) ;

    bool _is_deployer(const string&);
    bool _is_founder(const string&);
    bool _is_identifyuser(const string&);

    bool _is_sell_exist(BBSell&, const string&);
    bool _is_redeemsell_exist(BBRedeemSell&, const string&);
    bool _is_buyorder_exist(BCBuyOrder&, const string&);

    bool _scan_sell(xchain::json&, const string& ="");
    bool _scan_redeemsell(xchain::json&, const string& ="");
    bool _scan_buyorder(xchain::json&, const string& ="");

    bool _add_sell(const string&,const string&,const string&);
    bool _add_redeemsell(const string&,const string&,const string&,const string&);
    bool _add_buyorder(const string&,const string&,const string&,const string&);

    bool _delete_sell_record(const string&);
    bool _delete_redeemsell_record(const string&);
    bool _delete_buyorder_record(const string&);

    bool _clear_sell();
    bool _clear_redeemsell();
    bool _clear_buyorder();

    bool _transfer(const string&,const string&);

public:
    //对外的辅助接口

    void initialize();              //合约部署者
    void get_deployer();            //合约部署者，基金会成员。
    bool is_deployer();             //任意身份，判断自己是否是合约部署者

    //update无对应函数

    //发布卖单
    void hang_sell();               //认证用户
    void redeem_sell();             //认证用户
    void buy();                     //任意身份
    void confirm_buy();             //商家本身
    void recusal_buy();             //任意身份

    void find_sell();               //任意身份
    void list_sell();               //任意身份，根据身份id查所有，id可为空，安全

    bool find_redeemsell();         //任意身份
    void list_redeemsell();         //任意身份，根据身份id查所有，id可为空，安全

    bool find_buyorder();           //任意身份
    void list_buyorder();           //任意身份，根据身份id查所有，id可为空，安全
};

#endif // _MAIN_H_