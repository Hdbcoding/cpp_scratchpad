#include <vector>
#include <limits>
#include "memoization.hpp"

using namespace std;

int memoization::minJumps(const vector<int> &jumps)
{
    vector<int> memo(jumps.size());
    return recursive(jumps, 0, memo);
}

int memoization::recursive(const vector<int> &jumps, int index, vector<int> &memo)
{
    if (index >= jumps.size() - 1)
        return 0;
    if (index + jumps[index] >= jumps.size())
        return 1;
    if (jumps[index] == 0)
        return numeric_limits<int>::max();

    if (memo[index] == 0)
    {
        int minJumps = numeric_limits<int>::max();
        for (int i = jumps[index]; i > 0; --i)
        {
            int tryJump = recursive(jumps, index + i, memo);
            if (tryJump != numeric_limits<int>::max())
                minJumps = min(minJumps, tryJump + 1);
        }
        memo[index] = minJumps;
    }

    return memo[index];
}