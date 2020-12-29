#include <iostream>
#include "getMin.hpp"
#include "getMax.hpp"
#include "getMinMax.hpp"
#include "getSum.hpp"
#include "demonstrateStrings.hpp"

int main()
{
    std::cout << "simple integers" << std::endl;
    std::cout << "max " << getMax(1, 2) << std::endl;
    std::cout << "min " << getMin(1, 2) << std::endl;
    std::cout << "add " << getSum(1, 2) << std::endl;

    std::cout << "array of integers" << std::endl;
    int arr[]{1, 2, 3, 4, 5};
    std::cout << "sum " << getSum(arr, 5) << std::endl;
    std::cout << "max " << getMax(arr, 5) << std::endl;
    auto result = getMinMax(arr, 5);
    std::cout << "minmax " << result.first << ":" << result.second << std::endl;

    // following doesn't work - needs same type!
    // std::cout << max(1, 2.0) << std::endl;
    // but we can do this:
    std::cout << std::endl << "specify float " << getMax<float>(1, 2.3) << std::endl;

    // can also create a pointer to the method:
    double (*m)(double, double) = getMax;
    std::cout << "method constructed by pointer " << m(2.5, 2) << std::endl;

    std::cout << std::endl << "using non-type template arguments to specify array size: " << std::endl;
    // using non-type template arguments to omit the arrSize variable
    int arr2[]{1, 2, 3, 4, 5};
    std::cout << "sum " << getSum(arr2) << std::endl;
    std::cout << "max " << getMax(arr2) << std::endl;
    auto result2 = getMinMax(arr2);
    std::cout << "minmax " << result2.first << ":" << result2.second << std::endl;

    demonstrateStrings();

    return 0;
}