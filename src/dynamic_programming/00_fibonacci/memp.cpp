#include <vector>
#include "memo.hpp"

using namespace std;

int recursiveInner(vector<int> &memoTable, int n)
{
    if (n < 2)
        return n;

    if (memoTable[n] != 0)
        return memoTable[n];

    memoTable[n] = recursiveInner(memoTable, n - 1) + recursiveInner(memoTable, n - 2);
    return memoTable[n];
}

int memo::calculate(int n) const
{
    vector<int> memoTable(n + 1, 0);
    return recursiveInner(memoTable, n);
}