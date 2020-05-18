#include <iostream>

int main(){
    int x{10};
    std::cout << "value of x: " << x << std::endl;
    std::cout << "location of x: " << &x << std::endl;

    int *p = &x;

    std::cout << "value of pointer: " << p << std::endl;
    // dereference operator
    // gives read and write access to x!
    std::cout << "value at pointer: " << *p << std::endl;

    // uninitialized pointer
    int *p2 = nullptr;
    // can't read from or write to a null pointer
    // std::cout << *p2 << std::endl;
    p2 = &x;
    std::cout << "value of pointer: " << p2 << std::endl;
    std::cout << "value at pointer: " << *p2 << std::endl;

    return 0;
}