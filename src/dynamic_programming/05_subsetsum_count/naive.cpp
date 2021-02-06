#include <vector>
#include "naive.hpp"

using namespace std;

int recursive(const vector<int> &nums, int sum, int index)
{
    // if we found the sum, we're all set
    if (sum == 0)
        return 1;

    // if we overshot or if we've used up all the nums, we're done
    if (sum < 0 || index == nums.size())
        return 0;

    // see if we can find the sum either with or without this index
    return recursive(nums, sum - nums[index], index + 1) + recursive(nums, sum, index + 1);
}

int naive::countSubsets(const vector<int> &nums, int sum)
{
    return recursive(nums, sum, 0);
}