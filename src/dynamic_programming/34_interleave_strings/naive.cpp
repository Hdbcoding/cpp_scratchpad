#include <string>
#include "naive.hpp"

using namespace std;

bool naive::interleaved(const string &w1, const string& w2, const string& w3)
{
    return recursive(w1, w2, w3, 0, 0, 0);
}

bool naive::recursive(const string &w1, const string& w2, const string& w3, int i, int j, int k)
{
    if (i == w1.size() && j == w2.size() && k == w3.size())
        return true;

    bool useFirst{false};
    if (i < w1.size() && w1[i] == w3[k])
        useFirst = recursive(w1, w2, w3, i + 1, j, k + 1);

    bool useSecond{false};
    if (!useFirst && j < w2.size() && w2[j] == w3[k])
        useSecond = recursive(w1, w2, w3, i, j + 1, k + 1);

    return useFirst || useSecond;
}