#include <iostream>
#include <chrono>
#include <vector>
#include <algorithm>
#include <random>
#include "naiveslow.hpp"
#include "naive.hpp"
#include "memoizationslow.hpp"
#include "memoization.hpp"
#include "dpslow.hpp"

using namespace std;

typedef chrono::high_resolution_clock _clock;

template <class t>
void test(int cycles, int problemSize, const string &name)
{
    cout << "testing " << name << " with cycles: " << cycles << ", problemSize: " << problemSize << endl;

    t solver;
    auto t1 = _clock::now();

    vector<int> nums{1, 2, 3, 9};
    int diff{3};
    cout << "verify simple case: " << solver.canPartition(nums, diff) << endl;
    nums = {1, 2, 7, 1, 5};
    diff = 0;
    cout << "verify simple case: " << solver.canPartition(nums, diff) << endl;
    nums = {1, 3, 100, 4};
    diff = 92;
    cout << "verify simple case: " << solver.canPartition(nums, diff) << endl;

    default_random_engine dre(t1.time_since_epoch().count());
    uniform_int_distribution<int> di(1, 25);

    nums.assign(problemSize, 0);
    while (cycles-- > 0)
    {
        generate(nums.begin(), nums.end(), [&] { return di(dre); });
        diff = di(dre);
        solver.canPartition(nums, diff);
    }

    auto t2 = _clock::now();
    int elapsed = chrono::duration_cast<chrono::milliseconds>(t2 - t1).count();
    cout << "total test time: " << elapsed << "ms" << endl;
}

int main()
{
    // o(2 ^ n) - quite a bit slower than partition and subsetsum because this solution explores the whole tree
    test<naiveslow>(100, 20, "naive recursive - slow version");
    // when you're exploring the entire recursive tree, memoization provides a real improvement
    test<memoizationslow>(100, 100, "memoized recursive for slow version");
    test<dpslow>(100, 100, "dp for the slow version");

    // like the partition and subsetsum solutions, this skips most of the recursive tree if it finds a solution early
    test<naive>(1000, 10000, "naive recursive");
    // o(n * s) <- depends on s
    // actually much slower than naive, oddly enough
    //   might be a side effect of my number generation
    test<memoization>(100, 100, "memoized recursive");
}