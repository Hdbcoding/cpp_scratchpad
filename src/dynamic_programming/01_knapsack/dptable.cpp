#include <vector>
#include "dptable.hpp"

using namespace std;


int dptable::solveKnapsack(const vector<int> &profits, const vector<int> &weights, int capacity)
{
    if (capacity <= 0 || profits.empty())
        return 0;

    vector<vector<int>> dp(profits.size(), vector<int>(capacity + 1, 0));

    // first row - check if we can take the first
    for (int c = 0; c <= capacity; ++c)
        if (weights[0] <= c)
            dp[0][c] = profits[0];

    for (int i = 1; i < profits.size(); ++i)
    {
        for (int c = 1; c <= capacity; ++c)
        {
            int profitWith = 0;
            if (weights[i] <= c)
                profitWith = profits[i] + dp[i - 1][c - weights[i]];

            int profitWithout = dp[i - 1][c];

            dp[i][c] = max(profitWith, profitWithout);
        }
    }

    return dp[profits.size() - 1][capacity];
}