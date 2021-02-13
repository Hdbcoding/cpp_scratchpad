#include <string>
#include "naive.hpp"

using namespace std;

int naive::countPalindromes(const string &s)
{
    return recursive(s, 0, s.size() - 1);
}

int naive::recursive(const string &s, int left, int right)
{
    if (left > right)
        return 0;

    if (left == right)
        return 1;

    int total = 0;
    if (isPalindrome(s, left, right))
        total = 1;

    total += recursive(s, left + 1, right);
    total += recursive(s, left, right - 1);
    total -= recursive(s, left + 1, right - 1);
    return total;
}

bool naive::isPalindrome(const string &s, int left, int right)
{
    while (left < right)
    {
        if (s[left] != s[right])
            return false;
        ++left;
        --right;
    }
    return true;
}