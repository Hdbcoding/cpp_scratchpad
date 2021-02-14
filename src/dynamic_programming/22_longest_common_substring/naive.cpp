#include <string>
#include "naive.hpp"

using namespace std;

int naive::lcs(const string &w1, const string &w2)
{
    return lcs(w1, w2, 0, 0, 0);
}

int naive::lcs(const string &w1, const string &w2, int i1, int i2, int currentLength)
{
    if (i1 == w1.size() || i2 == w2.size())
        return 0;

    if (w1[i1] == w2[i2])
        currentLength = lcs(w1, w2, i1 + 1, i2 + 1, currentLength + 1);

    int skip1 = lcs(w1, w2, i1 + 1, i2, 0);
    int skip2 = lcs(w1, w2, i1, i2 + 1, 0);
    return max(currentLength, max(skip1, skip2));
}