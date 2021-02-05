#include <vector>
#include <cmath>
#include "naive.hpp"

using namespace std;

bool recursiveFast(const vector<int> &nums, int sum, int diff, int index)
{
    if (sum <= diff)
        return true;

    if (sum < 0 || index >= nums.size())
        return false;

    if (nums[index] == sum)
        return true;

    // either try adding this element in the first set, or don't

    return recursiveFast(nums, sum - nums[index], diff, index + 1) || recursiveFast(nums, sum, diff, index + 1);
}

bool naive::canPartition(const vector<int> &nums, int diff)
{
    int sum = 0;
    for (int i : nums)
        sum += i;

    return recursiveFast(nums, sum / 2, diff / 2, 0);
}