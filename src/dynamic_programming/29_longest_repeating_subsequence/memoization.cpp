#include <string>
#include <vector>
#include "memoization.hpp"

using namespace std;

int memoization::lrs(const string &w)
{
    vector<vector<int>> memo(w.size(), vector<int>(w.size(), -1));
    return recursive(w, 0, 0, memo);
}

int memoization::recursive(const string &w, int i, int j, vector<vector<int>> &memo)
{
    if (i == w.size() || j == w.size())
        return 0;

    if (memo[i][j] == -1)
    {
        if (i != j && w[i] == w[j])
            return memo[i][j] = 1 + recursive(w, i + 1, j + 1, memo);

        int skipi = recursive(w, i + 1, j, memo);
        int skipj = recursive(w, i, j + 1, memo);
        memo[i][j] = max(skipi, skipj);
    }
    
    return memo[i][j];
}