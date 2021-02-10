#include <vector>
#include "bottomup.hpp"

using namespace std;

int bottomup::countWays(int n)
{
    vector<int> dp(n + 1);

    dp[0] = dp[1] = 1;
    if (n > 1)
        dp[2] = 1;
    if (n > 2)
        dp[3] = 2;

    for (int i = 4; i <= n; ++i)
    {
        dp[i] = dp[i - 1] + dp[i - 3] + dp[i - 4];
    }

    return dp[n];
}