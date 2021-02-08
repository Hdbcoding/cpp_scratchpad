#include <vector>
#include "bottomup.hpp"

using namespace std;


int bottomup::countWays(const vector<int> &value, int amount)
{
    vector<vector<int>> dp(value.size(), vector<int>(amount + 1, 0));

    for (int i = 0; i < value.size(); ++i)
        dp[i][0] = 1;

    for (int i = 0; i < value.size(); ++i)
        for (int a = 1; a <= amount; ++a)
        {
            int with{0}, without{0};

            if (i > 0)
                without = dp[i - 1][a];
            if (a >= value[i])
                with = dp[i][a - value[i]];
            
            dp[i][a] = with + without;
        }

    return dp[value.size() - 1][amount];
}