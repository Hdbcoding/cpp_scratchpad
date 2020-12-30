#pragma once
#include <iostream>

template <typename T, int size>
void printArray(T (&arr)[size]){
    std::cout << "{ ";

    for (int i = 0; i < size - 1; i++){
        std::cout << arr[i] << ", ";
    }

    std::cout << arr[size - 1] << " }" << std::endl;
}