#include <vector>
#include "bottomup.hpp"

using namespace std;

int bottomup::las(const vector<int> &nums)
{
    vector<int> dpd(nums.size(), 1);
    vector<int> dpa(nums.size(), 1);
    int maxLength = 0;

    for (int i = 1; i < nums.size(); ++i)
    {
        for (int j = 0; j < i; ++j)
        {
            if (nums[i] < nums[j])
            {
                dpd[i] = max(dpd[i], dpa[j] + 1);
                maxLength = max(maxLength, dpd[i]);
            }
            else if (nums[i] > nums[j])
            {
                dpa[i] = max(dpa[i], dpd[j] + 1);
                maxLength = max(maxLength, dpa[i]);
            }
        }
    }

    return maxLength;
}