#include <vector>
#include "naive.hpp"

using namespace std;

int naive::maxLoot(const vector<int> &loot)
{
    return recursive(loot, 0);
}

int naive::recursive(const vector<int> &loot, int index)
{
    if (index >= loot.size())
        return 0;

    return max(loot[index] + recursive(loot, index + 2), recursive(loot, index + 1));
}