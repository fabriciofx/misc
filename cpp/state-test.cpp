#include <functional>
#include <iostream>

// https://stackoverflow.com/questions/48066747/c-recursive-function-type
class StateFn
{
public:
    StateFn() {}
    template<class T>
    StateFn(T&& state) : func(std::forward<T>(state)){}
    operator bool() { return (bool)func; }
    StateFn operator()() { return func(); }

private:
    std::function<StateFn()> func;
};

// What I'd like to make it
class Foo
{
public:
    Foo() {}
    StateFn m1();
    StateFn m2();
    StateFn m3();
};

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

// What I'd like to make it
StateFn Foo::m3()
{
    std::cout << "m3()\n";
    return {};
}

StateFn Foo::m2()
{
    std::cout << "m2()\n";
    return Foo::m3();
}

StateFn Foo::m1()
{
    std::cout << "m1()\n";
    return Foo::m2();
}

int
main() {
    StateFn state { stateStart };
    while (state) {
        state = state();
    }

    // What I'd like to make
    StateFn state2 { Foo::m1 };
    while (state2) {
        state2 = state2();
    }
}
