#include <vector>

struct naive
{
    int maxLoot(const std::vector<int> &loot);
private:
    int recursive(const std::vector<int> &loot, int index);
};