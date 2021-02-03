#include <vector>
#include "notable.hpp"

using namespace std;

int notable::calculate(int n) const
{
    if (n == 0)
        return 0;

    int l2 = 0;
    int l1 = 1;
    int current = 0;

    for (int i = 2; i <= n; ++i)
    {
        current = l1 + l2;
        l2 = l1;
        l1 = current;
    }

    return current;
}