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

// unbounded knapsack
// given a set of items with { weight, value }
// fill a knapsack with a given capacity with as much value as possible
// an individual item can be taken as many times as you want

// recursively, the solution is almost the same as 0/1 knapsack
//  the only difference, is when we consider using the current item, we don't skip it in recursion, since we might use it multiple times
//  this ends up with a crazy runtime of O(2^(n + C))

// for dynamic programming, we work up in a similar way to 0/1 knapsack
// same idea as before, where we either include or exclude each item
// instantiation: dp = int[weights.size()][capacity + 1]
// initialization:
//    dp[i][0] = 0 // if the knapsack has no capacity, it can't store anything
// induction
//     don't include this: dp[i - 1][c] -- if i > 0
//     include this: dp[i][c - weight[i]] -- if c >= weight[i]
//   dp[i][c] = max(dp[i - 1][c], profit[i] + dp[c - weight[i]])

struct settings
{
    int cycles;
    int problemSize;
    int weightCap{25};
    int profitCap{500};
    int capacityCap{200};
};

template <class t>
void test(const settings &s, const string &name)
{
    cout << "testing " << name << " with cycles: " << s.cycles << ", problemSize: " << s.problemSize << endl;

    t solver;
    auto t1 = _clock::now();

    vector<int> weight{1, 2, 3};
    vector<int> profit{15, 20, 50};
    int capacity{5};
    cout << "verify simple case: " << solver.solve(weight, profit, capacity) << endl;

    default_random_engine dre(t1.time_since_epoch().count());
    uniform_int_distribution<int> di_weight(1, s.weightCap);
    uniform_int_distribution<int> di_profit(1, s.profitCap);
    uniform_int_distribution<int> di_capacity(1, s.capacityCap);

    int cycles = s.cycles;
    float progress = 0;
    float increment = 1.0 / cycles;
    int width = 25;
    weight.assign(s.problemSize, 0);
    profit.assign(s.problemSize, 0);
    while (cycles-- > 0)
    {
        generate(weight.begin(), weight.end(), [&] { return di_weight(dre); });
        generate(profit.begin(), profit.end(), [&] { return di_profit(dre); });
        capacity = di_capacity(dre);
        solver.solve(weight, profit, capacity);

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
    // the naive solution is extremely sensitive to initial conditions
    // having the default weight cap of 200 can make this take 15s+
    //   in bad cases where many weights are small and the cap is big
    test<naive>({100, 8, 25, 500, 100}, "naive recursive");
    test<memoization>({1000, 100, 25, 500, 200}, "memoized recursive");
    test<bottomup>({1000, 100, 25, 500, 200}, "bottom-up dynamic programming");
}