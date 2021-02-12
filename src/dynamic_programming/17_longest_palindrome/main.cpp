#include <iostream>
#include <chrono>
#include <algorithm>
#include <random>
#include "naive.hpp"
#include "memoization.hpp"
#include "bottomup.hpp"

using namespace std;

typedef chrono::high_resolution_clock _clock;

// longest palindromic subsequence
// given a string, find the longest palindromic subsequence of that string
// a subsequence is a subset of the original string, not necessarily contiguous, in their original order
// palindromic -> [0] == [n-1], [1] == [n-2], etc.

// brute force solution
// two pointers at the ends
//  if [left] == [right] return recurse (left + 1, right - 1) + 2
//  return max (recurse(left + 1, right), recurse(left, right - 1))

// dynamic programming
// want to build up a table of tested subsequences
// instantiation: dp = int[s.size + 1][s.size + 1], all 0
// initialization: dp[i][i] = 1 // every individual letter is a palindomic subsequence
// induction:
//    if st[i] = st[j]
//       dp[i][j] = dp[i + 1]dp[j - 1] + 1
//    else
//       dp[i][j] = max(dp[i + 1][j], dp[i][j - 1]

struct settings
{
    int cycles;
    int problemSize;
};

template <class t>
void test(const settings &s, const string &name)
{
    cout << "testing " << name << " with cycles: " << s.cycles << ", problemSize: " << s.problemSize << endl;

    t solver;
    auto t1 = _clock::now();

    cout << "verify simple case: " << solver.maxPalindrome("abdba") << endl;
    cout << "verify simple case: " << solver.maxPalindrome("cddpd") << endl;
    cout << "verify simple case: " << solver.maxPalindrome("pqr") << endl;

    default_random_engine dre(t1.time_since_epoch().count());
    uniform_int_distribution<char> di_letter('a', 'z');

    int cycles = s.cycles;
    float progress = 0;
    float increment = 1.0 / cycles;
    int width = 25;
    string phrase(s.problemSize, 'a');
    while (cycles-- > 0)
    {
        generate(phrase.begin(), phrase.end(), [&] { return di_letter(dre); });

        solver.maxPalindrome(phrase);

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
    test<naive>({100, 20}, "naive recursive");
    test<memoization>({500, 200}, "naive recursive");
    test<bottomup>({500, 200}, "naive recursive");
}