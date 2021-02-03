#include <vector>
#include "naive.hpp"

using namespace std;

int recursive(const vector<int> &profits, const vector<int> &weights, int capacity, int index)
{
    if (capacity <= 0 || index >= profits.size())
        return 0;

    int profitWith = 0;
    if (weights[index] <= capacity)
        profitWith = profits[index] + recursive(profits, weights, capacity - weights[index], index + 1);

    int profitWithout = recursive(profits, weights, capacity, index + 1);

    return max(profitWith, profitWithout);
}

int naive::solveKnapsack(const vector<int> &profits, const vector<int> &weights, int capacity)
{
    return recursive(profits, weights, capacity, 0);
}