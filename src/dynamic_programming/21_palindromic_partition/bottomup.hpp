#include <string>

struct bottomup
{
    int palindromePartition(const std::string &);

private:
    int recursive(const std::string &s, int left, int right);
};