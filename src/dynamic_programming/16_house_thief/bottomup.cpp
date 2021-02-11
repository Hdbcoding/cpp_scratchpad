#include <vector>
#include "bottomup.hpp"

using namespace std;

int bottomup::maxLoot(const vector<int> &loot)
{
    vector<int> dp(loot.size() + 1, 0);
    dp[1] = loot[0];

    for (int i = 1; i < loot.size(); ++i)
        dp[i + 1] = max(loot[i] + dp[i - 1], dp[i]);

    return dp[loot.size()];
}