#include <vector>
#include "memoization.hpp"

using namespace std;

int memoization::maxSum(const vector<int> &nums)
{
    vector<vector<int>> memo(nums.size(), vector<int>(nums.size() + 1, -1));
    return recursive(nums, 0, -1, memo);
}

int memoization::recursive(const vector<int> &nums, int current, int previous, vector<vector<int>> &memo)
{
    if (current == nums.size())
        return 0;

    if (memo[current][previous + 1] == -1)
    {
        int useThis = 0;
        if (nums[current] > 0 && (previous == -1 || nums[current] > nums[previous]))
            useThis = recursive(nums, current + 1, current, memo) + nums[current];

        int skipThis = recursive(nums, current + 1, previous, memo);

        memo[current][previous + 1] = max(useThis, skipThis);
    }

    return memo[current][previous + 1];
}