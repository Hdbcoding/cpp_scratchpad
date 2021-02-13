#include <string>
#include <vector>

struct memoization
{
    int countPalindromes(const std::string &);

private:
    int recursive(const std::string &s, int left, int right, std::vector<std::vector<int>> &memo);
    bool isPalindrome(const std::string &s, int left, int right);
};