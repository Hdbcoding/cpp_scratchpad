#include <string>
#include <vector>
#include "memoization.hpp"

using namespace std;

int memoization::palindromePartition(const string &s)
{
    vector<vector<int>> memo(s.size(), vector<int>(s.size(), 0));
    return recursive(s, 0, s.size() - 1, memo);
}

int memoization::recursive(const string &s, int left, int right, vector<vector<int>> &memo)
{
    if (left >= right || isPalindrome(s, left, right))
        return 0;

    if (memo[left][right] == 0)
    {
        int minCuts = right - left;
        for (int i = left; i <= right; ++i)
        {
            if (isPalindrome(s, left, i))
                minCuts = min(minCuts, recursive(s, i + 1, right, memo) + 1);
        }

        memo[left][right] = minCuts;
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