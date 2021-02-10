#include "naive.hpp"

int naive::countWays(int n)
{
    if (n < 0)
        return 0;
    if (n <= 1)
        return 1;

    return countWays(n - 1) + countWays(n - 2) + countWays(n - 3);
}