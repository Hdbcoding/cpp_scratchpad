#include <iostream>
#include "NotLeakyClass.hpp"

NotLeakyClass::NotLeakyClass()
{
    std::cout << "NotLeakyClass constructor" << std::endl;
    a.reset(new TestClass());
    // with RAII, the memory leak is handled
    throw std::runtime_error("oops, failed to construct NotLeakyClass");
    uid.reset(new int);
    word.reserve(100);
    arr2.reserve(50000);
}

NotLeakyClass::~NotLeakyClass()
{
    std::cout << "NotLeakyClass destructor" << std::endl;
}
