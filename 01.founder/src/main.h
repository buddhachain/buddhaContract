#ifndef _MAIN_H_
#define _MAIN_H_

#include "xchain/xchain.h"
#include "xchain/json/json.h"
#include "xchain/contract.pb.h"

#include "founder.h"
#include "proposal.h"

#include <string>
using namespace std;

#define mycout cout << __FILE__ << "(" << __LINE__ << ") [" << __FUNCTION__ << "] " 

class Main : public xchain::Contract {
public:
    Main();

private:
    xchain::cdt::Table<BFounder>         _founder_table;
    xchain::cdt::Table<BProposal>        _proposal_table;

    xchain::Context* ctx;

public:

    decltype(_founder_table)& get_founder_table() {
        return _founder_table;
    }

    decltype(_proposal_table)& get_proposal_table() {
        return _proposal_table;
    }


private:
    //辅助函数

    void _log_error(const string&, const string&, const int, const string& ="") ;
    void _log_error(const string&, const string&, const int, const string&, const xchain::json&) ;
    void _log_ok(const string&, const string&, const int, const string& ="") ;
    void _log_ok(const string&, const string&, const int, const string&, const xchain::json&) ;

    bool _is_founder_exist(BFounder&, const string&);
    bool _is_proposal_exist(BProposal&, const string&);

    bool _is_deployer(const string&);
    bool _is_founder(const string&);
    bool _is_president(const string&);

    bool _scan_founder(xchain::json&, const string& ="");
    bool _scan_proposal(xchain::json&, const string& ="");

    bool _add_founder(const string&,const string&,const string&);
    bool _add_proposal(const string&,const string&,const string&,const string&);

    bool _delete_founder_record(const string&);
    bool _delete_proposal_record(const string&);

    bool _clear_founder();
    bool _clear_proposal();

    bool _transfer(const string&,const string&);

public:
    //对外的辅助接口

    void initialize();              //合约部署者
    void get_deployer();            //合约部署者，基金会成员。
    bool is_deployer();             //任意身份，判断自己是否是合约部署者

    //update无对应函数

    //所有的list函数，尽可能key:value中的value不为空，缩小scan范围，提高效率

    //申请成为基金会成员
    void apply_founder();           //用户,法师，寺院，合约部署者也可以
    void approve_founder();         //合约部署者
    void recusal_founder();         //合约部署者
    bool is_founder();              //所有角色，判断自己是否是基金会成员
    bool is_president();            //所有角色，判断自己是否是会长
    void list_founder();            //合约部署者，基金会成员，根据id查所有，id可为空，安全，

    //提案
    void make_proposal();           //基金会成员
    void delete_proposal();         //基金会成员
    void update_proposal();         //基金会成员
    void approve_proposal();        //基金会成员
    //void recusal_proposal();        //基金会成员
    void find_proposal();           //基金会成员
    void list_proposal();           //基金会成员

};
#endif // _MAIN_H_