#include <string>
#include <vector>

struct memoization
{
    int lrs(const std::string &);

private:
    int recursive(const std::string &w, int i, int j, std::vector<std::vector<int>> &memo);
};