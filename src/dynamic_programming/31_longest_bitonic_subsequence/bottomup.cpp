#include <vector>
#include "bottomup.hpp"

using namespace std;

int bottomup::lbs(const vector<int> &nums)
{
    vector<int> dpF(nums.size(), 1);
    vector<int> dpB(nums.size(), 1);

    for (int i = 1; i < nums.size(); ++i)
    {
        for (int j = 0; j < i; ++j)
        {
            if (nums[i] > nums[j])
            {
                dpF[i] = max(dpF[i], dpF[j] + 1);
            }
        }
    }

    for (int i = nums.size() - 2; i >= 0; --i)
    {
        for (int j = nums.size() - 1; j > i; --j)
        {
            if (nums[i] > nums[j])
                dpB[i] = max(dpB[i], dpB[j] + 1);
        }
    }

    int maxLength{0};
    for (int i = 0; i < nums.size(); ++i)
        maxLength = max(maxLength, dpF[i] + dpB[i]);

    return maxLength - 1;
}