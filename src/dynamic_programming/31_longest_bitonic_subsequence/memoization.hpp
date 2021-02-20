#include <vector>

struct memoization
{
    int lbs(const std::vector<int> &);

private:
    int lbs(const std::vector<int> &, int current, int previous, bool increasing,
            std::vector<std::vector<std::vector<int>>> &memo);
};
