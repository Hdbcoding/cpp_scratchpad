#include <iostream>
#include "integer.hpp"

integer::integer()
    : v{new int(0)}
{
    std::cout << "integer() - default constructor" << std::endl;
}

integer::~integer()
{
    delete v;
    std::cout << "~integer() - destructor" << std::endl;
}

integer::integer(int value)
    : v{new int(value)}
{
    std::cout << "integer(int) - parameterized constructor" << std::endl;
}

integer::integer(const integer &obj)
    : v{new int(obj.getValue())}
{
    std::cout << "integer(const integer &) - copy constructor" << std::endl;
}

integer::integer(integer &&obj)
    : v{obj.v}
{
    obj.v = nullptr;
    std::cout << "integer(integer &&) - move constructor" << std::endl;
}

integer &integer::operator=(const integer &a)
{
    std::cout << "&integer::operator=(const integer &) - copy assignment operator" << std::endl;
    // if we are not making a self assignment
    if (this != &a)
    {
        delete v;
        v = new int(a.getValue());
    }
    return *this;
}

integer &integer::operator=(integer &&a)
{
    std::cout << "&integer::operator=(integer &&) - move assignment operator" << std::endl;
    if (this != &a)
    {
        delete v;
        v = a.v;
        a.v = nullptr;
    }
    return *this;
}

int integer::getValue() const
{
    return *v;
}

void integer::setValue(int value)
{
    *v = value;
}