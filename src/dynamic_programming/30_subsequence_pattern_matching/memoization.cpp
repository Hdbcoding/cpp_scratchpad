#include <string>
#include <vector>
#include "memoization.hpp"

using namespace std;

int memoization::patternMatch(const string &word, const string &pattern)
{
    vector<vector<int>> memo(word.size(), vector<int>(pattern.size(), -1));
    return recursive(word, pattern, 0, 0, memo);
}

int memoization::recursive(const string &word, const string &pattern, int i, int j, vector<vector<int>> &memo)
{
    if (j == pattern.size())
        return 1;
    if (i == word.size())
        return 0;

    if (memo[i][j] == -1)
    {
        int withThis = 0;
        if (word[i] == pattern[j])
            withThis = recursive(word, pattern, i + 1, j + 1, memo);

        int withoutThis = recursive(word, pattern, i + 1, j, memo);

        memo[i][j] = withThis + withoutThis;
    }

    return memo[i][j];
}