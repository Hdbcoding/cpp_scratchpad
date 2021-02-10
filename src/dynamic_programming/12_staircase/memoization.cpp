#include <vector>
#include "memoization.hpp"

using namespace std;

int memoization::countWays(int n)
{
    vector<int> memo(n + 1);
    return recursion(n, memo);
}

int memoization::recursion(int n, vector<int> &memo)
{
    if (n < 0)
        return 0;
    if (n <= 1)
        return 1;

    if (memo[n] == 0)
        memo[n] = recursion(n - 1, memo) + recursion(n - 2, memo) + recursion(n - 3, memo);

    return memo[n];
}