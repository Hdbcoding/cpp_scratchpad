#include <iostream>
#include <cstring>

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
        result += arr[i];
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

// explicit specialization
template<> const char * max(const char *x, const char *y){
    return strcmp(x, y) > 0 ? x : y;
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

    return 0;
}