#include <vector>
#include "bottomup.hpp"

using namespace std;

int bottomup::maxSum(const vector<int> &nums)
{
    vector<int> dp(nums.begin(), nums.end());
    int maxSubsequenceSum = 0;

    for (int i = 1; i < nums.size(); ++i)
    {
        if (nums[i] <= 0)
            continue;

        for (int j = 0; j < i; ++j)
        {
            if (nums[i] > nums[j] && dp[i] < dp[j] + nums[i])
            {
                dp[i] = dp[j] + nums[i];
                maxSubsequenceSum = max(maxSubsequenceSum, dp[i]);
            }
        }
    }

        return maxSubsequenceSum;
}   