#include <vector>
#include <limits>
#include "bottomup.hpp"

using namespace std;

int bottomup::minJumps(const vector<int> &jumps)
{
    vector<int> dp(jumps.size(), numeric_limits<int>::max());

    for (int i = jumps.size() - 2; i >= 0; --i)
    {
        if (i + jumps[i] >= jumps.size() - 1)
        {
            dp[i] = 1;
            continue;
        }

        int minJumps = dp[i];
        for (int j = i + jumps[i]; j > i; --j)
        {
            minJumps = min(minJumps, dp[j] + 1);
        }
        dp[i] = minJumps;
    }

    return dp[0];
}