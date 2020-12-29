#pragma once
#include <utility>
#include "getMin.hpp"
#include "getMax.hpp"

// get the minimum and maximum of an array of values
template <typename T>
std::pair<T, T> getMinMax(T *arr, int arrSize)
{
    std::pair<T, T> result{arr[0], arr[0]};

    for (int i = 1; i < arrSize; ++i)
    {
        result.first = getMin(result.first, arr[i]);
        result.second = getMax(result.second, arr[i]);
    }

    return result;
}

// get the minimum and maximum of an array of values
template <typename T, int size>
std::pair<T, T> getMinMax(T (&arr)[size])
{
    std::pair<T, T> result{arr[0], arr[0]};

    for (int i = 1; i < size; ++i)
    {
        result.first = getMin(result.first, arr[i]);
        result.second = getMax(result.second, arr[i]);
    }

    return result;
}