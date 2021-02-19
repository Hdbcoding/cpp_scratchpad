#include <iostream>
#include <chrono>
#include <algorithm>
#include <random>
#include "naive.hpp"
#include "memoization.hpp"
#include "bottomup.hpp"

using namespace std;

typedef chrono::high_resolution_clock _clock;

// subsequence pattern matching
// given a string and a pattern
// find how many times the pattern appears as a subsequence of the string

// naive recursive solution
// idea - pointer to location in word and pattern
//   if at end of word return 0
//   if at end of pattern return 1
//   if word[i] == pattern[j], increment both
//   else, increment i
//   return sum of both choices

// dynamic programming
// idea - dp[i][j] is the count of how many times pattern[0:j] is a subsequence of word[0:i]
// instantiation: dp = int[word.size()][pattern.size()]
// initialization: dp[i][0] = 1 <- the empty pattern matches once
// induction:
//    if we found this pattern character, then we have as many combinations as we had without it
//    if word[i] == pattern[j]
//       dp[i][j] = dp[i-1][j-1]
//    we also have whatever combinations we had without this word character
//    dp[i][j] += dp[i - 1][j]

struct settings
{
    int cycles;
    int wordSize;
    int patternSize;
};

template <class t>
void test(const settings &s, const string &name)
{
    cout << "testing " << name << " with cycles: " << s.cycles << ", wordSize: " << s.wordSize << ", patternSize: " << s.patternSize << endl;

    t solver;
    auto t1 = _clock::now();

    cout << "verify simple case: " << solver.patternMatch("baxmx", "ax") << endl;
    cout << "verify simple case: " << solver.patternMatch("tomorrow", "tor") << endl;

    default_random_engine dre(t1.time_since_epoch().count());
    uniform_int_distribution<char> di_letter('a', 'z');
    uniform_int_distribution<int> di_word(s.patternSize, s.wordSize);
    uniform_int_distribution<int> di_pattern(1, s.patternSize);

    int cycles = s.cycles;
    float progress = 0;
    float increment = 1.0 / cycles;
    int width = 25;
    while (cycles-- > 0)
    {
        int wordSize = di_word(dre);
        int patternSize = di_pattern(dre);

        string word(wordSize, 'a');
        string pattern(patternSize, 'a');

        generate(word.begin(), word.end(), [&] { return di_letter(dre); });
        generate(pattern.begin(), pattern.end(), [&] { return di_letter(dre); });

        // for less boilerplate, guarantee that the smaller word is second
        solver.patternMatch(word, pattern);

        cout << int(progress * 100.0) << "% - ";
        int pwidth = progress * width;
        for (int i = 0; i < pwidth; ++i)
            cout << "*";
        cout << "\r";

        progress += increment;
    }

    cout << endl;

    auto t2 = _clock::now();
    int elapsed = chrono::duration_cast<chrono::milliseconds>(t2 - t1).count();
    cout << "total test time: " << elapsed << "ms" << endl;
}

int main()
{
    test<naive>({500, 300, 100}, "naive recursive");
    test<memoization>({500, 300, 100}, "memoization recursive");
    test<bottomup>({500, 300, 100}, "bottomup dynamic programming");
}