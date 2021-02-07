#include <vector>
#include "memoization.hpp"

using namespace std;

int recursive(const vector<int> &price, int length, int index, vector<vector<int>> &memo)
{
    if (length <= 0 || index == price.size())
        return 0;

    if (memo[index][length] == -1)
    {
        int profitWith = 0;
        if (index < length)
            profitWith = price[index] + recursive(price, length - index - 1, index, memo);

        int profitWithout = recursive(price, length, index + 1, memo);
        memo[index][length] = max(profitWith, profitWithout);
    }

    return memo[index][length];
}


int memoization::solve(const vector<int> &price, int length)
{
    vector<vector<int>> memo(price.size(), vector<int>(length + 1, -1));
    return recursive(price, length, 0, memo);
}