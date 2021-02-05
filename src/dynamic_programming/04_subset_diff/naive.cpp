#include <vector>
#include <cmath>
#include "naive.hpp"

using namespace std;

// int recursive(const vector<int> &nums, int sum1, int sum2, int index)
// {
//     if (index == nums.size())
//         return abs(sum1 - sum2);

//     // either try adding this element in the first set, or don't

//     int diff1 = recursive(nums, sum1 + nums[index], sum2, index + 1);
//     int diff2 = recursive(nums, sum1, sum2 + nums[index], index + 1);

//     return min(diff1, diff2);
// }

int recursiveFast(const vector<int> &nums, int sum, int diff, int index)
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

    // return recursive(nums, 0, 0, 0) <= diff;
}