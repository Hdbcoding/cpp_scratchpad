#include <string>
#include <vector>
#include "tworow.hpp"

using namespace std;

pair<int, int> tworow::minEdits(const string &w1, const string &w2)
{
    vector<vector<int>> dp(2 + 1, vector<int>(w2.size() + 1));

    for (int i = 0; i < w1.size(); ++i)
    {
        for (int j = 0; j < w2.size(); ++j)
        {
            if (w1[i] == w2[j])
                dp[(i + 1) % 2][j + 1] = dp[i % 2][j] + 1;
            else
                dp[(i + 1) % 2][j + 1] = max(dp[i % 2][j + 1], dp[(i + 1) % 2][j]);
        }
    }

    int lcs = dp[w1.size() % 2][w2.size()];

    return {w1.size() - lcs, w2.size() - lcs};
}