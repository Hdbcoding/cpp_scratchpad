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

// rod cutting
// given a set of prices/length ( length, price )
// cut a rod of length l
// to maximize the overall achievable price

// recursively, the solution is almost the same as knapsack
//  for each length, try cutting that length off the rod, or skip it

// dynamic programming
// we either include or exclude each rod length
// instantiation: dp = int[weights.size()][capacity + 1]
// initialization:
//    dp[i][0] = 0 // if the rod is length 0, we can't cut it
// induction
//     don't cut this length: dp[i - 1][c] -- if i > 0
//     cut this length: price[i] + dp[i][c - i - 1] -- if c >= i
//   dp[i][c] = max(dp[i - 1][c], price[i] + dp[c - i - 1])

struct settings
{
    int cycles;
    int problemSize;
    int priceCap{500};
    int lengthCap{200};
};

template <class t>
void test(const settings &s, const string &name)
{
    cout << "testing " << name << " with cycles: " << s.cycles << ", problemSize: " << s.problemSize << endl;

    t solver;
    auto t1 = _clock::now();

    vector<int> price{2, 6, 7, 10, 13};
    int length{5};
    cout << "verify simple case: " << solver.solve(price, length) << endl;

    default_random_engine dre(t1.time_since_epoch().count());
    uniform_int_distribution<int> di_price(1, s.priceCap);
    uniform_int_distribution<int> di_length(1, s.lengthCap);

    int cycles = s.cycles;
    float progress = 0;
    float increment = 1.0 / cycles;
    int width = 25;
    price.assign(s.problemSize, 0);
    while (cycles-- > 0)
    {
        generate(price.begin(), price.end(), [&] { return di_price(dre); });
        sort(price.begin(), price.end());
        length = di_length(dre);
        solver.solve(price, length);

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
    test<naive>({100, 10, 500, 75}, "naive recursive");
    test<memoization>({1000, 100}, "memoization recursive");
    test<bottomup>({1000, 100}, "bottom-up dynamic programming");
}