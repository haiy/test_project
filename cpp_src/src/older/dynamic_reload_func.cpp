#include <iostream>

int test_reload_func(int arg1)
{
    return arg1;
}

int test_reload_func(int arg1, int arg2)
{
    return arg1+arg2;
}

int main()
{
using namespace std;
    cout << test_reload_func(4) << endl;
    cout << test_reload_func(4,5) << endl;
    return 0;

}
