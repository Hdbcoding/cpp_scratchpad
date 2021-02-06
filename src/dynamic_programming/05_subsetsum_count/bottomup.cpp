#include <vector>
#include "bottomup.hpp"

using namespace std;

int bottomup::countSubsets(const vector<int> &nums, int sum)
{
    vector<vector<int>> dp(nums.size(), vector<int>(sum + 1, 0));

    // there is always one subset with sum 0 - the empty set
    // (for only positive numbers)
    for (int i = 0; i < nums.size(); ++i)
        dp[i][0] = 1;

    // for the 1-size set, there is 1 combination of the size of that number
    // but, only worth checking if it's < sum
    if (nums[0] < sum)
        dp[0][nums[0]] = 1;

    for (int i = 1; i < nums.size(); ++i)
        for (int s = 1; s <= sum; ++s)
        {
            dp[i][s] = dp[i - 1][s];

            if (s >= nums[i])
                dp[i][s] += dp[i - 1][s - nums[i]];
        }

    return dp[nums.size() - 1][sum];
}