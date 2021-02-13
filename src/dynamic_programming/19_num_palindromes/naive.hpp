#include <string>

struct naive
{
    int countPalindromes(const std::string &);

private:
    int recursive(const std::string &s, int left, int right);
    bool isPalindrome(const std::string &s, int left, int right);
};