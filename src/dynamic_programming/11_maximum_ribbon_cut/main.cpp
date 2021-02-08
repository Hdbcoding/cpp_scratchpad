#include <iostream>
#include <chrono>
#include <vector>
#include <algorithm>
#include <random>
#include "naive.hpp"
#include "memoization.hpp"
#include "bottomup.hpp"

using namespace std;

typedef chrono::high_resolution_clock _clock;

// maximum ribbon cut
// given a ribbon of length n
// and a set of possible lengths
// we need to cut the ribbon into pieces with lengths in the set
// return the maximum number of pieces we can cut the ribbon into

// recursive solution
// for each ribbon size, try making this cut or not
//   if the ribbon is 0 length, return 0
//   if we ran out of lengths to consider, return int::max
//   useThisCut = recursive(total - thisLength, index) + 1    (or int::max if we can't make this cut)
//   skipThisCut = recursive(total, index + 1)
//   return max(useThisCut, skipThisCut)

// dynamic programming
// dp[i][l] = maximum number of cuts using lengths [0,i] and total ribbon length l
// instantiation: dp = int[length.size()][total], instantiated to 0
// induction:
//    make this cut: 1 + dp[i][l - length[i]] (if that previous cut exists and worked)
//    skip this cut: dp[i - 1][l] (if that previous cut exists and worked)
//    dp[i][l] = max(makeThisCut, skipThisCut)

struct settings
{
    int cycles;
    int problemSize;
    int lengthCap{500};
    int totalCap{200};
};

template <class t>
void test(const settings &s, const string &name)
{
    cout << "testing " << name << " with cycles: " << s.cycles << ", problemSize: " << s.problemSize << endl;

    t solver;
    auto t1 = _clock::now();

    vector<int> length{2, 3, 5};
    int total{5};
    cout << "verify simple case: " << solver.maxCuts(length, total) << endl;
    length = {2, 3};
    total = 7;
    cout << "verify simple case: " << solver.maxCuts(length, total) << endl;
    length = {3, 5, 7};
    total = 13;
    cout << "verify simple case: " << solver.maxCuts(length, total) << endl;
    length = {3, 5};
    total = 7;
    cout << "verify simple case: " << solver.maxCuts(length, total) << endl;

    default_random_engine dre(t1.time_since_epoch().count());
    uniform_int_distribution<int> di_length(1, s.lengthCap);
    uniform_int_distribution<int> di_total(1, s.totalCap);

    int cycles = s.cycles;
    float progress = 0;
    float increment = 1.0 / cycles;
    int width = 25;
    length.assign(s.problemSize, 0);
    while (cycles-- > 0)
    {
        generate(length.begin(), length.end(), [&] { return di_length(dre); });
        sort(length.begin(), length.end());
        total = di_total(dre);
        solver.maxCuts(length, total);

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
    test<naive>({1000, 70, 500, 100}, "naive recursive");
    test<memoization>({1000, 100}, "memoization recursive");
    test<bottomup>({1000, 100}, "bottom-up dynamic programming");
}