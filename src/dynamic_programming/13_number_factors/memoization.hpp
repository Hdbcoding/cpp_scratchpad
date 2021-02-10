#include <vector>

struct memoization
{
    int countWays(int n);

private:
    int recursion(int n, std::vector<int> &memo);
};