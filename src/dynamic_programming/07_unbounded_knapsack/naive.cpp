#include <vector>
#include "naive.hpp"

using namespace std;

int recursive(const vector<int> &weight, const vector<int> &profit, int capacity, int index)
{
    if (capacity <= 0 || index == weight.size())
        return 0;

    int profitWith = 0;
    if (weight[index] <= capacity)
        profitWith = profit[index] + recursive(weight, profit, capacity - weight[index], index);

    int profitWithout = recursive(weight, profit, capacity, index + 1);
    return max(profitWith, profitWithout);
}


int naive::solve(const vector<int> &weight, const vector<int> &profit, int capacity)
{
    return recursive(weight, profit, capacity, 0);
}