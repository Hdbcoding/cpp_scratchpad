#include <string>

struct naive
{
    int lrs(const std::string &);

private:
    int recursive(const std::string &w, int i, int j);
};