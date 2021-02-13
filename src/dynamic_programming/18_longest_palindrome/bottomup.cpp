#include <string>
#include <vector>
#include "bottomup.hpp"

using namespace std;

int bottomup::maxPalindrome(const string &s)
{
    vector<vector<int>> dp(s.size(), vector<int>(s.size(), 0));

    for (int i = 0; i < s.size(); ++i)
        dp[i][i] = 1;

    for (int i = s.size() - 2; i >= 0; --i)
        for (int j = i + 1; j < s.size(); ++j)
        {
            if (s[i] == s[j])
            {
                int inner = dp[i + 1][j - 1];
                if (inner == j - i - 1)
                    dp[i][j] = inner + 2;
            }
            if (dp[i][j] == 0)
                dp[i][j] = max(dp[i + 1][j], dp[i][j - 1]);
        }

    return dp[0][s.size() - 1];
}