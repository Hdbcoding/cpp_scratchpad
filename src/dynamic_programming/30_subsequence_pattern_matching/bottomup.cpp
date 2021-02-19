#include <string>
#include <vector>
#include "bottomup.hpp"

using namespace std;

int bottomup::patternMatch(const string &word, const string &pattern)
{
    vector<vector<int>> dp(word.size() + 1, vector<int>(pattern.size() + 1, 0));

    for (int i = 0; i <= word.size(); ++i)
    {
        dp[i][0] = 1;
    }

    for (int i = 0; i < word.size(); ++i)
        for (int j = 0; j < pattern.size(); ++j)
        {
            if (word[i] == pattern[j])
            {
                dp[i + 1][j + 1] = dp[i][j];
            }
            dp[i + 1][j + 1] += dp[i][j + 1];
        }

    return dp[word.size()][pattern.size()];
}