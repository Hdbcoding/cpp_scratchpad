#include <vector>
#include "bottomup.hpp"

using namespace std;

int bottomup::countWays(const vector<int> &nums, int sum)
{
    int total{0};
    for (int i : nums)
        total += i;
    
    if (total < sum)
        return 0;
    
    if ((total + sum) % 2 == 1)
        return 0;

    sum = (total + sum) / 2;

    vector<vector<int>> dp(nums.size(), vector<int>(sum + 1, 0));

    // target sum == 0 -> empty subset
    for (int i = 0; i < nums.size(); ++i)
        dp[i][0] = 1;

    if (nums[0] < sum)
        dp[0][nums[0]] = 1;

    for (int i = 1; i < nums.size(); ++i)
    {
        for (int s = 1; s <= sum; ++s)
        {
            dp[i][s] = dp[i - 1][s];
            if (s >= nums[i])
                dp[i][s] += dp[i - 1][s - nums[i]];
        }
    }

    return dp[nums.size() - 1][sum];
}