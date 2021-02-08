#include <vector>
#include <limits>
#include "naive.hpp"

using namespace std;

int recursive(const vector<int> &length, int total, int index)
{
    if (total == 0)
        return 0;

    if (index == length.size())
        return -1;

    int useThisCut = -1;
    if (total >= length[index])
        useThisCut = recursive(length, total - length[index], index);
    
    if (useThisCut != -1)
        useThisCut += 1;

    int skipThisCut = recursive(length, total, index + 1);

    return max(useThisCut, skipThisCut);
}


int naive::maxCuts(const vector<int> &length, int total)
{
    return recursive(length, total, 0);
}