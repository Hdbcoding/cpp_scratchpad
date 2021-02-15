#include <iostream>
#include <chrono>
#include <algorithm>
#include <random>
#include "naive.hpp"
#include "memoization.hpp"
#include "bottomup.hpp"
#include "tworow.hpp"

using namespace std;

typedef chrono::high_resolution_clock _clock;

// longest common subsequence

// recursively, same plan as longest common substring
// except, we don't have to push down the length of the current substring

// dynamic programming
// logic: dp[i][j] is the length of the largest common subsequence achieved when considering w1[0:i] and w2[0:j]
// instantiation: dp = int[w1.size][w2.size]
// initialization: all 0
// induction: if w1[i] == w2[j], dp[i][h] = dp[i-1][j-1] + 1
//            else dp[i][j] = max(dp[i-1][j], dp[i][j-1])
// so, could be solved with a 2-row table

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
    test<memoization>({500, 200}, "memoization recursive");
    test<bottomup>({500, 200}, "bottom-up dynamic programming");
    test<tworow>({500, 200}, "two-row-bottom-up");
}