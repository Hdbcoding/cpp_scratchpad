#include <string>
#include "naive.hpp"

using namespace std;

int naive::editDistance(const string &w1, const string& w2)
{
    return recursive(w1, w2, 0, 0);
}

int naive::recursive(const string &w1, const string& w2, int i, int j)
{
    if (j == w2.size())
        return w1.size() - i;

    if (i == w1.size())
        return w2.size() - j;

    if (w1[i] == w2[j])
        return recursive(w1, w2, i + 1, j + 1);

    int doDelete = 1 + recursive(w1, w2, i + 1, j);
    int doInsert = 1 + recursive(w1, w2, i, j + 1);
    int doReplace = 1 + recursive(w1, w2, i + 1, j + 1);

    return min(doDelete, min(doInsert, doReplace));
}