#include <vector>
#include "naive.hpp"

using namespace std;

int naive::minCost(const vector<int> &cost)
{
    return recursive(cost, 0);
}

int naive::recursive(const vector<int> &cost, int index)
{
    if (index >= cost.size())
        return 0;

    return (cost[index] + min(recursive(cost, index + 1), min(recursive(cost, index + 2), recursive(cost, index + 3))));
}