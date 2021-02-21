#include <vector>
struct memoization
{
    int las(const std::vector<int> &);

private:
    int las(const std::vector<int> &, int prev2, int prev, int current, std::vector<std::vector<std::vector<int>>> &memo);
};