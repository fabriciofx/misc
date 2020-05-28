#include <iostream>

using namespace std;

class Base {
private:
    int x = 2;
public:
    Base() {
        cout << "Calling Base constructor\n";       
    }
    virtual ~Base() {
        cout << "Calling Base destructor\n";       
    }
};

class Derivated : public Base {
private:
    int y = 3;
public:
    Derivated() {
        cout << "Calling Derivated constructor\n";       
    }
    ~Derivated() {
        cout << "Calling Derivated destructor\n";       
    }
};


int
main(void)
{
    Derivated *d = new Derivated();
    delete d;
    cout << "-------------------------\n";
    Base *b = new Derivated();
    delete b;
    return 0;
}
