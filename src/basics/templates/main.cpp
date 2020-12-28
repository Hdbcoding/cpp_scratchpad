#include <iostream>
#include <cstring>
#include <string>

// primary template
template <typename T>
T max(T x, T y)
{
    return x > y ? x : y;
}

template <typename T>
T min(T x, T y)
{
    return x > y ? y : x;
}

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

// force compiler to generate a particular type of the above template method:
// explicit instantiation
template char max(char x, char y);
// template std::string max(std::string x, std::string y);

// explicit specialization

template <>
const char *max(const char *x, const char *y)
{
    return strcmp(x, y) > 0 ? x : y;
}
// template <>
// std::string max(std::string x, std::string y)
// {
//     return x > y > 0 ? x : y;
// }

template <>
const char *min(const char *x, const char *y)
{
    return strcmp(x, y) < 0 ? x : y;
}

template <>
const char *add(const char *x, const char *y)
{
    // with c-style strings, I'm doing dynamic memory allocation to add the strings!
    char *result = (char *)malloc((strlen(x) + strlen(y)) * sizeof(char));
    strcpy(result, x);
    strcat(result, y);
    return result;
}

// non type template arguments
// can declare a template as taking certain constant value arguments
template <int size>
void print()
{
    // size is const, so can declare arrays with it (not variable size!)
    char buffer[size];
    std::cout << size << std::endl;
}

// non type template argument to specify an array size
template <typename T, int size>
// replace raw T pointer with an array reference
T sum2(T (&arr)[size])
{
    T result{arr[0]};
    for (int i = 1; i < size; ++i)
    {
        result = add(result, arr[i]);
    }
    return result;
}

template <typename T, int size>
T max2(T (&arr)[size])
{
    T result{arr[0]};
    for (int i = 1; i < size; ++i)
    {
        result = max(result, arr[i]);
    }
    return result;
}

template <typename T, int size>
std::pair<T, T> minMax2(T (&arr)[size])
{
    std::pair<T, T> result{arr[0], arr[0]};

    for (int i = 1; i < size; ++i)
    {
        result.first = min(result.first, arr[i]);
        result.second = max(result.second, arr[i]);
    }

    return result;
}

// due to dynamic memory allocation, summing array of strings requires a little extra work
template<int size>
const char * sum2(const char *(&arr)[size])
{
    char *result = (char *)malloc(size * sizeof(char));
    strcpy(result, arr[0]);
    char *temp{};
    for (int i = 1; i < size; ++i)
    {
        temp = result;
        result = (char *)add<const char *>(result, arr[i]);
        free(temp);
    }
    return result;
}

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

    // constant value non-type template ok
    print<3>();
    const int cval{5};
    print<cval>();
    // non-const value not ok - the compiler needs to know the value of the non-type template argument
    // int val{5};
    // print<val>();

    std::cout << "using non-type template arguments to specify array size: " << std::endl;
    // using non-type template arguments to omit the arrSize variable
    int arr2[]{1, 2, 3, 4, 5};
    std::cout << "sum " << sum2(arr2) << std::endl;
    std::cout << "max " << max2(arr2) << std::endl;
    auto result2 = minMax2(arr2);
    std::cout << "minmax " << result2.first << ":" << result2.second << std::endl;

    const char *arr3[]{"E", "D", "C", "B", "A"};
    std::cout << "max " << max2(arr3) << std::endl;
    auto result3 = minMax2(arr3);
    std::cout << "minmax " << result3.first << ":" << result3.second << std::endl;

    std::cout << "sum " << sum2(arr3) << std::endl;

    // all of a sudden, if I add a test case for std::string, I can't compile because the templates are ambiguous
    std::string arr4[5] {"E", "D", "C", "B", "A"};
    std::cout << "sum " << sum2(arr4) << std::endl;
    std::cout << "max " << max2(arr4) << std::endl;
    auto result4 = minMax2(arr4);
    std::cout << "minmax " << result4.first << ":" << result4.second << std::endl;


    return 0;
}