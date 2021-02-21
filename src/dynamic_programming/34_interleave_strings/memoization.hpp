#include <string>
#include <vector>

struct memoization
{
    bool interleaved(const std::string &w1, const std::string &w2, const std::string &w3);

private:
    bool recursive(const std::string &w1, const std::string &w2, const std::string &w3, int i, int j, int k, std::vector<std::vector<int>> &);
};