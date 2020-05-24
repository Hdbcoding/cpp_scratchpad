#include <iostream>
#include "functions.h"

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

    int a{3};
    int b{5};
    int *ap = &a;
    int *bp = &b;

    swap(ap, bp);

    std::cout << "Value of a should now be 5: " << a << std::endl;
    std::cout << "Value of b should now be 3: " << b << std::endl;

    int r = 0;
    int *rp = &r;
    int r2 = add(ap, bp);
    add(ap, bp, rp);

    std::cout << "Should get same value for r " << r << " and r2 " << r2 << std::endl;

    int fa = 1;
    int *fap = &fa;
    factorial(ap, fap);
    int fb = 1;
    int *fbp = &fb;
    factorial(bp, fbp);

    std::cout << "Factorial for a: " << fa << ", and b: " << fb << std::endl;

    std::cout << "don't need to explicitly declare a pointer variable" << std::endl;
    int z{10}, y{5};
    swap(&z, &y);
    std::cout << "z: " << z << ", y: " << y << std::endl;

    return 0;
}