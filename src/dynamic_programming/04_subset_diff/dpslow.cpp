#include <vector>
#include <cmath>
#include "dpslow.hpp"

using namespace std;

int dpslow::canPartition(const vector<int> &nums)
{
    int sum = 0;
    for (int i = 0; i < nums.size(); i++) {
      sum += nums[i];
    }

    // dp table that records what subset sizes we can construct 
    vector<vector<bool>> dp(nums.size(), vector<bool>(sum / 2 + 1, false));

    // can always construct the empty set
    for (int i = 0; i < nums.size(); ++i)
        dp[i][0] = true;

    // we can construct a subset of only the first item
    if (nums[0] <= sum / 2)
        dp[0][nums[0]] = true;

    for (int i = 1; i < nums.size(); ++i)
    {
        for (int s = 1; s <= sum / 2; ++s)
        {
            if (dp[i - 1][s])
            {
                dp[i][s] = dp[i - 1][s];
            }
            else if (s >= nums[i])
            {
                dp[i][s] = dp[i - 1][s - nums[i]];
            }
        }
    }

    // what is the biggest subset we can construct?
    int sum1 = 0;
    for (int s = sum / 2; s >= 0; --s)
        if (dp[nums.size() - 1][s])
        {
            sum1 = s;
            break;
        }

    int sum2 = sum - sum1;
    return abs(sum2 - sum1);
}