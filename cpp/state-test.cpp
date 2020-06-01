#include <iostream>
#include "state-test.hpp"

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

int
main() {
    StateFn state { stateStart };
    while (state) {
        state = state();
    }
}
