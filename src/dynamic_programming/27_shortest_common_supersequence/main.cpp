#include <iostream>
#include <chrono>
#include <algorithm>
#include <random>
#include "naive.hpp"
#include "memoization.hpp"
#include "bottomup.hpp"

using namespace std;

typedef chrono::high_resolution_clock _clock;

// shortest common supersequence

// given two strings, find the shortest string that contains both strings as a subsequence

// recursion consider each character of both strings
//  if I have gone past both strings, return 0
//  if I only have one string left, return the number of characters remaining
//  if the current character of each string is the same, return 1 + recurse(i+1, j+1)
//  otherwise, return max(result(i+1, j), recurse(i, j+1))

// dynamic programming
// dp[i][j] should be the minimum length supersequence which contains all of w1[0:i] and w2[0:j]
// instantiation: dp = int[w1.size][w2.size]
// initialization: dp[i][0] = i, dp[0][j] = j
// induction: 
//     if w1[i] == w2[j]
//         dp[i][j] = dp[i-1][j-1] + 1
//     else
//         dp[i][j] = min(dp[i-1][j], dp[i][j-1]) + 1

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

    cout << "verify simple case: " << solver.mcs("abdca", "cbda") << endl;
    cout << "verify simple case: " << solver.mcs("passport", "ppsspt") << endl;
    cout << "verify simple case: " << solver.mcs("abcf", "bdcf") << endl;
    cout << "verify simple case: " << solver.mcs("dynamic", "programming") << endl;

    default_random_engine dre(t1.time_since_epoch().count());
    uniform_int_distribution<char> di_letter('a', 'z');
    uniform_int_distribution<int> di_size(1, s.problemSize);

    int cycles = s.cycles;
    float progress = 0;
    float increment = 1.0 / cycles;
    int width = 25;
    while (cycles-- > 0)
    {
        int s1 = di_size(dre);
        int s2 = di_size(dre);

        string w1(s1, 'a');
        string w2(s1, 'a');

        generate(w1.begin(), w1.end(), [&] { return di_letter(dre); });
        generate(w2.begin(), w2.end(), [&] { return di_letter(dre); });

        // for less boilerplate, guarantee that the smaller word is second
        if (s1 < s2) solver.mcs(w2, w1);
        else solver.mcs(w1, w2);

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
    test<naive>({100, 14}, "naive recursive");
    test<memoization>({500, 200}, "memoization recursive");
    test<bottomup>({500, 200}, "bottomup dynamic programming");
}