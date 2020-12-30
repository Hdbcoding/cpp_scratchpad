#include <iostream>
#include "getMin.hpp"
#include "getMax.hpp"
#include "getMinMax.hpp"
#include "getSum.hpp"
#include "printArray.hpp"
#include "demonstrateInts.hpp"

void demonstrateInts()
{
    std::cout << "simple integers" << std::endl;
    std::cout << "max " << getMax(1, 2) << std::endl;
    std::cout << "min " << getMin(1, 2) << std::endl;
    std::cout << "add " << getSum(1, 2) << std::endl;

    std::cout << "array of integers" << std::endl;
    int arr[]{1, 2, 3, 4, 5};
    printArray(arr);
    std::cout << "sum " << getSum(arr, 5) << std::endl;
    std::cout << "min " << getMin(arr, 5) << std::endl;
    std::cout << "max " << getMax(arr, 5) << std::endl;
    auto result = getMinMax(arr, 5);
    std::cout << "minmax " << result.first << ":" << result.second << std::endl;

    std::cout << std::endl << "integers - using non-type template arguments to specify array size: " << std::endl;
    // using non-type template arguments to omit the arrSize variable
    int arr2[]{1, 2, 3, 4, 5};
    printArray(arr2);
    std::cout << "sum " << getSum(arr2) << std::endl;
    std::cout << "max " << getMax(arr2) << std::endl;
    auto result2 = getMinMax(arr2);
    std::cout << "minmax " << result2.first << ":" << result2.second << std::endl;
}