#include <vector>
#include "naiveFaster.hpp"

using namespace std;

int naiveFaster::lbs(const vector<int> &nums)
{
    int maxLength = 0;

    for (int i = 0; i < nums.size(); ++i)
        maxLength = max(maxLength, lds(nums, i + 1, i, true) + lds(nums, i - 1, i, false) + 1);

    return maxLength;
}

int naiveFaster::lds(const vector<int> &nums, int current, int previous, bool forward)
{
    if (current == nums.size() || current == -1)
        return 0;

    int next = forward ? current + 1 : current - 1;

    int useThis = 0;
    if (previous == -1 || nums[current] < nums[previous])
        useThis = lds(nums, next, current, forward) + 1;

    int skipThis = lds(nums, next, previous, forward);

    return max(useThis, skipThis);
}