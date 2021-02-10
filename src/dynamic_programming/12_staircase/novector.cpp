#include "novector.hpp"

int novector::countWays(int n)
{
    if (n <= 1)
        return 1;

    // 0
    int old3 = 1;
    // 1
    int old2 = 1;
    // 2
    int old1 = 2;

    for (int i = 3; i <= n; ++i)
    {
        int temp = old1 + old2 + old3;
        old3 = old2;
        old2 = old1;
        old1 = temp;
    }

    return old1;
}