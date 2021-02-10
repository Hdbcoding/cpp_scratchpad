#include "novector.hpp"

int novector::countWays(int n)
{
    if (n <= 1)
        return 1;

    // 0
    int old4 = 1;
    // 1
    int old3 = 1;
    // 2
    int old2 = 1;
    // 3
    int old1 = 2;

    for (int i = 4; i <= n; ++i)
    {
        int temp = old1 + old3 + old4;
        old4 = old3;
        old3 = old2;
        old2 = old1;
        old1 = temp;
    }

    return old1;
}