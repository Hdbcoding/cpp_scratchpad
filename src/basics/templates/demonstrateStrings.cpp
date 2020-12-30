#include <iostream>
#include "getMin.hpp"
#include "getMax.hpp"
#include "getMinMax.hpp"
#include "getSum.hpp"
#include "printArray.hpp"
#include "demonstrateStrings.hpp"

void demonstrateStrings() {
    std::cout << std::endl << "operations on c style strings" << std::endl;

    const char *b{"BCD"};
    const char *a{"ABC"};

    std::cout << "operating on: " << a << "; " << b << std::endl;
    std::cout << "min: " << getMin(a, b) << std::endl;
    std::cout << "max: " << getMax(a, b) << std::endl;
    // didnt implement sum for const char * yet
    // std::cout << "sum: " << getSum(a, b) << std::endl;

    std::cout << "operations on arrays of c-style strings" << std::endl;
    const char *arr[] {"EFG", "DEF", "CDE", "BCD", "ABC"};
    printArray(arr);
    std::cout << "sum " << getSum(arr) << std::endl;
    std::cout << "min " << getMin(arr) << std::endl;
    std::cout << "max " << getMax(arr) << std::endl;
    auto result3 = getMinMax(arr);
    std::cout << "minmax " << result3.first << ":" << result3.second << std::endl;

    std::cout << std::endl << "operations on c++ stl strings" << std::endl;
    std::string strA{"ABC"};
    std::string strB{"BCD"};
    std::cout << "operating on: " << strA << "; " << strB << std::endl;
    std::cout << "min " << getMin(strA, strB) << std::endl;
    std::cout << "max " << getMax(strA, strB) << std::endl;
    std::cout << "sum " << getSum(strA, strB) << std::endl;

    std::cout << "operations on arrays of c++ stl strings" << std::endl;
    std::string arr2[5] {"EFG", "DEF", "CDE", "BCD", "ABC"};
    printArray(arr2);
    std::cout << "sum " << getSum(arr2) << std::endl;
    std::cout << "max " << getMin(arr2) << std::endl;
    std::cout << "max " << getMax(arr2) << std::endl;
    auto result4 = getMinMax(arr2);
    std::cout << "minmax " << result4.first << ":" << result4.second << std::endl;

}