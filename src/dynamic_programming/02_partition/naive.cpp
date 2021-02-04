#include <vector>
#include "naive.hpp"

using namespace std;

int recursive(const vector<int> &nums, int currentSum, int targetSum, int index)
{
    if (currentSum == targetSum)
        return currentSum;

    if (currentSum > targetSum || index >= nums.size())
        return 0;

    if (nums[index] + currentSum == targetSum)
        return targetSum;

    int sumWith = 0;
    if (nums[index] + currentSum < targetSum)
        sumWith = recursive(nums, currentSum + nums[index], targetSum, index + 1);

    int sumWithout = recursive(nums, currentSum, targetSum, index + 1);
    return max(sumWith, sumWithout);
}

bool naive::canPartition(const vector<int> &nums){
    int sum = 0;
    for (int i : nums)
        sum += i;

    if (sum % 2 == 1)
        return false;

    sum /= 2;

    int closestSum = recursive(nums, 0, sum, 0);
    return closestSum == sum;
}