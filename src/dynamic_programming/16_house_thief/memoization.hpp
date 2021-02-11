#include <vector>

struct memoization
{
    int maxLoot(const std::vector<int> &loot);
private:
    int recursive(const std::vector<int> &loot, int index, std::vector<int> &memo);
};