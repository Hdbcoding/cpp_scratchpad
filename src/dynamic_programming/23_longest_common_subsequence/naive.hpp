#include <string>

struct naive
{
    int lcs(const std::string &w1, const std::string &w2);
private:
    int lcs(const std::string &w1, const std::string &w2, int i1, int i2);
};