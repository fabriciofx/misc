#include <iostream>

enum class X{X1};
enum class Y{Y1};


template <class T>
struct A{
    A(T&& t):t{t}{}

    void f() {
        std::cout << static_cast<int>(t) << '\n';
    }

private:
    T t;
};

int main(){
    A x{X::X1};
    A y{Y::Y1};

    x.f();
    y.f();
}