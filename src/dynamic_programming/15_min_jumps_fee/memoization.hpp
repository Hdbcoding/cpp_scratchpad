#include <vector>

struct memoization
{
    int minCost(const std::vector<int> &cost);
private:
    int recursive(const std::vector<int> &cost, int index, std::vector<int> &memo);
};