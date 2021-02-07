#include <vector>
#include "bottomup.hpp"

using namespace std;

int bottomup::solve(const vector<int> &weight, const vector<int> &profit, int capacity)
{
    vector<vector<int>> dp(weight.size(), vector<int>(capacity + 1, 0));

    for (int i = 0; i < weight.size(); ++i)
    {
        for (int c = 1; c <= capacity; ++c)
        {
            int profitWith{0}, profitWithout{0};

            if (i > 0)
                profitWithout = dp[i - 1][c];
            if (c >= weight[i])
                profitWith = profit[i] + dp[i][c - weight[i]];

            dp[i][c] = max(profitWith, profitWithout);
        }
    }

    return dp[weight.size() - 1][capacity];
}