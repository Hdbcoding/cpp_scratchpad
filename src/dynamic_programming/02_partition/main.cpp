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

template <class t>
void test(int cycles, int problemSize, const string &name)
{
    cout << "testing " << name << " with cycles: " << cycles << ", problemSize: " << problemSize << endl;

    t solver;
    auto t1 = _clock::now();

    vector<int> nums{1, 2, 3, 4};
    cout << "verify simple case: " << solver.canPartition(nums) << endl;
    nums = {1, 1, 3, 4, 7};
    cout << "verify simple case: " << solver.canPartition(nums) << endl;
    nums = {2, 3, 4, 6};
    cout << "verify simple case: " << solver.canPartition(nums) << endl;

    default_random_engine dre(t1.time_since_epoch().count());
    uniform_int_distribution<int> di(1, 15);

    nums.assign(problemSize, 0);
    while (cycles-- > 0)
    {
        generate(nums.begin(), nums.end(), [&] { return di(dre); });
        solver.canPartition(nums);
    }
    
    auto t2 = _clock::now();
    int elapsed = chrono::duration_cast<chrono::milliseconds>(t2 - t1).count();
    cout << "total test time: " << elapsed << "ms" << endl;
}

int main()
{
    // o(2 ^ n)
    test<naive>(1000, 10000, "naive recursive");

    // o(n * s) <- depends on s
    // actually much slower than naive, oddly enough
    //   might be a side effect of my number generation
    test<memoization>(1000, 100, "memoized recursive");
    test<bottomup>(1000, 100, "bottom-up dp");
}