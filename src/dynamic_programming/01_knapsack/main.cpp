#include <iostream>
#include <chrono>
#include <vector>
#include <algorithm>
#include <random>
#include "naive.hpp"
#include "memotable.hpp"
#include "dptable.hpp"
#include "tworowdptable.hpp"
#include "onerowdp.hpp"

using namespace std;

typedef chrono::high_resolution_clock _clock;

// O,1 knapsack
// given a set of unique products {value,weight}
//   and a knapsack with weight capacity
// calculate the most valuable way to pack the knapsack
// a naive recursive solution yields a runtime of O(2^n)
// various memoization/dynamic programming solutions can pull the runtime down to O(n*C)
//    where C is the capacity of the bag
// since the dp table calculations only depend on the previous row and smaller sums, space optimizations can be made to the dp table

// recursive concept:
// recursively consider an item. 
//    if I can fit it in the bag, recursively check how much value I get.
//    also consider how much value I get if I skip this item
//    return the better option

// with dynamic programming:
// dp[items.size()][capacity]
//    dp[i][c] = the best profit I could make with items 0-i, and capacity c
// initialization:
//      dp[0][weights[0]] = profits[0]
// induction:
//      if this item fits, pick this item, and check back in the table for how much profit I have if I pick it
//      or look back for the profit without considering this item
//      dp[i][c] = max(profits[i] + dp[i - 1][c - weights[i]], dp[i - 1][c]);

template <class t>
void test(int cycles, int problemSize, const string &name)
{
    cout << "testing " << name << " with cycles: " << cycles << ", problemSize: " << problemSize << endl;

    t solver;
    auto t1 = _clock::now();

    vector<int> profits{1, 6, 10, 16};
    vector<int> weights{1, 2, 3, 5};
    cout << "verify simple case: " << solver.solveKnapsack(profits, weights, 7) << endl;

    default_random_engine dre(t1.time_since_epoch().count());
    uniform_int_distribution<int> di(1, 100);

    profits.assign(problemSize, 0);
    weights.assign(problemSize, 0);
    int capacity;
    while (cycles-- > 0)
    {
        generate(profits.begin(), profits.end(), [&] { return di(dre); });
        generate(weights.begin(), weights.end(), [&] { return di(dre); });
        capacity = di(dre) * di(dre);
        solver.solveKnapsack(profits, weights, capacity);
    }

    auto t2 = _clock::now();
    int elapsed = chrono::duration_cast<chrono::milliseconds>(t2 - t1).count();
    cout << "total test time: " << elapsed << "ms" << endl;
}

int main()
{
    test<naive>(20, 23, "naive recursive");
    test<memotable>(100, 50, "memo recursive");
    test<dptable>(100, 50, "dp iterative");
    test<tworowdptable>(100, 100, "two-row dp iterative");
    test<onerowdp>(100, 100, "one-row dp iterative");
}