#include <functional>

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
