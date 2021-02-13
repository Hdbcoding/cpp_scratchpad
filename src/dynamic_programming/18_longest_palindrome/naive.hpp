#include <string>

struct naive
{
    int maxPalindrome(const std::string &);

private:
    int recursive(const std::string &s, int left, int right);
};