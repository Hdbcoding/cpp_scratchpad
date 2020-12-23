#include <iostream>
#include "LeakyClass.hpp"

LeakyClass::LeakyClass()
{
    std::cout << "LeakyClass constructor" << std::endl;
    a = new TestClass();
    // exceptions thrown at startup skip the destructor, so dynamically allocated memory will not be freed
    // thus, the instance of TestClass on the heap will be a memory leak
    throw std::runtime_error("oops, failed to construct LeakyClass");
    uid = new int;
    word = new char[100];
    arr2 = new int[50000];
}

LeakyClass::~LeakyClass()
{
    std::cout << "LeakyClass destructor" << std::endl;
    delete a;
    delete uid;
    delete[] word;
    delete[] arr2;
}
