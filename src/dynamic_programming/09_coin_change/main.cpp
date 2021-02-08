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

// coin change
// given a set of money denominations
// and a given amount of money
// find the number of possible combinations to produce the amount of money with the given sizes of coins

// recursively, try to subtract each size of coin from the total
//   if I have gotten to 0 money, return 1 (found one way)
//   if I am out of coins or have negative money, return 0 (this way doesn't work)
//   return the sum of using this coin or skipping this coin, following the unbounded knapsack pattern

// dynamic programming
// we either include or exclude each coin
// instantiation: dp = int[coin.size()][total + 1]
// initialization:
//    dp[i][0] = 1 // the empty set works when we have no money
// induction
//     don't use this coin: dp[i - 1][c] -- if i > 0
//     use this coin: value[i] + dp[i][c - value[i]] -- if c >= value[i]
//   dp[i][c] = max(dp[i - 1][c], value[i] + dp[i][c - value[i]])

struct settings
{
    int cycles;
    int problemSize;
    int valueCap{500};
    int totalCap{200};
};

template <class t>
void test(const settings &s, const string &name)
{
    cout << "testing " << name << " with cycles: " << s.cycles << ", problemSize: " << s.problemSize << endl;

    t solver;
    auto t1 = _clock::now();

    vector<int> value{1, 2, 3};
    int amount{5};
    cout << "verify simple case: " << solver.countWays(value, amount) << endl;

    default_random_engine dre(t1.time_since_epoch().count());
    uniform_int_distribution<int> di_value(1, s.valueCap);
    uniform_int_distribution<int> di_amount(1, s.totalCap);

    int cycles = s.cycles;
    float progress = 0;
    float increment = 1.0 / cycles;
    int width = 25;
    value.assign(s.problemSize, 0);
    while (cycles-- > 0)
    {
        generate(value.begin(), value.end(), [&] { return di_value(dre); });
        sort(value.begin(), value.end());
        amount = di_amount(dre);
        solver.countWays(value, amount);

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