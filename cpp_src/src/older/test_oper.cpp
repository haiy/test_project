#include <iostream>

class Money
{
public:
    friend Money operator + (const Money& mine, const Money& yours);
    Money(int money);
    int get_money();
private:
    int m;
};

int main()
{
    using namespace std;
    Money my_money(5);
    cout << "I have " << my_money.get_money() << endl;
    Money your_money(5);
    cout << "You have " << your_money.get_money() << endl;
    Money sum = your_money + my_money ;
    cout << "we have " << sum.get_money() << endl;
}

Money::Money (int money)
{
    m = money;
}


int Money::get_money()
{
    return m;
}

Money operator + (const Money& mine, const Money& yours)
{
    Money sum(0);
    sum.m = mine.m + yours.m;
    return sum;
}
