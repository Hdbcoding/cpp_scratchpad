#include <vector>
#include "naive.hpp"

using namespace std;

int recursive(const vector<int> &nums, int sum, int index)
{
    if (sum == 0)
        return true;

    if (sum < 0 || index >= nums.size())
        return false;

    if (nums[index] == sum)
        return true;

    // either try adding this element, or don't
    return recursive(nums, sum - nums[index], index + 1) || recursive(nums, sum, index + 1);
}

bool naive::canGetSubset(const vector<int> &nums, int sum){
    return recursive(nums, sum, 0);
}