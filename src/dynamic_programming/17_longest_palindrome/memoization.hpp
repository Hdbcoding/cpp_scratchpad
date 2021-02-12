#include <string>
#include <vector>

struct memoization
{
    int maxPalindrome(const std::string &);

private:
    int recursive(const std::string &s, int left, int right, std::vector<std::vector<int>> &memo);
};