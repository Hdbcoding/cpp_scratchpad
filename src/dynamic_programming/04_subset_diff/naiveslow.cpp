#include <vector>
#include <cmath>
#include "naiveslow.hpp"

using namespace std;

int recursiveSlow(const vector<int> &nums, int sum1, int sum2, int index)
{
    if (index == nums.size())
        return abs(sum1 - sum2);

    // either try adding this element in the first set, or don't
    int diff1 = recursiveSlow(nums, sum1 + nums[index], sum2, index + 1);
    int diff2 = recursiveSlow(nums, sum1, sum2 + nums[index], index + 1);

    return min(diff1, diff2);
}

bool naiveslow::canPartition(const vector<int> &nums, int diff)
{
    return recursiveSlow(nums, 0, 0, 0) <= diff;
}