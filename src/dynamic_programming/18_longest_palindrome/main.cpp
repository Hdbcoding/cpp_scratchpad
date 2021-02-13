#include <iostream>
#include <chrono>
#include <algorithm>
#include <random>
#include "naive.hpp"
#include "memoization.hpp"
#include "bottomup.hpp"
#include "nodpn2.hpp"

using namespace std;

typedef chrono::high_resolution_clock _clock;

// longest palindromic substring
// like palindrome, but now the palindrome must be a contiguous substring

// recursively
// two pointers at the ends
// if (left > right) return 0
// if (left == right) return 1
// if [left] == [right], and recurse(left + 1, right - 1) == right - left - 1 is a palindrome, return right - left + 1;
// return max(recurse(left + 1, right), recurse(left, right - 1))

// dynamic programming
// want to build up a table of tested substrings
// instantiation: dp = int[s.size + 1][s.size + 1], all 0
// initialization: dp[i][i] = 1 // every individual letter is a palindomic substring
// induction:
//    if st[i] = st[j] && (length of segment between i and j == dp[i + 1][j - 1])
//       dp[i][j] = dp[i + 1]dp[j - 1] + 2
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
    cout << "verify simple case: " << solver.maxPalindrome("abdbca") << endl;
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
    test<memoization>({500, 200}, "memoization recursive");
    test<bottomup>({500, 200}, "bottom-up dynamic programming");
    test<nodpn2>({2000, 2000}, "no dynamic programming, iterative, O(n^2)");
}