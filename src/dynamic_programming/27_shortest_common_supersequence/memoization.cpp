#include <string>
#include <vector>
#include "memoization.hpp"

using namespace std;

int memoization::mcs(const string &w1, const string &w2)
{
    vector<vector<int>> memo(w1.size(), vector<int>(w2.size(), -1));
    return recursive(w1, w2, 0, 0, memo);
}

int memoization::recursive(const string &w1, const string &w2, int i1, int i2, vector<vector<int>> &memo)
{
    if (i1 == w1.size() && i2 == w2.size())
        return 0;

    if (i1 == w1.size())
        return w2.size() - i2;

    if (i2 == w2.size())
        return w1.size() - i1;

    if (memo[i1][i2] == -1)
    {
        if (w1[i1] == w2[i2])
            return recursive(w1, w2, i1 + 1, i2 + 1, memo) + 1;

        int useW1 = 1 + recursive(w1, w2, i1 + 1, i2, memo);
        int useW2 = 1 + recursive(w1, w2, i1, i2 + 1, memo);
        memo[i1][i2] = min(useW1, useW2);
    }
    return memo[i1][i2];
}