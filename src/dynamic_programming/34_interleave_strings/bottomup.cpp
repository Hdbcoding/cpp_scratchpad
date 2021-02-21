#include <string>
#include <vector>
#include "bottomup.hpp"

using namespace std;

bool bottomup::interleaved(const string &w1, const string &w2, const string &w3)
{
    vector<vector<bool>> dp(w1.size() + 1, vector<bool>(w2.size() + 1, false));
    dp[0][0] = true;

    for (int i = 0; i < w1.size(); ++i)
    {
        if (w1[i] == w3[i])
            dp[i + 1][0] = dp[i][0];
        
        if (!dp[i + 1][0])
            break;
    }

    for (int i = 0; i < w2.size(); ++i)
    {
        if (w2[i] == w3[i])
            dp[0][i + 1] = dp[0][i];
        
        if (!dp[0][i + 1])
            break;
    }

    for (int i = 0; i < w1.size(); ++i)
    {
        for (int j = 0; j < w2.size(); ++j)
        {
            if (w1[i] == w3[i + j + 1])
            {
                dp[i + 1][j + 1] = dp[i][j + 1];
            }
            if (w2[j] == w3[i + j + 1])
            {
                dp[i + 1][j + 1] = dp[i + 1][j + 1] || dp[i + 1][j];
            }
        }
    }

    return dp[w1.size()][w2.size()];
}