#include <string>
#include "naive.hpp"

using namespace std;

int naive::lcs(const string &w1, const string &w2)
{
    return lcs(w1, w2, 0, 0);
}

int naive::lcs(const string &w1, const string &w2, int i1, int i2)
{
    if (i1 == w1.size() || i2 == w2.size())
        return 0;

    int withChar = 0;
    if (w1[i1] == w2[i2])
        withChar = lcs(w1, w2, i1 + 1, i2 + 1) + 1;

    int skip1 = lcs(w1, w2, i1 + 1, i2);
    int skip2 = lcs(w1, w2, i1, i2 + 1);
    return max(withChar, max(skip1, skip2));
}