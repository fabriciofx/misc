#include <iostream>

class A {
public:
    std::string m1() { return "I'm in A::m1()"; }
};

class B {
public:
    void m2(A a) { std::cout << a.m1() << std::endl; }
};

int main(void)
{
    A a;
    B b;
    b.m2(a);
    return 0;
}
