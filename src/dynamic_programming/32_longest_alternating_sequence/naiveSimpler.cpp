#include <vector>
#include "naiveSimpler.hpp"

using namespace std;

int naiveSimpler::las(const vector<int> &nums)
{
    return max(las(nums, -1, 0, true), las(nums, -1, 0, false));
}

int naiveSimpler::las(const vector<int> &nums, int prev, int current, bool asc)
{
    if (current == nums.size())
        return 0;

    bool canChooseThis = prev == -1 
        || (asc && nums[prev] > nums[current]) 
        || (!asc && nums[prev] < nums[current]);

    int useThis = 0;
    if (canChooseThis)
        useThis = las(nums, current, current + 1, !asc) + 1;

    int skipThis = las(nums, prev, current + 1, asc);

    return max(useThis, skipThis);
}