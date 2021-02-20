#include <vector>
#include "naive.hpp"

using namespace std;

int naive::lbs(const vector<int> &nums)
{
    return lbs(nums, 0, -1, true);
}

int naive::lbs(const vector<int> &nums, int current, int previous, bool increasing)
{
    if (current == nums.size())
        return 0;

    int increase = 0;
    if (increasing)
    {
        int useThis = 0;

        if (previous == -1 || nums[current] > nums[previous])
            useThis = lbs(nums, current + 1, current, true) + 1;

        int skipThis = lbs(nums, current + 1, previous, true);
        increase = max(useThis, skipThis);
    }

    int decrease = 0;
    int useThis = 0;
    if (previous == -1 || nums[current] < nums[previous])
        useThis = lbs(nums, current + 1, current, false) + 1;

    int skipThis = lbs(nums, current + 1, previous, false);
    decrease = max(useThis, skipThis);

    return max(increase, decrease);
}