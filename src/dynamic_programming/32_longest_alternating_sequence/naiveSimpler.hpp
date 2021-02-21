#include <vector>
struct naiveSimpler
{
    int las(const std::vector<int> &);

private:
    int las(const std::vector<int> &, int prev, int current, bool asc);
};