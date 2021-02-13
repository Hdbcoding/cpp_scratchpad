#include <string>

struct nodpn2
{
    int maxPalindrome(const std::string &);

private:
    int width(const std::string &s, int l, int r);
};