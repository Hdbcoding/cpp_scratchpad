#include <iostream>
#include "getMax.hpp"
#include "demonstrateExplicitTypes.hpp"

void demonstrateExplicitTypes(){
    std::cout << "can explicitly specify type with <>" << std::endl;
    std::cout << "getMax(1, 1.2) is illegal because the compiler doesn't know what type you want" << std::endl;
    std::cout << "getMax<float>(1, 1.2) is ok: " << getMax<float>(1, 1.2) << std::endl;

    std::cout << "can also construct a method pointer to specify the type: double (*m)(double, double) = getMax" << std::endl;
    double (*m)(double, double) = getMax;
    std::cout << "m(2.5, 2): " << m(2.5, 2) << std::endl;
}