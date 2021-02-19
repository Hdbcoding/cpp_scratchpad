#include <string>
#include <vector>

struct memoization
{
    int patternMatch(const std::string &word, const std::string &pattern);

private:
    int recursive(const std::string &word, const std::string &pattern, int i, int j, std::vector<std::vector<int>> &memo);
};