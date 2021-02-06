#include <vector>
#include "memoization.hpp"

using namespace std;

int recursive(const vector<int> &nums, int sum, int index, vector<vector<int>> &memo)
{
    // if we found the sum, we're all set
    if (sum == 0)
        return 1;

    // if we overshot or if we've used up all the nums, we're done
    if (sum < 0 || index == nums.size())
        return 0;

    // see if we can find the sum either with or without this index
    if (memo[index][sum] == -1)
        memo[index][sum] = recursive(nums, sum - nums[index], index + 1, memo) + recursive(nums, sum, index + 1, memo);

    return memo[index][sum];
}

int memoization::countSubsets(const vector<int> &nums, int sum)
{
    vector<vector<int>> memo(nums.size(), vector<int>(sum + 1, -1));
    return recursive(nums, sum, 0, memo);
}