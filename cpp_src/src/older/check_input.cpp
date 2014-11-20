#include <iostream>
using namespace std;

void new_line();
//drop all the input after the line
//为什么需要这个函数呢？
//
void get_int(int& number);
//assign the value for number 
//ensure a correct input

int main()
{
    int n;
    get_int(n);
    cout << "Final get the value " << n << endl
         << "End of demonstration. \n";
    return 0;
}

void new_line()
{
    char symbol;
    do
    {
        cin.get(symbol);
        //cout << "Get symbol :" << symbol << endl;
    }while(symbol != '\n');
}

void get_int(int& number)
{
    char ans;
    do
    {
        cout << "Please input your number :\n";
        cin >> number;
        cout << "You have input :" << number << endl 
            << "Is that correct ? [Y/N] " << endl;
        cin >> ans;
        cout << "Your answer is :" << ans << endl;
        new_line();
        //如果没有这个new_line函数，那么程序就会陷入
        //死循环，为什么会陷入死循环呢？因为按照流输入的
        //时候，前面的数据没有流动就会一直在，所以
        //number传入的就会一直是一个值
    }while( ans != 'Y' and  ans != 'y');
}
