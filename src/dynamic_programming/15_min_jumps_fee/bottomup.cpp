#include <vector>
#include <limits>
#include "bottomup.hpp"

using namespace std;

int bottomup::minCost(const vector<int> &cost)
{
    vector<int> dp(cost.size() + 1, 0);

    for (int i = 1; i <= cost.size(); ++i)
    {
        int m1 = dp[i - 1] + cost[i - 1];
        int m2 = numeric_limits<int>::max();
        if (i > 1)
            m2 = dp[i - 2] + cost[i - 2];
        int m3 = numeric_limits<int>::max();
        if (i > 2)
            m3 = dp[i - 3] + cost[i - 3];
        dp[i] = min(m1, min(m2, m3));
    }

    return dp[cost.size()];
}