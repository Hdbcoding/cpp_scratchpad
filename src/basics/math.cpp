#include <iostream>

int add(int x, int y){
    std::cout << "Adding " << x << " and " << y << std::endl;
    int result {x + y};
    std::cout << "Result: " << result;
    return result;
}