#include "test_lib.h"

using namespace std;

MyClass MyClass::operator+ (const MyClass& m){
    MyClass tmp;
    tmp.x = m.x + x;
    return tmp;
}

bool MyClass::IsSelf(MyClass& TestObject){
    return (&TestObject == this);
}

MyClass& MyClass::operator = (const MyClass& para){
    x = para.x;
    return *this;
}

int sum(int a, int b){
    return a+b;
}

double sum(double a, double b){
    return a+b;
}

int MyClass::st = 5;


