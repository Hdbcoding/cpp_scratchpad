#include <iostream>

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

int main()
{
    // following doesn't work - needs same type!
    // std::cout << max(1, 2.0) << std::endl;

    std::cout << "max " << max(1, 2) << std::endl;
    std::cout << "min " << min(1, 2) << std::endl;
    std::cout << "add " << add(1, 2) << std::endl;

    int arr[]{1, 2, 3, 4, 5};
    std::cout << "sum " << sum(arr, 5) << std::endl;
    std::cout << "max " << max(arr, 5) << std::endl;
    auto result = minMax(arr, 5);
    std::cout << "minmax " << result.first << ":" << result.second << std::endl;

    return 0;
}