#include <vector>
#include <cmath>
#include "memoization.hpp"

using namespace std;

bool recursiveFast(const vector<int> &nums, int sum, int diff, int index, vector<vector<int>> &memo)
{
    if (sum <= diff)
        return true;

    if (sum < 0 || index >= nums.size())
        return false;

    if (nums[index] == sum)
        return true;

    // either try adding this element in the first set, or don't
    if (memo[index][sum] == -1)
    {
        memo[index][sum] = recursiveFast(nums, sum - nums[index], diff, index + 1, memo) 
            || recursiveFast(nums, sum, diff, index + 1, memo);
    }

    return memo[index][sum] == 1;
}

bool memoization::canPartition(const vector<int> &nums, int diff)
{
    int sum = 0;
    for (int i : nums)
        sum += i;

    vector<vector<int>> memo(nums.size(), vector<int>(sum / 2 + 1, -1));
    return recursiveFast(nums, sum / 2, diff / 2, 0, memo);
}