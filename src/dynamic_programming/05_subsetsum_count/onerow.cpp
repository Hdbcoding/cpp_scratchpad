#include <vector>
#include "onerow.hpp"

using namespace std;

int onerow::countSubsets(const vector<int> &nums, int sum)
{
    vector<int> dp(sum + 1, 0);

    // there is always one subset with sum 0 - the empty set
    // (for only positive numbers)
    dp[0] = 1;

    // for the 1-size set, there is 1 combination of the size of that number
    // but, only worth checking if it's < sum
    if (nums[0] < sum)
        dp[nums[0]] = 1;

    for (int i = 1; i < nums.size(); ++i)
        for (int s = sum; s != 0; --s)
            if (s >= nums[i])
                dp[s] += dp[s - nums[i]];

    return dp[sum];
}