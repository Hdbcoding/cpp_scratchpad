#include <vector>
#include "memoization.hpp"

using namespace std;

int memoization::minCost(const vector<int> &cost)
{
    vector<int> memo(cost.size(), -1);
    return recursive(cost, 0, memo);
}

int memoization::recursive(const vector<int> &cost, int index, vector<int> &memo)
{
    if (index >= cost.size())
        return 0;

    if (memo[index] == -1)
        memo[index] = cost[index] + min(
            recursive(cost, index + 1, memo), 
            min(recursive(cost, index + 2, memo), 
                recursive(cost, index + 3, memo)));

    return memo[index];
}