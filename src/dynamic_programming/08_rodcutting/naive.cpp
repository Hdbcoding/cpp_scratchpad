#include <vector>
#include "naive.hpp"

using namespace std;

int recursive(const vector<int> &price, int length, int index)
{
    if (length <= 0 || index == price.size())
        return 0;

    int profitWith = 0;
    if (index < length)
        profitWith = price[index] + recursive(price, length - index - 1, index);

    int profitWithout = recursive(price, length, index + 1);
    return max(profitWith, profitWithout);
}


int naive::solve(const vector<int> &price, int length)
{
    return recursive(price, length, 0);
}