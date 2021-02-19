#include <string>

struct naive
{
    int patternMatch(const std::string &word, const std::string &pattern);

private:
    int recursive(const std::string &word, const std::string &pattern, int i, int j);
};