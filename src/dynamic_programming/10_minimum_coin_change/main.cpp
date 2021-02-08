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
// find the smallest number of coins needed to make up that amount

// recursively, try to subtract each size of coin from the total
//   if I have gotten to 0 money, return numUsed
//   if I am out of coins or have negative money, return 0 (this way doesn't work)
//   return the lesser of using this coin or skipping this coin, following the unbounded knapsack pattern

// note to self - this pattern of pushing down the numUsed works here
// but when we convert to memoization, we can't push values down like this
//   results need to trickle up from the bottom, not get pushed down from the top

// so, to solve that problem:
//   if I have 0 money, return 0
//   if i have pushed past all of the coins, I didn't find a combo at all - return int--max
//   when checking useThisCoin, if there is a combination (e.g. result < int max), add 1 to it
//   return the min of useThisCoin, skipThisCoin

// dynamic programming:
//   dp[i][a] = minimum number of coins needed for coins 0:i to produce value of a
// instantiation: dp = int[values.size()][amount + 1] <- all values set to int max
// initialization:
//   dp[i][0] = 0 <- takes 0 coins to produce a total amount of 0
// induction:
//   use this coin: dp[i][a - value[i] + 1]
//   skip this coin: dp[i - 1][a]

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
    cout << "verify simple case: " << solver.minCoins(value, amount) << endl;
    amount = 11;
    cout << "verify simple case: " << solver.minCoins(value, amount) << endl;

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
        solver.minCoins(value, amount);

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