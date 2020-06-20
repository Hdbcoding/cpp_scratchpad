#include <string>
#include <iostream>

std::string toUpper(const std::string &s){
    std::string ret{s};
    for (char & c : ret)
        c = toupper(c);
    return ret;
}

std::string toLower(const std::string &s){
    std::string ret{s};
    for (char & c : ret)
        c = tolower(c);
    return ret;
}




int main(){
    std::string a = "aBcDe";

    std::cout << toUpper(a) << toLower(a) << std::endl;

    return 0;
}