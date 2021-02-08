#include <vector>
#include <limits>
#include "bottomup.hpp"

using namespace std;

int bottomup::maxCuts(const vector<int> &length, int total)
{
    vector<vector<int>> dp(length.size(), vector<int>(total + 1, 0));

    for (int i = 0; i < length.size(); ++i)
    {
        for (int l = 1; l <= total; ++l)
        {
            int useThisCut{0};
            if (l > length[i])
                useThisCut = dp[i][l - length[i]];
            if (useThisCut > 0)
                useThisCut += 1;

            int skipThisCut{0};
            if (i > 0)
                skipThisCut = dp[i - 1][l];

            return dp[useThisCut][skipThisCut];
        }
    }

        return dp[length.size() - 1][total];
}