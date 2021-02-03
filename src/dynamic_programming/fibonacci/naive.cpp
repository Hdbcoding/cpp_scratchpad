#include "naive.hpp"

int naive::calculate(int n) const
{
    if (n < 2)
        return n;

    return calculate(n - 1) + calculate(n - 2);
}
