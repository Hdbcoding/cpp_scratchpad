#pragma once
#include <cstring>

// get the min of two values
template <typename T>
T getMin(T x, T y)
{
    return x > y ? y : x;
}

// get the min of two c-strings (explicit template specialization)
// template specializations have to be inline or included in .cpp
template <>
inline const char *getMin(const char *x, const char *y)
{
    return strcmp(x, y) < 0 ? x : y;
}

// get the min of an array of values
template <typename T>
T getMin(T *arr, int arrSize)
{
    T result{arr[0]};
    for (int i = 1; i < arrSize; ++i)
    {
        result = getMin(result, arr[i]);
    }
    return result;
}

// get the min of an array of values
template <typename T, int size>
T getMin(T (&arr)[size])
{
    T result{arr[0]};
    for (int i = 1; i < size; ++i)
    {
        result = getMin(result, arr[i]);
    }
    return result;
}