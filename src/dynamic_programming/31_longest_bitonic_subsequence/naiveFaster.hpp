#include <vector>

struct naiveFaster
{
    int lbs(const std::vector<int> &);

private:
    int lds(const std::vector<int> &, int current, int previous, bool forward);
};
