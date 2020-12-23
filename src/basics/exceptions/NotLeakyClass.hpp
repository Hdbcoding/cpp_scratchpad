#pragma once

#include <memory>
#include <string>
#include <vector>
#include "TestClass.hpp"
#include "TestClass2.hpp"

class NotLeakyClass {
    std::unique_ptr<TestClass> a;
    TestClass2 b;
    std::unique_ptr<int> uid;
    std::string word;
    std::vector<int> arr2;

public:
    NotLeakyClass();
    ~NotLeakyClass();
};