#include <vector>

struct memoization
{
    int maxSum(const std::vector<int> &);

private:
    int recursive(const std::vector<int> &, int current, int previous, std::vector<std::vector<int>> &memo);
};
