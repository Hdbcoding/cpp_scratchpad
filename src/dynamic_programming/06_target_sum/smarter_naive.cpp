#include <vector>
#include "smarter_naive.hpp"

using namespace std;

int smarter_recursive(const vector<int> &nums, int sum, int index)
{
    if (sum == 0)
        return 1;

    if (sum < 0 || index >= nums.size())
        return 0;

    if (nums[index] == sum)
        return 1;

    // count the ways if we either add or subtract this index
    return smarter_recursive(nums, sum - nums[index], index + 1) + smarter_recursive(nums, sum, index + 1);
}

int smarter_naive::countWays(const vector<int> &nums, int target)
{
    int total{0};
    for (int i : nums)
        total += i;
    
    if (total < target)
        return 0;
    
    if ((total + target) % 2 == 1)
        return 0;

    return smarter_recursive(nums, (total + target) / 2, 0);
}