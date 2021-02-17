#include <vector>
#include "naive.hpp"

using namespace std;

int naive::maxSum(const vector<int> &nums)
{
    return recursive(nums, 0, -1);
}

int naive::recursive(const vector<int> &nums, int current, int previous)
{
    if (current == nums.size())
        return 0;

    int useThis = 0;

    if (nums[current] > 0 && (previous == -1 || nums[current] > nums[previous]))
        useThis = recursive(nums, current + 1, current) + nums[current];

    int skipThis = recursive(nums, current + 1, previous);

    return max(useThis, skipThis);
}