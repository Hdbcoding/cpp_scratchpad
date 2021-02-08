#include <vector>
#include <limits>
#include "memoization.hpp"

using namespace std;

int recursive(const vector<int> &value, int amount, int index, vector<vector<int>> &memo)
{
    if (amount == 0)
        return 0;

    if (amount < 0 || index == value.size())
        return numeric_limits<int>::max();

    if (memo[index][amount] == 0)
    {
        int useThisCoin = numeric_limits<int>::max();

        if (amount >= value[index])
            useThisCoin = recursive(value, amount - value[index], index, memo);
        
        if (useThisCoin != numeric_limits<int>::max())
            useThisCoin += 1;

        int skipThisCoin = recursive(value, amount, index + 1, memo);

        memo[index][amount] = min(useThisCoin, skipThisCoin);
    }

    return memo[index][amount];
}


int memoization::minCoins(const vector<int> &value, int amount)
{
    vector<vector<int>> memo(value.size(), vector<int>(amount + 1));
    return recursive(value, amount, 0, memo);
}