#include <vector>
#include "naive.hpp"

using namespace std;

int naive::las(const vector<int> &nums)
{
    return las(nums, -1, -1, 0);
}

int naive::las(const vector<int> &nums, int prev2, int prev, int current)
{
    if (current == nums.size())
        return 0;

    bool canChooseThis = prev2 == -1 || prev == -1 
        || (nums[prev2] < nums[prev] && nums[prev] > nums[current]) 
        || (nums[prev2] > nums[prev] && nums[prev] < nums[current]);

    int useThis = 0;
    if (canChooseThis)
        useThis = las(nums, prev, current, current + 1) + 1;

    int skipThis = las(nums, prev2, prev, current + 1);

    return max(useThis, skipThis);
}