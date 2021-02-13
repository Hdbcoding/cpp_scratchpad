#include <string>
#include <vector>
#include "memoization.hpp"

using namespace std;

int memoization::countPalindromes(const string &s)
{
    vector<vector<int>> memo(s.size(), vector<int>(s.size()));
    return recursive(s, 0, s.size() - 1, memo);
}

int memoization::recursive(const string &s, int left, int right, vector<vector<int>> &memo)
{
    if (left > right)
        return 0;

    if (left == right)
        return 1;

    if (memo[left][right] == 0)
    {
        int total = 0;
        if (isPalindrome(s, left, right))
            total = 1;

        total += recursive(s, left + 1, right, memo);
        total += recursive(s, left, right - 1, memo);
        total -= recursive(s, left + 1, right - 1, memo);
        memo[left][right] = total;
    }

    return memo[left][right];
}

bool memoization::isPalindrome(const string &s, int left, int right)
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