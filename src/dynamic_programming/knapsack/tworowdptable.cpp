#include <vector>
#include "tworowdptable.hpp"

using namespace std;


int tworowdptable::solveKnapsack(const vector<int> &profits, const vector<int> &weights, int capacity)
{
    if (capacity <= 0 || profits.empty())
        return 0;

    vector<vector<int>> dp(2, vector<int>(capacity + 1, 0));

    // first row - check if we can take the first
    for (int c = 0; c <= capacity; ++c)
        if (weights[0] <= c)
            dp[0][c] = profits[0];

    for (int i = 1; i < profits.size(); ++i)
    {
        int here = i & 1;
        int old = ~i & 1;

        for (int c = 1; c <= capacity; ++c)
        {
            int profitWith = 0;
            if (weights[i] <= c)
                profitWith = profits[i] + dp[old][c - weights[i]];

            int profitWithout = dp[old][c];

            dp[here][c] = max(profitWith, profitWithout);
        }
    }

    int row = (profits.size() - 1) & 1;
    return dp[row][capacity];
}