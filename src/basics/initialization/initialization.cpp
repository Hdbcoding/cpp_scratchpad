#include <string>
#include <iostream>

int main(){
    // int a1; // uninitialized
    // copy initialization
    int a2 = 0;
    // direct initialization
    int a3(0);
    // uniform initialization
    int a4{0};
    // default initialization for integers will be 0
    int a5{};

    // narrowing conversions not allowed with uniform initialization
    // int a6{1.234f};

    std::cout << a2 << a3 << a4 << a5 << std::endl;

    std::string s1;
    // avoid copy initialization with user defined types
    std::string s2 = "some value";
    std::string s3("value");
    std::string s4{"value"};

    std::cout << s1 << s2 << s3 << s4 << std::endl;

    // char d1[8]; // uninitialized
    // copy initializations
    char d2[8] = {'\0'};
    char d3[8] = {'a', 'b', 'c', 'd'};
    char d4[8] = {"abcd"};
    char d5[8]{"abcd"};
    char d6[8]{'a', 'b', 'c', 'd'};

    std::cout << d2 << d3 << d4 << d5 << d6 << std::endl;

    int *p1 = new int{};

    char *p2 = new char[8]{};
    // for some reason, this version didn't work:
    // char *p3 = new char[8]{"Hello"};
    // error was "invalid conversion from 'const char*' to 'char'"
    char *p3 = new char[8]{'H', 'e', 'l', 'l', 'o', '\0'};

    std::cout << p1 << p2 << p3 << std::endl;

    return 0;
}