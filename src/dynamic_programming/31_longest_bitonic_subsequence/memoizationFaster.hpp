#include <vector>

struct memoizationFaster
{
    int lbs(const std::vector<int> &);

private:
    int lds(const std::vector<int> &, int current, int previous, bool forward, std::vector<std::vector<int>> &memo);
};
