#include <string>
#include <vector>
#include "bottomup.hpp"

using namespace std;

int bottomup::lrs(const string &w)
{
    vector<vector<int>> dp(w.size() + 1, vector<int>(w.size() + 1));

    for (int i = 0; i < w.size(); ++i)
    {
        for (int j = 0; j < w.size(); ++j)
        {
            if (i != j && w[i] == w[j])
            {
                dp[i + 1][j + 1] = dp[i][j] + 1;
            }
            else
            {
                dp[i + 1][j + 1] = max(dp[i][j + 1], dp[i + 1][j]);
            }
        }
    }

    return dp[w.size()][w.size()];
}