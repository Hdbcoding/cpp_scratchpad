#include <vector>
#include <cmath>
#include "memoizationslow.hpp"

using namespace std;

int recursiveSlow(const vector<int> &nums, int sum1, int sum2, int index, vector<vector<int>> &memo)
{
    if (index == nums.size())
        return abs(sum1 - sum2);

    if (memo[index][sum1] == -1)
    {
        // either try adding this element in the first set, or don't
        int diff1 = recursiveSlow(nums, sum1 + nums[index], sum2, index + 1, memo);
        int diff2 = recursiveSlow(nums, sum1, sum2 + nums[index], index + 1, memo);
        memo[index][sum1] = min(diff1, diff2);
    }

    return memo[index][sum1];
}

bool memoizationslow::canPartition(const vector<int> &nums, int diff)
{
    int sum = 0;
    for (int i : nums)
        sum += i;

    vector<vector<int>> memo(nums.size(), vector<int>(sum + 1, -1));

    return recursiveSlow(nums, 0, 0, 0, memo) <= diff;
}