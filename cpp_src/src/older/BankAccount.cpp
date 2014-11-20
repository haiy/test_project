/*
 * Author:haiy
 * Date:Thu Dec 12 09:59:56 CST 2013
 * Description:
 * 函数重载是指函数名相同，但是输入参数的不同，包括个数，
 * 以及参数的类型来实现对相类似的操作进行处理，动态参数
 * 则是函数的输入参数的长度可变。
 * */

#include <iostream>
#include <cstdlib>
using namespace std;

class BankAccount
{
public:
    void set(int dollars, int cents, double rate);
    //将余额设置为double.cents，利率为rate 
    void set(int dollars, double rate);
    //后条件：将余额设置为dollars.00,利率为rate
    void update();
    //后条件：将一年的利率添加到账户上

    double get_balance();
    //返回账户当前余额
    double get_rate();
    //将当前账户的利率作为一个百分比返回
    void output(ostream& outs);
    //前条件：如果outs是一个文件输出流，那么其已经连接到一个文件
    //后条件：账户余额和利率写入outs流

private:
    double balance;
    double interest_rate;
    double fraction(double percent);
};

int main()
{
    BankAccount account1, account2;
    cout << "Start of Test:\n";
    account1.set(123, 99, 3.0);
    cout << "Account1 initial statement:\n";
    account1.output(cout);

    account1.set(100, 5.0);
    cout << "Account1 with new setup:\n";
    account1.output(cout);

    account1.update();
    cout << "Account1 after update:\n";
    account1.output(cout);

    account2 = account1;
    cout << "Account2 :\n";
    account2.output(cout);

    return 0;
}


void BankAccount::set(int dollars, int cents, double rate)
{
    if ( (dollars < 0 ) || (cents < 0) || (rate < 0) )
    {
        cout << "Illigal values for money or rate .\n";
        exit(1);
    }

    balance = dollars + 0.01*cents;
    interest_rate = rate;
}


void BankAccount::set(int dollars, double rate)
{
    if ( (dollars < 0 ) || (rate < 0) )
    {
        cout << "Illigal values for money or rate .\n";
        exit(1);
    }

    balance = dollars;
    interest_rate = rate;
}

void BankAccount::update()
{
    balance = balance + fraction(interest_rate)*balance;
}

double BankAccount::get_balance()
{
    return balance;
}

double BankAccount::get_rate()
{
    return interest_rate;
}

double BankAccount::fraction(double percent)
{
    if ( (percent < 0) || (percent > 100) )
    {
        cout << "percent input error!\n";
    }
    return (percent/100.00);
}
void BankAccount::output(ostream& outs)
{
    outs.setf(ios::fixed);
    outs.setf(ios::showpoint);
    outs.precision(2);
    outs << "Accounts balance $ " << balance << endl;
    outs << "Interest rate " << interest_rate << endl;
}
