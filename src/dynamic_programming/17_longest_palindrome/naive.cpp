#include <string>
#include "naive.hpp"

using namespace std;

int naive::maxPalindrome(const string &s)
{
    return recursive(s, 0, s.size() - 1);
}

int naive::recursive(const string &s, int left, int right)
{
    if (left > right)
        return 0;

    if (left == right)
        return 1;

    if (s[left] == s[right])
        return recursive(s, left + 1, right - 1) + 2;

    return max(recursive(s, left + 1, right), recursive(s, left, right - 1));
}