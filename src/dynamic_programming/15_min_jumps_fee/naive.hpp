#include <vector>

struct naive
{
    int minCost(const std::vector<int> &cost);
private:
    int recursive(const std::vector<int> &cost, int index);
};