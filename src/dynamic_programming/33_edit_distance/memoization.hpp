#include <string>
#include <vector>

struct memoization
{
    int editDistance(const std::string &w1, const std::string &w2);

private:
    int recursive(const std::string &w1, const std::string &w2, int i, int j, std::vector<std::vector<int>> &);
};