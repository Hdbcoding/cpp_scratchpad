#include <vector>
#include "naive.hpp"

using namespace std;

// note to self - this pattern of pushing down the numUsed works here
// but when we convert to memoization, we can't push values down like this
//   results need to trickle up from the bottom, not get pushed down from the top
int recursive(const vector<int> &value, int amount, int numUsed, int index)
{
    if (amount == 0)
        return numUsed;

    if (amount < 0 || index == value.size())
        return 0;

    int useThisCoin = 0;
    if (amount >= value[index])
        useThisCoin = recursive(value, amount - value[index], numUsed + 1, index);
    int skipThisCoin = recursive(value, amount, numUsed, index + 1);

    if (useThisCoin == 0)
        return skipThisCoin;
    if (skipThisCoin == 0)
        return useThisCoin;

    return min(useThisCoin, skipThisCoin);
}


int naive::minCoins(const vector<int> &value, int amount)
{
    return recursive(value, amount, 0, 0);
}