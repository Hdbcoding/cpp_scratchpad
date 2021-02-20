#include <vector>

struct naive
{
    int lbs(const std::vector<int> &);

private:
    int lbs(const std::vector<int> &, int current, int previous, bool increasing);
};
