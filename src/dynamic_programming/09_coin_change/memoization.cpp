#include <vector>
#include "memoization.hpp"

using namespace std;

int recursive(const vector<int> &value, int amount, int index, vector<vector<int>> &memo)
{
    if (amount == 0)
        return 1;

    if (amount < 0 || index == value.size())
        return 0;

    if (memo[index][amount] == -1)
    {
        int useThisCoin = 0;
        if (amount >= value[index])
            useThisCoin = recursive(value, amount - value[index], index, memo);
        int skipThisCoin = recursive(value, amount, index + 1, memo);

        memo[index][amount] = useThisCoin + skipThisCoin;
    }

    return memo[index][amount];
}


int memoization::countWays(const vector<int> &value, int amount)
{
    vector<vector<int>> memo(value.size(), vector<int>(amount + 1, -1));
    return recursive(value, amount, 0, memo);
}