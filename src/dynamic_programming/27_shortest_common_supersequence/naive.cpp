#include <string>
#include "naive.hpp"

using namespace std;

int naive::mcs(const string &w1, const string &w2)
{
    return recursive(w1, w2, 0, 0);
}

int naive::recursive(const string &w1, const string &w2, int i1, int i2)
{
    if (i1 == w1.size() && i2 == w2.size())
        return 0;

    if (i1 == w1.size())
        return w2.size() - i2;

    if (i2 == w2.size())
        return w1.size() - i1;

    if (w1[i1] == w2[i2])
        return recursive(w1, w2, i1 + 1, i2 + 1) + 1;

    int useW1 = 1 + recursive(w1, w2, i1 + 1, i2);
    int useW2 = 1 + recursive(w1, w2, i1, i2 + 1);
    return min(useW1, useW2);
}