#include <vector>
#include "memoization.hpp"

using namespace std;

int recursive(const vector<int> &nums, int sum, int index, vector<vector<int>> &memo)
{
    if (sum == 0)
        return true;

    if (sum < 0 || index >= nums.size())
        return false;

    if (nums[index] == sum)
        return true;

    // if we haven't yet processed this problem size
    if (memo[index][sum] == -1)
    {
        // either try adding this element, or don't
        memo[index][sum] =
            (recursive(nums, sum - nums[index], index + 1, memo) || recursive(nums, sum, index + 1, memo)) ? 1 : 0;
    }

    return memo[index][sum] == 1;
}

bool memoization::canPartition(const vector<int> &nums)
{
    int sum = 0;
    for (int i : nums)
        sum += i;

    if (sum % 2 == 1)
        return false;

    vector<vector<int>> memo(nums.size(), vector<int>(sum / 2 + 1, -1));

    return recursive(nums, sum / 2, 0, memo);
}