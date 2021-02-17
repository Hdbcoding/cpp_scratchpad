#include <vector>

struct naive
{
    int maxSum(const std::vector<int> &);

private:
    int recursive(const std::vector<int> &, int current, int previous);
};
