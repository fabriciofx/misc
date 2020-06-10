#include <functional>
#include <string>
#include <iostream>

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

class Foo
{
public:
    Foo(std::string input) {_input = input; }
    void run();
    StateFn start();
    StateFn m1();
    StateFn m2();
    StateFn m3();

private:
    std::string _input;
};

StateFn Foo::m1()
{
    std::cout  << "m1()\n";
    return [this] { return this->start(); };
}

StateFn Foo::m3()
{
    std::cout  << "m3()\n";
    return {};
}

StateFn Foo::m2()
{
    std::cout  << "m2()\n";
    return [this] { return this->m3(); };
}

StateFn Foo::start()
{
    std::cout  << "start()\n";
    char chr = _input[0];
    if (chr == 'A') return [this] { return this->m2(); };
    else return [this] { return this->m1(); };
}

void Foo::run()
{
    std::cout  << "run()\n";
    StateFn state{[&]{ return this->start(); }};
    while (state = state());
}

int
main()
{
    Foo foo("ABC");
    foo.run();
    return 0;
}
