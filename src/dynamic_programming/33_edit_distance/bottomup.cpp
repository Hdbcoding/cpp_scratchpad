#include <string>
#include <vector>
#include "bottomup.hpp"

using namespace std;

int bottomup::editDistance(const string &w1, const string &w2)
{
    vector<vector<int>> dp(w1.size() + 1, vector<int>(w2.size() + 1, 0));

    for (int i = 0; i <= w1.size(); ++i)
        dp[i][0] = i;
    for (int j = 0; j <= w2.size(); ++j)
        dp[0][j] = j;

    for (int i = 0; i < w1.size(); ++i)
    {
        for (int j = 0; j < w2.size(); ++j)
        {
            if (w1[i] == w2[j])
            {
                dp[i + 1][j + 1] = dp[i][j];
            }
            else
            {
                dp[i + 1][j + 1] = 1 + min(dp[i][j + 1], min(dp[i + 1][j], dp[i][j]));
            }
        }
    }

    return dp[w1.size()][w2.size()];
}