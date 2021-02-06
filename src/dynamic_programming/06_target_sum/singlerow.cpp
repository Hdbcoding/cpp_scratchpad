#include <vector>
#include "singlerow.hpp"

using namespace std;

int singlerow::countWays(const vector<int> &nums, int sum)
{
    int total{0};
    for (int i : nums)
        total += i;
    
    if (total < sum)
        return 0;
    
    if ((total + sum) % 2 == 1)
        return 0;

    sum = (total + sum) / 2;

    vector<int> dp(sum + 1, 0);

    // target sum == 0 -> empty subset
    dp[0] = 1;

    // possible lonely subset of the first element in the set
    if (nums[0] < sum)
        dp[nums[0]] = 1;

    for (int i = 1; i < nums.size(); ++i)
    {
        for (int s = sum; s != 0; --s)
        {
            if (s >= nums[i])
                dp[s] += dp[s - nums[i]];
        }
    }

    return dp[sum];
}