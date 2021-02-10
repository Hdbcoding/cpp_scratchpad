#include <vector>
#include <limits>
#include "naive.hpp"

using namespace std;

int naive::minJumps(const vector<int> &jumps)
{
    return recursive(jumps, 0);
}

int naive::recursive(const vector<int> &jumps, int index)
{
    if (index >= jumps.size() - 1)
        return 0;
    if (index + jumps[index] >= jumps.size())
        return 1;
    if (jumps[index] == 0)
        return numeric_limits<int>::max();

    int minJumps = numeric_limits<int>::max();
    for (int i = jumps[index]; i > 0; --i)
    {
        int tryJump = recursive(jumps, index + i);
        if (tryJump != numeric_limits<int>::max())
            minJumps = min(minJumps, tryJump + 1);
    }
    return minJumps;
}