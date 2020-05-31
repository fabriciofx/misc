#include <iostream>
#include "state-test.hpp"

state stateEnd()
{
    std::cout << "end\n";
    return {};
}
state stateTransit()
{
    std::cout << "transit\n";
    return stateEnd;
}

state stateStart()
{
    std::cout << "start\n";
    return stateTransit;
}


int main() {
    state s {stateStart};
    while(s = s());
}
