#include <vector>
#include "memoization.hpp"

using namespace std;

int recursive(const vector<int> &weight, const vector<int> &profit, int capacity, int index, vector<vector<int>> &memo)
{
    if (capacity <= 0 || index == weight.size())
        return 0;

    if (memo[index][capacity] == -1)
    {
        int profitWith = 0;
        if (weight[index] <= capacity)
            profitWith = profit[index] + recursive(weight, profit, capacity - weight[index], index, memo);

        int profitWithout = recursive(weight, profit, capacity, index + 1, memo);
        memo[index][capacity] = max(profitWith, profitWithout);
    }
    return memo[index][capacity];
}


int memoization::solve(const vector<int> &weight, const vector<int> &profit, int capacity)
{
    vector<vector<int>> memo(weight.size(), vector<int>(capacity + 1, -1));
    return recursive(weight, profit, capacity, 0, memo);
}