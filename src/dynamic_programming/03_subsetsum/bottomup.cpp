#include <vector>
#include "bottomup.hpp"

using namespace std;

bool bottomup::canGetSubset(const vector<int> &nums, int sum)
{
    vector<vector<bool>> dp(nums.size(), vector<bool>(sum + 1, false));

    // target sum == 0 ? true
    for (int i = 0; i < nums.size(); ++i)
        dp[i][0] = true;

    // target sum == num ? true
    for (int s = 1; s <= sum; ++s)
        dp[0][s] = (nums[0] == s ? true : false);

    for (int i = 1; i < nums.size(); ++i)
    {
        for (int s = 1; s <= sum; ++s)
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

    return dp[nums.size() - 1][sum];
}