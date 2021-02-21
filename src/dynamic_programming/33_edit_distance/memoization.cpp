#include <string>
#include <vector>
#include "memoization.hpp"

using namespace std;

int memoization::editDistance(const string &w1, const string &w2)
{
    vector<vector<int>> memo(w1.size(), vector<int>(w2.size(), -1));
    return recursive(w1, w2, 0, 0, memo);
}

int memoization::recursive(const string &w1, const string &w2, int i, int j, vector<vector<int>> &memo)
{
    if (j == w2.size())
        return w1.size() - i;

    if (i == w1.size())
        return w2.size() - j;

    if (memo[i][j] == -1)
    {
        int value = 0;
        if (w1[i] == w2[j])
            value = recursive(w1, w2, i + 1, j + 1, memo);
        else
        {
            int doDelete = 1 + recursive(w1, w2, i + 1, j, memo);
            int doInsert = 1 + recursive(w1, w2, i, j + 1, memo);
            int doReplace = 1 + recursive(w1, w2, i + 1, j + 1, memo);
            value = min(doDelete, min(doInsert, doReplace));
        }
        memo[i][j] = value;
    }

    return memo[i][j];
}