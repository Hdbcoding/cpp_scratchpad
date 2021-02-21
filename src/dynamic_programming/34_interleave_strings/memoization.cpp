#include <string>
#include <vector>
#include "memoization.hpp"

using namespace std;

bool memoization::interleaved(const string &w1, const string& w2, const string& w3)
{
    vector<vector<int>> memo(w1.size() + 1, vector<int>(w2.size() + 1, -1));
    return recursive(w1, w2, w3, 0, 0, 0, memo);
}

bool memoization::recursive(const string &w1, const string& w2, const string& w3, int i, int j, int k, vector<vector<int>> &memo)
{
    if (i == w1.size() && j == w2.size() && k == w3.size())
        return true;
    
    if (memo[i][j] == -1)
    {
        bool useFirst{false};
        if (i < w1.size() && w1[i] == w3[k])
            useFirst = recursive(w1, w2, w3, i + 1, j, k + 1, memo);

        bool useSecond{false};
        if (!useFirst && j < w2.size() && w2[j] == w3[k])
            useSecond = recursive(w1, w2, w3, i, j + 1, k + 1, memo);

        memo[i][j] = useFirst || useSecond ? 1 : 0;
    }

    return memo[i][j] == 1;
}