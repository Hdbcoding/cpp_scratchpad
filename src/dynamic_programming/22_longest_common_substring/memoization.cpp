#include <string>
#include <vector>
#include "memoization.hpp"

using namespace std;

int memoization::lcs(const string &w1, const string &w2)
{
    vector<vector<vector<int>>> memo(w1.size(), vector<vector<int>>(w2.size(), vector<int>(w2.size(), -1)));
    return lcs(w1, w2, 0, 0, 0, memo);
}

int memoization::lcs(const string &w1, const string &w2, int i1, int i2, int currentLength, vector<vector<vector<int>>> &memo)
{
    if (i1 == w1.size() || i2 == w2.size())
        return 0;

    if (memo[i1][i2][currentLength] == -1)
    {
        int updatedLength = currentLength;
        if (w1[i1] == w2[i2])
            updatedLength = lcs(w1, w2, i1 + 1, i2 + 1, currentLength + 1, memo);

        int skip1 = lcs(w1, w2, i1 + 1, i2, 0, memo);
        int skip2 = lcs(w1, w2, i1, i2 + 1, 0, memo);
        memo[i1][i2][currentLength] = max(updatedLength, max(skip1, skip2));
    }

    return memo[i1][i2][currentLength];
}