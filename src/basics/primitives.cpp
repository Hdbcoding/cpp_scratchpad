#include <iostream>
#include <climits>
#include <cfloat>

int main(){
    bool b = false;
    int i = 0;
    // c++ 11 - uniform initialization
    int i2{42};
    char c = 'a';
    float f = 1.2345f;
    double d = 3.4567;
    int arr[5];
    int arr2[5] = {1, 2, 3, 4, 5};
    // c++ 11 feature - uniform initialization
    int arr3[5]{1, 2, 3, 4, 5};

    // max integer value from climits macro
    int max_int = INT_MAX;

    // max double value from cfloat macro
    double max_double = DBL_MAX;

    std::cout << "defined a bunch of primitives" << std::endl;

    return 0;
}