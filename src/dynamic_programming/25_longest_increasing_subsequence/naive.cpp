#include <vector>
#include "naive.hpp"

using namespace std;

int naive::lis(const vector<int> &nums)
{
    return recursive(nums, 0, -1);
}

int naive::recursive(const vector<int> &nums, int current, int previous)
{
    if (current == nums.size())
        return 0;

    int useThis = 0;
    if (previous == -1 || nums[previous] < nums[current])
        useThis = recursive(nums, current + 1, current) + 1;

    int skipThis = recursive(nums, current + 1, previous);

    return max(useThis, skipThis);
}