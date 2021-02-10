#include <vector>
#include "bottomup.hpp"

using namespace std;

int bottomup::countWays(int n)
{
    vector<int> dp(n + 1);

    dp[0] = dp[1] = 1;
    if (n > 1)
        dp[2] = 2;

    for (int i = 3; i <= n; ++i)
        dp[i] = dp[i - 1] + dp[i - 2] + dp[i - 3];

    return dp[n];
}