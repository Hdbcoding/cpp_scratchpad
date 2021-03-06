#include <vector>
#include "memoization.hpp"

using namespace std;

int memoization::las(const vector<int> &nums)
{
    vector<vector<vector<int>>> memo(2, vector<vector<int>>(nums.size(), vector<int>(nums.size() + 1, -1)));
    return las(nums, -1, -1, 0, memo);
}

int memoization::las(const vector<int> &nums, int prev2, int prev, int current, vector<vector<vector<int>>> &memo)
{
    if (current == nums.size())
        return 0;

    bool increasing = prev2 == -1 || prev == -1 || nums[prev2] < nums[prev];
    int key = increasing ? 0 : 1;

    if (memo[key][current][prev + 1] == -1)
    {
        bool canChooseThis = prev2 == -1 || prev == -1 
            || (nums[prev2] < nums[prev] && nums[prev] > nums[current]) 
            || (nums[prev2] > nums[prev] && nums[prev] < nums[current]);

        int useThis = 0;
        if (canChooseThis)
            useThis = las(nums, prev, current, current + 1, memo) + 1;

        int skipThis = las(nums, prev2, prev, current + 1, memo);

        memo[key][current][prev + 1] = max(useThis, skipThis);
    }

    return memo[key][current][prev + 1];
}