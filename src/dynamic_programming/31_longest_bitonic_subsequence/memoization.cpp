#include <vector>
#include "memoization.hpp"

using namespace std;

int memoization::lbs(const vector<int> &nums)
{
    vector<vector<vector<int>>> memo(nums.size(), vector<vector<int>>(nums.size() + 1, vector<int>(2, -1)));

    return lbs(nums, 0, -1, true, memo);
}

int memoization::lbs(const vector<int> &nums, int current, int previous, bool increasing, vector<vector<vector<int>>> &memo)
{
    if (current == nums.size())
        return 0;

    if (memo[current][previous + 1][increasing ? 0 : 1] == -1)
    {
        int increase = 0;
        if (increasing)
        {
            int useThis = 0;

            if (previous == -1 || nums[current] > nums[previous])
                useThis = lbs(nums, current + 1, current, true, memo) + 1;

            int skipThis = lbs(nums, current + 1, previous, true, memo);
            increase = max(useThis, skipThis);
        }

        int decrease = 0;
        int useThis = 0;
        if (previous == -1 || nums[current] < nums[previous])
            useThis = lbs(nums, current + 1, current, false, memo) + 1;

        int skipThis = lbs(nums, current + 1, previous, false, memo);
        decrease = max(useThis, skipThis);

        memo[current][previous + 1][increasing ? 0 : 1] = max(increase, decrease);
    }

    return memo[current][previous + 1][increasing ? 0 : 1];
}