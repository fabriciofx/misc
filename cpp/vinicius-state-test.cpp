// Solution provided by Vinicius Souza @cppbrasil
#include <functional>

// https://stackoverflow.com/questions/48066747/c-recursive-function-type
class StateFn
{
public:
    StateFn() {};
    template<class T>
    StateFn(T&& state) : func(std::forward<T>(state)){}
    operator bool() { return (bool)func; }
    StateFn operator()() { return func(); }

private:
    std::function<StateFn()> func;
};

// What I'd like to make
class Foo
{
public:
    explicit Foo(int x) : x(x) {}
    StateFn m1();
    StateFn m2();
    StateFn m3();

private:
    int x{0};
};


// c++ -O3 -g state-test.cpp -o state-test
#include <iostream>
//#include "state-test.hpp"

// It works
StateFn stateEnd()
{
    std::cout << "end\n";
    return {};
}
StateFn stateTransit()
{
    std::cout << "transit\n";
    return stateEnd;
}

StateFn stateStart()
{
    std::cout << "start\n";
    return stateTransit;
}

// What I'd like to make
StateFn Foo::m3()
{
    x += 2;
    std::cout << "m3() " << x << '\n';
    return {};
}

StateFn Foo::m2()
{
    std::cout << "m2()\n";
    x *= 4;
    return Foo::m3();
}

StateFn Foo::m1()
{
    std::cout << "m1()\n";
    x += 10;
    return Foo::m2();
}

int main() {
    StateFn state { stateStart };
    while (state) {
        state = state();
    }

    Foo foo{0};
    StateFn state2 {
        [&]() {
            return foo.m1();
        }
    };
    while (state2) {
        state2 = state2();
    }
}
