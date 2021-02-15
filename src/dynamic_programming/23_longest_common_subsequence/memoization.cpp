#include <string>
#include <vector>
#include "memoization.hpp"

using namespace std;

int memoization::lcs(const string &w1, const string &w2)
{
    vector<vector<int>> memo(w1.size(), vector<int>(w2.size(), -1));
    return lcs(w1, w2, 0, 0, memo);
}

int memoization::lcs(const string &w1, const string &w2, int i1, int i2, vector<vector<int>> &memo)
{
    if (i1 == w1.size() || i2 == w2.size())
        return 0;

    if (memo[i1][i2] == -1)
    {
        int withChar = 0;
        if (w1[i1] == w2[i2])
            withChar = lcs(w1, w2, i1 + 1, i2 + 1, memo) + 1;

        int skip1 = lcs(w1, w2, i1 + 1, i2, memo);
        int skip2 = lcs(w1, w2, i1, i2 + 1, memo);
        memo[i1][i2] = max(withChar, max(skip1, skip2));
    }

    return memo[i1][i2];
}