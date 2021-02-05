#include <vector>
#include "singlerow.hpp"

using namespace std;

bool singlerow::canGetSubset(const vector<int> &nums, int sum)
{
    vector<bool> dp(sum + 1, false);
    dp[0] = true;

    // target sum == num ? true
    for (int s = 1; s <= sum; ++s)
        dp[s] = (nums[0] == s ? true : false);

    for (int i = 1; i < nums.size(); ++i)
        for (int s = sum; s != 0; --s)
            if (!dp[s] && s >= nums[i])
                dp[s] = dp[s - nums[i]];

    return dp[sum];
}