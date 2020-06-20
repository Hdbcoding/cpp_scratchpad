#include <string>
#include <iostream>
#include <vector>

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

enum class Case
{
    sensitive,
    insensitive
};

size_t find(const std::string &src, const std::string &pattern, Case searchCase = Case::insensitive, size_t offset = 0){
    if (searchCase == Case::insensitive)
        return src.find(pattern);

    return toLower(src).find(toLower(pattern));
}

std::vector<size_t> findAll(const std::string &src, const std::string &pattern, Case searchCase = Case::insensitive, size_t offset = 0) {
    std::vector<size_t> ret;
    int i = offset;

    while (i != std::string::npos){
        // of course, don't want to toLower every single time I find, but whatever
        i = find(src, pattern, searchCase, offset);
        if (i != std::string::npos)
            ret.push_back(i);
    }

    return ret;
}




int main(){
    std::string a = "aBcDe";

    std::cout << toUpper(a) << toLower(a) << std::endl;

    return 0;
}