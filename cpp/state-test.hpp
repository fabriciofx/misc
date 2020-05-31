#include <functional>

// https://stackoverflow.com/questions/48066747/c-recursive-function-type
class state
{
public:
    state() {}
    template<class T>
    state(T&& t) : f(std::forward<T>(t)){}
    operator bool() { return (bool)f; }
    state operator()() { return f(); }

private:
    std::function<state()> f;
};
