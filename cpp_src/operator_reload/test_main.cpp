#include<iostream>
#include "test_lib.h"

using namespace std;

void  operator_reload_test(){
    //operator reload test
    int a(5);
    MyClass test1(a);
    MyClass test2(4);
    MyClass res;
    //res = test1 + test2;
    std::cout << res.x << "= " << test1.x << " + " << test2.x << endl;
    MyClass& res_ref = res;
    std::cout << "here !!" << endl;

    std::cout << res.IsSelf(res) << ":" << res.IsSelf(res_ref) << endl;
    MyClass test_ref = res;
    std::cout << "Check if self is the same : " << test_ref.IsSelf(res) << res.IsSelf(test_ref) << endl;
}

void function_reload_test(){
    std::cout << "Int result " << sum(4,5) << endl;
    std::cout << "Double result " << sum(2.0,5.0) << endl;
}

void template_test(){
    std::cout << "=============\nTemplate test!" << endl;
    std::cout << "Int result " << Tsum<int, 3>(4,5) << endl;
    std::cout << "Double result" << Tsum<double, 3>(2.0,5.0) << endl;
    //std::cout << "Int result " << Tsum(4,5) << endl;
    //std::cout << "Double result " << Tsum(2.0,5.0) << endl;
}

void static_test(){

}
int main(){
    //operator_reload_test();
    function_reload_test();
    template_test();

    return 0;
}
