#include <vector>
#include "naive.hpp"

using namespace std;

int recursive(const vector<int> &value, int amount, int index)
{
    if (amount == 0)
        return 1;

    if (amount < 0 || index == value.size())
        return 0;

    int useThisCoin = 0;
    if (amount >= value[index])
        useThisCoin = recursive(value, amount - value[index], index);
    int skipThisCoin = recursive(value, amount, index + 1);

    return useThisCoin + skipThisCoin;
}


int naive::countWays(const vector<int> &value, int amount)
{
    return recursive(value, amount, 0);
}