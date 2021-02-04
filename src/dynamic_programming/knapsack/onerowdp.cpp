#include <vector>
#include "onerowdp.hpp"

using namespace std;


int onerowdp::solveKnapsack(const vector<int> &profits, const vector<int> &weights, int capacity)
{
    if (capacity <= 0 || profits.empty())
        return 0;

    vector<int> dp(capacity + 1, 0);

    // first row - check if we can take the first
    for (int c = 0; c <= capacity; ++c)
        if (weights[0] <= c)
            dp[c] = profits[0];

    for (int i = 1; i < profits.size(); ++i)
    {
        for (int c = capacity; c != 0; --c)
        {
            int profitWith = 0;
            if (weights[i] <= c)
                profitWith = profits[i] + dp[c - weights[i]];

            int profitWithout = dp[c];

            dp[c] = max(profitWith, profitWithout);
        }
    }

    return dp[capacity];
}