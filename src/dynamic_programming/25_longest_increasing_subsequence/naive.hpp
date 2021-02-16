#include <vector>

struct naive
{
    int lis(const std::vector<int> &);

private:
    int recursive(const std::vector<int> &, int current, int previous);
};