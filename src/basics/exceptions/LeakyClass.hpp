#pragma once

#include "TestClass.hpp"
#include "TestClass2.hpp"

class LeakyClass {
    TestClass *a;
    TestClass2 b;
    int *uid;
    char *word;
    int *arr2;

public:
    LeakyClass();
    ~LeakyClass();
};