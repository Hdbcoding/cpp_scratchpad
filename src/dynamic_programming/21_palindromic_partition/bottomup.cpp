#include <string>
#include <vector>
#include "bottomup.hpp"

using namespace std;

int bottomup::palindromePartition(const string &s)
{
    vector<vector<bool>> isPalindrome(s.size(), vector<bool>(s.size()));

    for (int i = 0; i < s.size(); ++i)
        isPalindrome[i][i] = true;

    for (int left = s.size() - 2; left >= 0; --left)
    {
        for (int right = left + 1; right < s.size(); ++ right)
        {
            if (s[left] == s[right] && (right - left == 1 || isPalindrome[left + 1][right - 1]))
                isPalindrome[left][right] = true;
        }
    }

    vector<int> dp(s.size());

    for (int left = s.size() - 1; left >= 0; --left)
    {
        int minCuts = s.size();
        for (int right = s.size() - 1; right >= left; --right)
        {
            if (isPalindrome[left][right])
            {
                minCuts = right == s.size() - 1
                    ? 0
                    : min(minCuts, 1 + dp[right + 1]);
            }
        }
        dp[left] = minCuts;
    }

        return dp[0];
}