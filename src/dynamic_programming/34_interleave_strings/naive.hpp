#include <string>

struct naive
{
    bool interleaved(const std::string &w1, const std::string &w2, const std::string &w3);

private:
    bool recursive(const std::string &w1, const std::string &w2, const std::string &w3, int i, int j, int k);
};