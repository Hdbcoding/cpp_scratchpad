#include <string>
#include "naive.hpp"

using namespace std;

int naive::patternMatch(const string &word, const string& pattern)
{
    return recursive(word, pattern, 0, 0);
}

int naive::recursive(const string &word, const string& pattern, int i, int j)
{
    if (j == pattern.size())
        return 1;
    if (i == word.size())
        return 0;

    int withThis = 0;
    if (word[i] == pattern[j])
        withThis = recursive(word, pattern, i + 1, j + 1);

    int withoutThis = recursive(word, pattern, i + 1, j);

    return withThis + withoutThis;
}