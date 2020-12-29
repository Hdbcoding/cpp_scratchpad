#pragma once

// get the sum of two values
template <typename T>
T getSum(T x, T y)
{
    return x + y;
}

// get the sum of an array of values
template <typename T>
T getSum(T *arr, int arrSize)
{
    T result{arr[0]};
    for (int i = 1; i < arrSize; ++i)
    {
        result = getSum(result, arr[i]);
    }
    return result;
}

// get the sum of an array of values
template <typename T, int size>
T getSum(T (&arr)[size])
{
    T result{arr[0]};
    for (int i = 1; i < size; ++i)
    {
        result = getSum(result, arr[i]);
    }
    return result;
}

// get the sum of an array of c-strings
// "sum" in this case is the concatenation of all the strings in the array
// to avoid extra dynamic memory allocation, this allocates all of the required memory only once
// template specializations have to be inline or included in .cpp
template <int size>
inline const char *getSum(const char *(&arr)[size])
{
    int totalSize = 0;
    for (int i = 0; i < size; ++i)
    {
        totalSize += strlen(arr[i]);
    }

    char *result = (char *)malloc(totalSize * sizeof(char));
    // new char is also fine
    // char *result = new char[totalSize];
    // first has to be strcpy, or could do something like a strcpy(result, "\0")
    strcpy(result, arr[0]);
    for (int i = 1; i < size; ++i)
    {
        strcat(result, arr[i]);
    }
    return result;
}