#include<iostream>
//
//operator reload test
class MyClass{
public:
    static int st;
    int x;
    MyClass() {};
    MyClass(int val):x(val){};
    MyClass operator + (const MyClass&);
    MyClass& operator = (const MyClass&);
    bool IsSelf(MyClass& a);

    int get(){return x;};
};

//function reload test
int sum(int a, int b);
double sum(double a, double b);

//template test
template <class T, int M>
T Tsum (T a, T b){
    return (a+b)*M;
}




