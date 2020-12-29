#pragma once
#include <cstring>

// get the max of two values
template <typename T>
T getMax(T x, T y)
{
    return x > y ? x : y;
}

// get the max of two c-strings (explicit template specialization)
// template specializations have to be inline or included in .cpp
template <>
inline const char *getMax(const char *x, const char *y)
{
    return strcmp(x, y) > 0 ? x : y;
}

// get the max of an array of values
template <typename T>
T getMax(T *arr, int arrSize)
{
    T result{arr[0]};
    for (int i = 1; i < arrSize; ++i)
    {
        result = getMax(result, arr[i]);
    }
    return result;
}

// get the max of an array of values
template <typename T, int size>
T getMax(T (&arr)[size])
{
    T result{arr[0]};
    for (int i = 1; i < size; ++i)
    {
        result = getMax(result, arr[i]);
    }
    return result;
}