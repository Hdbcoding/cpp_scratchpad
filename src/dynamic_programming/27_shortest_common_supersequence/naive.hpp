#include <string>

struct naive
{
    int mcs(const std::string &w1, const std::string &w2);

private:
    int recursive(const std::string &w1, const std::string &w2, int i1, int i2);
};