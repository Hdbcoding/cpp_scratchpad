#include <vector>
#include "memoization.hpp"

using namespace std;

int memoization::maxLoot(const vector<int> &loot)
{
    vector<int> memo(loot.size(), 0);
    return recursive(loot, 0, memo);
}

int memoization::recursive(const vector<int> &loot, int index, vector<int> &memo)
{
    if (index >= loot.size())
        return 0;

    if (memo[index] == 0)
        memo[index] = max(loot[index] + recursive(loot, index + 2, memo), recursive(loot, index + 1, memo));

    return memo[index];
}