#include <vector>
#include "dptable.hpp"

using namespace std;

int dptable::calculate(int n) const
{
    if (n == 0)
        return 0;
    
    vector<int> dp(n + 1, 0);

    dp[0] = 0;
    dp[1] = 1;

    for (int i = 2; i < dp.size(); ++i)
    {
        dp[i] = dp[i - 1] + dp[i - 2];
    }

    return dp[n];
}