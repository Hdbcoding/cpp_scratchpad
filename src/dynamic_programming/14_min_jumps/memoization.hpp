#include <vector>

struct memoization
{
    int minJumps(const std::vector<int> &jumps);
private:
    int recursive(const std::vector<int> &jumps, int index, std::vector<int> &memo);
};