#include <vector>

struct naive
{
    int minJumps(const std::vector<int> &jumps);
private:
    int recursive(const std::vector<int> &jumps, int index);
};