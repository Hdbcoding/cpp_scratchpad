#include <iostream>
#include <cstring>
#include <string>

#pragma region max

template <typename T>
T getMax(T x, T y)
{
    return x > y ? x : y;
}

// // explicit specialization
template <>
const char *getMax(const char *x, const char *y)
{
    return strcmp(x, y) > 0 ? x : y;
}

// max for an array with array size specified
template <typename T>
T max(T *arr, int arrSize)
{
    T result{arr[0]};
    for (int i = 1; i < arrSize; ++i)
    {
        result = getMax(result, arr[i]);
    }
    return result;
}

// max for an array with array size specified by non-type argument
template <typename T, int size>
T max(T (&arr)[size])
{
    T result{arr[0]};
    for (int i = 1; i < size; ++i)
    {
        result = getMax(result, arr[i]);
    }
    return result;
}

#pragma endregion min

#pragma region min

template <typename T>
T getMin(T x, T y)
{
    return x > y ? y : x;
}

template <>
const char *getMin(const char *x, const char *y)
{
    return strcmp(x, y) < 0 ? x : y;
}

#pragma endregion min

#pragma region minmax

template <typename T>
std::pair<T, T> minMax(T *arr, int arrSize)
{
    std::pair<T, T> result{arr[0], arr[0]};

    for (int i = 1; i < arrSize; ++i)
    {
        result.first = getMin(result.first, arr[i]);
        result.second = getMax(result.second, arr[i]);
    }

    return result;
}

template <typename T, int size>
std::pair<T, T> minMax(T (&arr)[size])
{
    std::pair<T, T> result{arr[0], arr[0]};

    for (int i = 1; i < size; ++i)
    {
        result.first = getMin(result.first, arr[i]);
        result.second = getMax(result.second, arr[i]);
    }

    return result;
}

#pragma endregion minmax

#pragma region add

template <typename T>
T add(T x, T y)
{
    return x + y;
}

template <typename T>
T sum(T *arr, int arrSize)
{
    T result{arr[0]};
    for (int i = 1; i < arrSize; ++i)
    {
        result = add(result, arr[i]);
    }
    return result;
}

template <typename T, int size>
T sum(T (&arr)[size])
{
    T result{arr[0]};
    for (int i = 1; i < size; ++i)
    {
        result = add(result, arr[i]);
    }
    return result;
}

// due to dynamic memory allocation, summing array of strings requires a little extra work
template <int size>
const char *sum(const char *(&arr)[size])
{
    int totalSize = 0;
    for (int i = 0; i < size; ++i)
    {
        totalSize += strlen(arr[i]);
    }

    char *result = (char *)malloc(totalSize * sizeof(char));
    for (int i = 0; i < size; ++i)
    {
        strcat(result, arr[i]);
    }
    return result;
}

#pragma endregion add

int main()
{
    std::cout << "simple integers" << std::endl;
    std::cout << "max " << getMax(1, 2) << std::endl;
    std::cout << "min " << getMin(1, 2) << std::endl;
    std::cout << "add " << add(1, 2) << std::endl;

    std::cout << "array of integers" << std::endl;
    int arr[]{1, 2, 3, 4, 5};
    std::cout << "sum " << sum(arr, 5) << std::endl;
    std::cout << "max " << max(arr, 5) << std::endl;
    auto result = minMax(arr, 5);
    std::cout << "minmax " << result.first << ":" << result.second << std::endl;

    // following doesn't work - needs same type!
    // std::cout << max(1, 2.0) << std::endl;
    // but we can do this:
    std::cout << "specify float " << getMax<float>(1, 2.3) << std::endl;

    // can also create a pointer to the method:
    double (*m)(double, double) = getMax;
    std::cout << "method constructed by pointer " << m(2.5, 2) << std::endl;

    // the following only prints the correct result because of the explicit specialization for const char *
    const char *b{"BCD"};
    const char *a{"ABC"};
    auto s = getMax(a, b);
    std::cout << "max of " << a << " and " << b << ": " << s << std::endl;

    std::cout << "using non-type template arguments to specify array size: " << std::endl;
    // using non-type template arguments to omit the arrSize variable
    int arr2[]{1, 2, 3, 4, 5};
    std::cout << "sum " << sum(arr2) << std::endl;
    std::cout << "max " << max(arr2) << std::endl;
    auto result2 = minMax(arr2);
    std::cout << "minmax " << result2.first << ":" << result2.second << std::endl;

    std::cout << "array of c-style strings" << std::endl;
    const char *arr3[]{"EFG", "DEF", "CDE", "BCD", "ABC"};
    std::cout << "sum " << sum(arr3) << std::endl;
    std::cout << "max " << max(arr3) << std::endl;
    auto result3 = minMax(arr3);
    std::cout << "minmax " << result3.first << ":" << result3.second << std::endl;

    // // all of a sudden, if I add a test case for std::string, I can't compile because the templates are ambiguous
    std::cout << "c++ strings" << std::endl;
    std::string strA{"ABC"};
    std::string strB{"BCD"};
    std::cout << "sum " << add(strA, strB) << std::endl;
    // add is ok, but min/max cause issues
    std::cout << "min " << getMin(strA, strB) << std::endl;
    std::cout << "max " << getMax(strA, strB) << std::endl;

    std::string arr4[5] {"EFG", "DEF", "CDE", "BCD", "ABC"};
    std::cout << "sum " << sum(arr4) << std::endl;
    std::cout << "max " << max(arr4) << std::endl;
    auto result4 = minMax(arr4);
    std::cout << "minmax " << result4.first << ":" << result4.second << std::endl;

    // Current total output:
    // max 5
    // minmax 1:5
    // specify float 2.3
    // method constructed by pointer 2.5
    // max of ABC and BCD: BCD
    // using non-type template arguments to specify array size:
    // sum 15
    // max 5
    // minmax 1:5
    // array of c-style strings
    // sum
    // 2
    // �
    // ����������EFGDEFCDEBCDABC
    // max EFG
    // minmax ABC:EFG
    // c++ strings
    // sum ABCBCD
    // sum EFGDEFCDEBCDABC

    return 0;
}