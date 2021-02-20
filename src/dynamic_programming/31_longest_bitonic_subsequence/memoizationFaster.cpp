#include <vector>
#include "memoizationFaster.hpp"

using namespace std;

int memoizationFaster::lbs(const vector<int> &nums)
{
    vector<vector<int>> memo(nums.size(), vector<int>(nums.size() + 1, -1));

    int maxLength = 0;

    for (int i = 0; i < nums.size(); ++i)
        maxLength = max(maxLength, lds(nums, i + 1, i, true, memo) + lds(nums, i - 1, i, false, memo) + 1);

    return maxLength;
}

int memoizationFaster::lds(const vector<int> &nums, int current, int previous, bool forward, vector<vector<int>> &memo)
{
    if (current == nums.size() || current == -1)
        return 0;

    if (memo[current][previous + 1] == -1)
    {
        int next = forward ? current + 1 : current - 1;

        int useThis = 0;
        if (previous == -1 || nums[current] < nums[previous])
            useThis = lds(nums, next, current, forward, memo) + 1;

        int skipThis = lds(nums, next, previous, forward, memo);

        memo[current][previous + 1] =  max(useThis, skipThis);
    }
    return memo[current][previous + 1];
}