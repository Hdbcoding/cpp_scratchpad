#include <vector>
struct naive
{
    int las(const std::vector<int> &);

private:
    int las(const std::vector<int> &, int prev2, int prev, int current);
};