#include <string>
#include <vector>
#include "bottomup.hpp"

using namespace std;

int bottomup::lcs(const string &w1, const string &w2)
{
    vector<vector<int>> dp(w1.size() + 1, vector<int>(w2.size() + 1));

    for (int i = 0; i < w1.size(); ++i)
    {
        for (int j = 0; j < w2.size(); ++j)
        {
            if (w1[i] == w2[j])
                dp[i + 1][j + 1] = dp[i][j] + 1;
            else
                dp[i + 1][j + 1] = max(dp[i][j + 1], dp[i + 1][j]);
        }
    }

    return dp[w1.size()][w2.size()];
}