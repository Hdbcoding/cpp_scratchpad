#include <vector>
#include <limits>
#include "memoization.hpp"

using namespace std;

int recursive(const vector<int> &length, int total, int index, vector<vector<int>> &memo)
{
    if (total == 0)
        return 0;

    if (index == length.size())
        return -1;

    if (memo[index][total] == 0)
    {
        int useThisCut = -1;
        if (total >= length[index])
            useThisCut = recursive(length, total - length[index], index, memo);
        
        if (useThisCut != -1)
            useThisCut += 1;

        int skipThisCut = recursive(length, total, index + 1, memo);

        memo[index][total] = max(useThisCut, skipThisCut);
    }

    return memo[index][total];
}


int memoization::maxCuts(const vector<int> &length, int total)
{
    vector<vector<int>> memo(length.size(), vector<int>(total + 1, 0));
    return recursive(length, total, 0, memo);
}