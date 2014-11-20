#include <iostream>
#include <cmath>
#include <cstdlib>

using namespace std;

class BankAccount
{
public:
    BankAccount(int dollars, int cents, double rate);
    BankAccount(int dollars, double rate);
    BankAccount();

    void set(int dollars, int cents, double rate);
    void set(int dollars, double rate);

    void update();
    double get_balance();
    double get_rate();
    void output(ostream& outs);

private:
    int dollars_part;
    int cents_part;
    double interest_rate;

    double fraction(double percent);
    double percent(double fraction_value);
};

class SavingsAccount : public BankAccount
{
public:
    SavingsAccount(int dollars, int cents, double rate);
    void deposit(int dollars, int cents);
    void withdraw(int dollars, int cents);
private:
};

int main()
{
    SavingsAccount account(100, 50, 5.5);
    account.output(cout);
    cout << endl;
    cout << "Despositing $10.25." << endl;
    account.deposit(10, 25);
    account.output(cout);
    cout << endl;

    cout << "Withdrawing $11.80." << endl;
    account.withdraw(11, 80);
    account.output(cout);
    cout << endl;
    return 0;
}


BankAccount::BankAccount(int dollars, int cents, double rate)
{
    if ( (dollars < 0) || (cents < 0) || (rate < 0) )
    {
        cout << "Input Error!\n";
        exit(1);
    }
    dollars_part = dollars;
    cents_part = cents;
    interest_rate = rate;
}
BankAccount::BankAccount(int dollars, double rate)
{
    if ( (dollars < 0) || (rate < 0) )
    {
        cout << "Input Error!\n";
        exit(1);
    }
    dollars_part = dollars;
    interest_rate = rate;
}

BankAccount::BankAccount():dollars_part(0), cents_part(0), interest_rate(0.0)
{}

void BankAccount::set(int dollars, int cents, double rate)
{
    if ( (dollars < 0) || (cents < 0) || (rate < 0) )
    {
        cout << "Input Error!\n";
        exit(1);
    }
    dollars_part = dollars;
    cents_part = cents;
    interest_rate = rate;
}
void BankAccount::set(int dollars, double rate)
{
    if ( (dollars < 0) || (rate < 0) )
    {
        cout << "Input Error!\n";
        exit(1);
    }
    dollars_part = dollars;
    interest_rate = rate;
}
void BankAccount::update()
{
    double balance = get_balance();
    balance = balance + interest_rate*balance;
    dollars_part = floor(balance);
    cents_part = floor( (balance - dollars_part)*100 );
}
double BankAccount::get_balance()
{
    return (dollars_part + 0.01*cents_part);
}
double BankAccount::get_rate()
{
    return interest_rate;
}
void BankAccount::output(ostream& outs)
{
    outs.setf(ios::fixed);
    outs.setf(ios::showpoint);
    outs.precision(2);
    outs << "Accout Balance is $ " << get_balance() << endl;
    outs << "Interest rate :" << get_rate() << "%" << endl;
}

double BankAccount::fraction(double percent)
{
    return (percent/100.00);
}
double BankAccount::percent(double fraction_value)
{
    return (fraction_value*100);
}

SavingsAccount::SavingsAccount(int dollars, int cents, double rate):BankAccount(dollars, cents, rate)
{
}

void SavingsAccount::deposit(int dollars, int cents)
{
    double balance = get_balance();
    balance += dollars;
    balance += (static_cast<double>(cents) / 100);
    int new_dollars = static_cast<int>(balance);
    int new_cents = static_cast<int>((balance - new_dollars) * 100);
    set(new_dollars, new_cents, get_rate());
}

void SavingsAccount::withdraw(int dollars, int cents)
{
    double balance = get_balance();
    balance -= dollars;
    balance -= (static_cast<double>(cents) / 100);
    int new_dollars = static_cast<int>(balance);
    int new_cents = static_cast<int>((balance - new_dollars) * 100);
    set(new_dollars, new_cents, get_rate());
}
