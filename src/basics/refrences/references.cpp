#include <iostream>
#include "functions.h"

int main(){
    using namespace std;

    int x{10};
    int &ref{x};

    cout << "x: " << x << ", ref: " << ref << endl;

    int y{20};
    ref = y;

    cout << "x: " << x << ", ref: " << ref << endl;

    cout << "x address: " << &x << ", ref address: " << &ref << endl;

    add(3, 5, ref);
    cout << "3 + 5 = " << x << endl;

    int &ref2{y};

    cout << "before swap " << x << ", " << y << endl;

    swap(ref, ref2);

    cout << "after swap " << x << ", " << y << endl;

    factorial(5, ref);
    cout << "should be 120: " << x << endl;
}