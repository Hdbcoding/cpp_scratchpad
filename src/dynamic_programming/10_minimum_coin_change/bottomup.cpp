#include <vector>
#include <limits>
#include "bottomup.hpp"

using namespace std;

// int recursive(const vector<int> &value, int amount, int index, vector<vector<int>> &memo)
// {
//     if (amount == 0)
//         return 0;

//     if (amount < 0 || index == value.size())
//         return numeric_limits<int>::max();

//     if (memo[index][amount] == 0)
//     {
//         int useThisCoin = numeric_limits<int>::max();

//         if (amount >= value[index])
//             useThisCoin = recursive(value, amount - value[index], index, memo);

//         if (useThisCoin != numeric_limits<int>::max())
//             useThisCoin += 1;

//         int skipThisCoin = recursive(value, amount, index + 1, memo);

//         memo[index][amount] = min(useThisCoin, skipThisCoin);
//     }

//     return memo[index][amount];
// }

int bottomup::minCoins(const vector<int> &value, int amount)
{
    vector<vector<int>> dp(value.size(), vector<int>(amount + 1, numeric_limits<int>::max()));

    for (int i = 0; i < value.size(); ++i)
        dp[i][0] = 0;

    for (int i = 0; i < value.size(); ++i)
    {
        for (int a = 1; a <= amount; ++a)
        {
            int useThisCoin{numeric_limits<int>::max()};
            if (a >= value[i])
                useThisCoin = dp[i][a - value[i]];
            if (useThisCoin < numeric_limits<int>::max())
                useThisCoin += 1;

            int skipThisCoin = numeric_limits<int>::max();
            if (i > 0)
                skipThisCoin = dp[i - 1][a];

            dp[i][a] = min(useThisCoin, skipThisCoin);
        }
    }

    return dp[value.size() - 1][amount];
}