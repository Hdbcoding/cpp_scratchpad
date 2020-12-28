#include <iostream>
#include <cstring>
#include <string>

#pragma region max

template <typename T>
T max(T x, T y)
{
    return x > y ? x : y;
}

// // explicit specialization
// template <>
// const char *max(const char *x, const char *y)
// {
//     return strcmp(x, y) > 0 ? x : y;
// }

// max for an array with array size specified
template <typename T>
T max(T *arr, int arrSize)
{
    T result{arr[0]};
    for (int i = 1; i < arrSize; ++i)
    {
        result = max(result, arr[i]);
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
        result = max(result, arr[i]);
    }
    return result;
}

#pragma endregion min

#pragma region min

template <typename T>
T min(T x, T y)
{
    return x > y ? y : x;
}

// template <>
// const char *min(const char *x, const char *y)
// {
//     return strcmp(x, y) < 0 ? x : y;
// }

#pragma endregion min

#pragma region minmax

template <typename T>
std::pair<T, T> minMax(T *arr, int arrSize)
{
    std::pair<T, T> result{arr[0], arr[0]};

    for (int i = 1; i < arrSize; ++i)
    {
        result.first = min(result.first, arr[i]);
        result.second = max(result.second, arr[i]);
    }

    return result;
}

template <typename T, int size>
std::pair<T, T> minMax(T (&arr)[size])
{
    std::pair<T, T> result{arr[0], arr[0]};

    for (int i = 1; i < size; ++i)
    {
        result.first = min(result.first, arr[i]);
        result.second = max(result.second, arr[i]);
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

// template <>
// const char *add(const char *x, const char *y)
// {
//     // with c-style strings, I'm doing dynamic memory allocation to add the strings!
//     char *result = (char *)malloc((strlen(x) + strlen(y)) * sizeof(char));
//     strcpy(result, x);
//     strcat(result, y);
//     return result;
// }

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

// // due to dynamic memory allocation, summing array of strings requires a little extra work
// template<int size>
// const char * sum(const char *(&arr)[size])
// {
//     char *result = (char *)malloc(size * sizeof(char));
//     strcpy(result, arr[0]);
//     char *temp{};
//     for (int i = 1; i < size; ++i)
//     {
//         temp = result;
//         result = (char *)add<const char *>(result, arr[i]);
//         free(temp);
//     }
//     return result;
// }

#pragma endregion add



int main()
{
    std::cout << "max " << max(1, 2) << std::endl;
    std::cout << "min " << min(1, 2) << std::endl;
    std::cout << "add " << add(1, 2) << std::endl;

    int arr[]{1, 2, 3, 4, 5};
    std::cout << "sum " << sum(arr, 5) << std::endl;
    std::cout << "max " << max(arr, 5) << std::endl;
    auto result = minMax(arr, 5);
    std::cout << "minmax " << result.first << ":" << result.second << std::endl;

    // following doesn't work - needs same type!
    // std::cout << max(1, 2.0) << std::endl;
    // but we can do this:
    std::cout << "specify float " << max<float>(1, 2.3) << std::endl;

    // can also create a pointer to the method:
    double (*m)(double, double) = max;
    std::cout << "method constructed by pointer " << m(2.5, 2) << std::endl;

    // the following only prints the correct result because of the explicit specialization for const char *
    const char *b{"B"};
    const char *a{"A"};
    auto s = max(a, b);
    std::cout << "max of " << a << " and " << b << ": " << s << std::endl;

    std::cout << "using non-type template arguments to specify array size: " << std::endl;
    // using non-type template arguments to omit the arrSize variable
    int arr2[]{1, 2, 3, 4, 5};
    std::cout << "sum " << sum(arr2) << std::endl;
    std::cout << "max " << max(arr2) << std::endl;
    auto result2 = minMax(arr2);
    std::cout << "minmax " << result2.first << ":" << result2.second << std::endl;

    const char *arr3[]{"E", "D", "C", "B", "A"};
    std::cout << "sum " << sum(arr3) << std::endl;
    std::cout << "max " << max(arr3) << std::endl;
    auto result3 = minMax(arr3);
    std::cout << "minmax " << result3.first << ":" << result3.second << std::endl;

    // // all of a sudden, if I add a test case for std::string, I can't compile because the templates are ambiguous
    // std::string arr4[5] {"E", "D", "C", "B", "A"};
    // std::cout << "sum " << sum(arr4) << std::endl;
    // std::cout << "max " << max(arr4) << std::endl;
    // auto result4 = minMax(arr4);
    // std::cout << "minmax " << result4.first << ":" << result4.second << std::endl;


    return 0;
}