#include <string>
#include <vector>
#include "onerow.hpp"

using namespace std;

int onerow::lcs(const string &w1, const string &w2)
{
    vector<vector<int>> dp(2, vector<int>(w2.size() + 1));

    int maxLength = 0;
    for (int i = 0; i < w1.size(); ++i)
    {
        for (int j = 0; j < w2.size(); ++j)
        {
            dp[i % 2][j + 1] = 0;
            if (w1[i] == w2[j])
            {
                dp[i % 2][j + 1] = dp[(i + 1) % 2][j] + 1;
                maxLength = max(maxLength, dp[i % 2][j + 1]);
            }
        }
    }
    return maxLength;
}