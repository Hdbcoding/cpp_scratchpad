#include <string>
#include "naive.hpp"

using namespace std;

int naive::lrs(const string &w)
{
    return recursive(w, 0, 0);
}

int naive::recursive(const string &w, int i, int j)
{
    if (i == w.size() || j == w.size())
        return 0;
    
    if (i != j && w[i] == w[j])
        return 1 + recursive(w, i + 1, j + 1);

    int skipi = recursive(w, i + 1, j);
    int skipj = recursive(w, i, j + 1);
    return max(skipi, skipj);
}