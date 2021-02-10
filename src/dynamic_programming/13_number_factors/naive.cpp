#include "naive.hpp"

int naive::countWays(int n)
{
    if (n < 0)
        return 0;
    if (n == 0)
        return 1;

    return countWays(n - 1) + countWays(n - 3) + countWays(n - 4);
}