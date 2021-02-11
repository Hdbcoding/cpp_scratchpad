#include <vector>
#include "novector.hpp"

using namespace std;

int novector::maxLoot(const vector<int> &loot)
{
    int last = 0;
    int current = loot[0];

    for (int i = 1; i < loot.size(); ++i)
    {
        int temp = max(loot[i] + last, current);
        last = current;
        current = temp;
    }

    return current;
}