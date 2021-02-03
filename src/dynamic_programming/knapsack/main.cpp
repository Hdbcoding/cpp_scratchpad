#include <iostream>
#include <chrono>
#include <vector>
#include <algorithm>
#include <random>
#include "naive.hpp"
#include "memotable.hpp"
#include "dptable.hpp"

using namespace std;

typedef chrono::high_resolution_clock _clock;

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
    test<memotable>(100, 50, "dp iterative");
}