#include <string>
#include "nodpn2.hpp"

using namespace std;

int nodpn2::maxPalindrome(const string &s)
{
    int w = 0;

    for (int i = 0; i < s.size(); ++i)
    {
        int odd = width(s, i, i);
        int even = width(s, i, i + 1);
        w = max(w, max(odd, even));
    }

    return w;
}

int nodpn2::width(const string &s, int l, int r)
{
    while (l >= 0 && r < s.size() && s[l] == s[r])
    {
        --l;
        ++r;
    }
    return r - l - 1;
}