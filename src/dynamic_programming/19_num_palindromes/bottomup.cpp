#include <string>
#include <vector>
#include "bottomup.hpp"

using namespace std;

int bottomup::countPalindromes(const string &s)
{
    vector<vector<bool>> dp(s.size(), vector<bool>(s.size(), 0));
    int count = s.size();

    for (int i = 0; i < s.size(); ++i)
        dp[i][i] = true;

    for (int i = s.size() - 2; i >= 0; --i)
        for (int j = i + 1; j < s.size(); ++j)
        {
            if (s[i] == s[j] && ((j - i == 1) || dp[i + 1][j - 1]))
            {
                dp[i][j] = true;
                ++count;
            }
        }

    return count;
}