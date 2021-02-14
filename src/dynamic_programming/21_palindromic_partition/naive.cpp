#include <string>
#include "naive.hpp"

using namespace std;

int naive::palindromePartition(const string &s)
{
    return recursive(s, 0, s.size() - 1);
}

int naive::recursive(const string &s, int left, int right)
{
    if (left >= right || isPalindrome(s, left, right))
        return 0;

    int minCuts = right - left;
    for (int i = left; i <= right; ++i)
    {
        if (isPalindrome(s, left, i))
            minCuts = min(minCuts, recursive(s, i + 1, right) + 1);
    }

    return minCuts;
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