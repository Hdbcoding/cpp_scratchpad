#include <vector>
#include "bottomup.hpp"

using namespace std;

int bottomup::lis(const vector<int> &nums)
{
    vector<int> dp(nums.size(), 1);

    int maxLength;
    for (int i = 1; i < nums.size(); ++i)
    {
        for (int j = 0; j < i; ++j)
        {
            if (nums[j] < nums[i] && dp[i] <= dp[j])
            {
                dp[i] = dp[j] + 1;
                maxLength = max(maxLength, dp[i]);
            }
        }
    }
    return maxLength;
}