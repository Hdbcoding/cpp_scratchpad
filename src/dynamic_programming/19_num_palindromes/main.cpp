#include <iostream>
#include <chrono>
#include <algorithm>
#include <random>
#include "naive.hpp"
#include "memoization.hpp"
#include "bottomup.hpp"

using namespace std;

typedef chrono::high_resolution_clock _clock;

// count of palindromic substrings
// count all of the palindromic substrings of a string, including nested substrings

// recursively
// two pointers at the ends
// if (left > right) return 0
// if (left == right) return 1
// int total = 0
// if (isPalindrom(left, right))
//    total = 1;
// total += recurse(left + 1, right)
// total += recurse(left, right - 1)
// subtract inner count to avoid double counting
// total -= recurse(left + 1, right - 1)

// dynamic programming
// instantiation: 
//    dp = bool[s.size()][s.size()] <- true if substring is a palindrome
//    count = s.size() // one for each lone letter
// initialization: dp[i][i] = true // each lone letter is a palindrome
// induction:
//   if current chars are the same
//   if s[i] == s[j] 
//      and this is a two char string
//      && ((j - i == 1) 
//         or the inner substring is a palindrome
//         || (dp[i + 1][j - 1]))
//      then this is a palindrome too
//      dp[i][j] = true
//      count++

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

    cout << "verify simple case: " << solver.countPalindromes("abdba") << endl;
    cout << "verify simple case: " << solver.countPalindromes("abdbca") << endl;
    cout << "verify simple case: " << solver.countPalindromes("cddpd") << endl;
    cout << "verify simple case: " << solver.countPalindromes("pqr") << endl;

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

        solver.countPalindromes(phrase);

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
    test<naive>({100, 17}, "naive recursive");
    test<memoization>({500, 200}, "memoization recursive");
    test<bottomup>({1000, 300}, "bottom-up dynamic programming");
}