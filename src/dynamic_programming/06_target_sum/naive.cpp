#include <vector>
#include "naive.hpp"

using namespace std;

int recursive(const vector<int> &nums, int sum, int index)
{
    // if we've used up all the nums, we're done
    if (index == nums.size())
        // if we ended up with 0, then this way worked
        return sum == 0 ? 1 : 0;

    // count the ways if we either add or subtract this index
    return recursive(nums, sum - nums[index], index + 1) + recursive(nums, sum + nums[index], index + 1);
}

int naive::countWays(const vector<int> &nums, int sum)
{
    return recursive(nums, sum, 0);
}