#include <string>
#include <vector>
#include "memoization.hpp"

using namespace std;

int memoization::maxPalindrome(const string &s)
{
    vector<vector<int>> memo(s.size(), vector<int>(s.size(), -1));
    return recursive(s, 0, s.size() - 1, memo);
}

int memoization::recursive(const string &s, int left, int right, vector<vector<int>> &memo)
{
    if (left > right)
        return 0;

    if (left == right)
        return 1;

    if (memo[left][right] == -1)
    {
        int v = 0;
        if (s[left] == s[right])
        {
            int inner = recursive(s, left + 1, right - 1, memo);
            if (inner == (right - left - 1))
                v = right - left + 1;
        }
        
        if (v == 0)
            v = max(recursive(s, left + 1, right, memo), recursive(s, left, right - 1, memo));

        memo[left][right] = v;
    }

    return memo[left][right];
}