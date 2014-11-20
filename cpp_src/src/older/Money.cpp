/*Date:Thu Dec 19 09:37:53 CST 2013
 *Author:haiy
 *Description: The very odd part is how to change the digit strings
 *             into float digits.
 * */
#include <iostream> 
#include <cstdlib>
#include <cctype>

using namespace std;

class Money
{
public:
    friend Money add(Money account1, Money account2);
    friend bool equal(Money account1, Money account2);
    friend Money operator +(const Money& amount1, const Money& amount2);
    friend bool operator ==(const Money& amount1, const Money& amount2);

    Money(long dolloars, int cents);
    Money(long dolloars);
    Money();

    double get_value();

    void input(istream& ins);
    void output(ostream& outs);

private:
    long all_cents;
};

int digit_to_int(char c);

int main()
{
    Money your_amount, my_amount(10, 9), our_amount;
    cout << "Enter an amount of money: ";
    your_amount.input(cin);
    cout << "Your amount is :";
    my_amount.output(cout);
    cout << endl;

    if (equal(your_amount, my_amount))
    {
        cout << "We have the same amounts.\n";
    }
    else
    {
        cout << "One of us is richer!\n";
    }

    our_amount = add(your_amount, my_amount);
    your_amount.output(cout);
    cout << " + ";
    my_amount.output(cout);
    cout << " equals " ;
    our_amount.output(cout);
    cout << endl;

    Money cost(1, 50), tax(0, 15), total;
    total = cost + tax;

    cout << "cost = ";
    cost.output(cout);
    cout << endl;

    cout << "tax = ";
    cost.output(cout);
    cout << endl;

    cout << "total bill = ";
    total.output(cout);
    cout << endl;

    if (cost == tax)
    {
        cout << "Move to another stat.\n";
    }
    else
    {
        cout << "Things seems normal.\n";
    }
    return 0;
}

Money add(Money amount1, Money amount2)
{
    Money tmp;

    tmp.all_cents =  (amount1.all_cents + amount2.all_cents);
    return tmp;
}

bool equal(Money amount1, Money amount2)
{
    return (amount1.all_cents == amount2.all_cents);
}

Money::Money(long dolloars, int cents)
{
    if (dolloars*cents < 0)
    {
        cout << "Illigal input .\n";
        exit(1);
    }
    all_cents = dolloars*100 + cents;
}

Money::Money(long dolloars)
{
    if (dolloars < 0)
    {
        cout << "Illigal input .\n";
        exit(1);
    }
    all_cents = dolloars*100 ;
}

Money::Money():all_cents(0)
{}

double Money::get_value()
{
    return all_cents;
}

void Money::input(istream& ins)
{
    char one_char, decimal_point, digit1, digit2;
    long dollars;
    int cents;
    bool negative;

    ins >> one_char;
    if (one_char == '-')
    {
        negative = true;
        ins >> one_char;
    }
    else
    {
        negative = false;
    }
    ins >> dollars >> decimal_point >> digit1 >> digit2;
    cout << "Input :" << dollars << decimal_point << digit1 
        << digit2;
    cout << endl;

    if ( (one_char != '$' || decimal_point != '.') 
        || !isdigit(digit1) || !isdigit(digit2) )
    {
        cout << "Error illigal input form for money input\n";
        exit(1);
    }

    cents = digit_to_int(digit1)*10 + digit_to_int(digit2);

    all_cents = dollars*100 + cents;
    if (negative)
    {
        all_cents = -all_cents;
    }
}

void Money::output(ostream& outs)
{
    long positive_cents, dollars, cents;
    positive_cents = labs(all_cents);
    dollars = positive_cents/100;
    cents = positive_cents%100;

    if(all_cents < 0)
    {
        outs << "-$" << dollars << "." ;
    }
    else
    {
        outs << "$" << dollars << ".";
    }

    if (cents <= 10)
    {
        outs << "0";
    }
    outs << cents;
}

int digit_to_int(char c)
{
    return ( static_cast<int>(c) - static_cast<int>('0') );
}

Money operator +(const Money& amount1, const Money& amount2)
{
    Money tmp;
    tmp.all_cents = amount1.all_cents + amount2.all_cents;
    return tmp;
}

bool operator ==(const Money& amount1, const Money& amount2)
{
    return (amount1.all_cents == amount2.all_cents);
}

