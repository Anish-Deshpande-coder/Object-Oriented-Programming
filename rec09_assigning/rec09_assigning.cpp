#include <iostream>
using namespace std;

class Base {
public:
    void display() const { cout << "Base class\n"; }
};

class Derived : public Base {
public:
    void display() const { cout << "Derived class\n"; }
};

int main() {
    Base base;
    Derived derived;
    Base* basePtr = nullptr;
    Derived* derivedPtr = nullptr;
    Base baseVar = derived;
    // derived = base;
    derivedPtr = nullptr;
    basePtr = derivedPtr;
    basePtr = &base;
    derivedPtr = &derived;
    basePtr = &derived;
    // derivedPtr = &base;
    if (basePtr) basePtr->display();
    if (derivedPtr) derivedPtr->display();

    return 0;
}