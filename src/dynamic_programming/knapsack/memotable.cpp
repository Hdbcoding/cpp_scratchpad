#include <vector>
#include "memotable.hpp"

using namespace std;

int recursive(const vector<int> &profits, const vector<int> &weights, int capacity, int index, vector<vector<int>> &memo)
{
    if (capacity <= 0 || index >= profits.size())
        return 0;

    if (memo[index][capacity] != -1)
        return memo[index][capacity];

    int profitWith = 0;
    if (weights[index] <= capacity)
        profitWith = profits[index] + recursive(profits, weights, capacity - weights[index], index + 1, memo);

    int profitWithout = recursive(profits, weights, capacity, index + 1, memo);

    memo[index][capacity] = max(profitWith, profitWithout);
    return memo[index][capacity];
}

int memotable::solveKnapsack(const vector<int> &profits, const vector<int> &weights, int capacity)
{
    vector<vector<int>> memo(profits.size(), vector<int>(capacity + 1, -1));
    return recursive(profits, weights, capacity, 0, memo);
}