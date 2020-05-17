#include <iostream>
// reference to a header file
#include "math.h"

int main() {
    int x, y;
    std::cout << "Enter two numbers: " << std::endl;
    // in the console, the two inputs should be separated by spaces
    std::cin >> x >> y;
    // function must be declared before it is used - doesn't necessarily have to be defined yet
    int result{add(x, y)};
    return 0;
}