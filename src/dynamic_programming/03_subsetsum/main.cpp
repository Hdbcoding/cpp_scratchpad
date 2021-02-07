#include <iostream>
#include <chrono>
#include <vector>
#include <algorithm>
#include <random>
#include "naive.hpp"
#include "memoization.hpp"
#include "bottomup.hpp"
#include "singlerow.hpp"

using namespace std;

typedef chrono::high_resolution_clock _clock;

// subset sum
//   given a set of positive integers, does there exist a subest with a given sum?
// essentially the same algorithm as equal subset sum partition, but with a specific target sum instead of totalSum / 2

template <class t>
void test(int cycles, int problemSize, const string &name)
{
    cout << "testing " << name << " with cycles: " << cycles << ", problemSize: " << problemSize << endl;

    t solver;
    auto t1 = _clock::now();

    vector<int> nums{1, 2, 3, 7};
    int sum{6};
    cout << "verify simple case: " << solver.canGetSubset(nums, sum) << endl;
    nums = {1, 2, 7, 1, 5};
    sum = 10;
    cout << "verify simple case: " << solver.canGetSubset(nums, sum) << endl;
    nums = {1, 3, 4, 8};
    sum = 6;
    cout << "verify simple case: " << solver.canGetSubset(nums, sum) << endl;

    default_random_engine dre(t1.time_since_epoch().count());
    uniform_int_distribution<int> di(1, 15);

    nums.assign(problemSize, 0);
    while (cycles-- > 0)
    {
        generate(nums.begin(), nums.end(), [&] { return di(dre); });
        sum = di(dre) * di(dre);
        solver.canGetSubset(nums, sum);
    }

    auto t2 = _clock::now();
    int elapsed = chrono::duration_cast<chrono::milliseconds>(t2 - t1).count();
    cout << "total test time: " << elapsed << "ms" << endl;
}

int main()
{
    // o(2 ^ n)
    test<naive>(1000, 10000, "naive recursive");

    // // o(n * s) <- depends on s
    // // actually much slower than naive, oddly enough
    // //   might be a side effect of my number generation
    test<memoization>(1000, 100, "memoized recursive");
    test<bottomup>(1000, 100, "bottom-up dp");
    test<singlerow>(1000, 1000, "single-row dp");
}