#include <iostream>
#include <chrono>
#include <vector>
#include <algorithm>
#include <random>
#include "naive.hpp"
#include "memoization.hpp"

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
}