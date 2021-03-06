#include <iostream>
#include <chrono>
#include <algorithm>
#include <random>
#include "naive.hpp"
#include "memoization.hpp"
#include "bottomup.hpp"
#include "onerow.hpp"

using namespace std;

typedef chrono::high_resolution_clock _clock;

// longest common substring

// naively, compare every substring of w1 to every substring of w2
// return the biggest substring we see

// recursively, keep a pointer to the current index of each string
// if (i1 == w1.size() || i2 == w2.size()) return 0
// int lengthWith = 0; // length with current char
// if w1[i1] == w2[i2]
//   lengthWith = 1 + recursive(i1 + 1, i2 + 1)
// int skip1 = recursive(i1 + 1, i2)
// int skip2 = recursive(i1, i2 + 1)
// return max(lengthWith, skip1, skip2)

// dynamic programming
//  dp[i][j] = maximum length of substring in w1 and w2 ending at w1[i], w2[j]
//  (separately keep track of the max length seen so far)
// instantiation: dp = int[w1.size() + 1][w2.size() + 1]
// initialization: dp[0][j] = dp[i][0] = 0
// induction:
//   if (w1[i] == w2[j])
//     dp[i][j] = 1 + dp[i-1][j-1]
//   else
//     dp[i][j] = 0
//   maxLength = max(maxLength, dp[i][j])

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

    cout << "verify simple case: " << solver.lcs("abdca", "cbda") << endl;
    cout << "verify simple case: " << solver.lcs("passport", "ppsspt") << endl;

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
        if (s1 < s2) solver.lcs(w2, w1);
        else solver.lcs(w1, w2);

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
    test<memoization>({100, 50}, "memoization recursive");
    test<bottomup>({500, 200}, "bottom-up dynamic programming");
    test<onerow>({500, 300}, "one-row dynamic programming");
}