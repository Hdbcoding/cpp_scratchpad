#include <iostream>
#include <chrono>
#include <vector>
#include <algorithm>
#include <random>
#include "naive.hpp"
#include "memoization.hpp"
#include "bottomup.hpp"
#include "onerow.hpp"

using namespace std;

typedef chrono::high_resolution_clock _clock;

// count of subset sum
// given a set of positive integers, and a target sum, how many subsets sum to the target sum?

// naively, recursively consider each item
//    consider what sum we would get if we added it to the subset, or not
//    when we recurse to sum == 0, return 1
//    when we recurse to sum < 0 or all nums explored, return 0
//    otherwise return the sum of including and excluding this item

// the dynamic programming solution works basically the same as for subsetsum, partition, etc.
// just, instead of bool[][] (can I construct this?), it's int[][] (how many ways can I construct this?)
// so:
// initialization: dp = int[nums.size()][sum + 1]
// instantiation:
//  dp[i][0] = 1 // there is always one way to construct the empty subset
//  dp[0][nums[0]] = 1 // can construct a subset with the first item, if it's smaller than the target sum
// induction:
//   exclude this item: dp[i - 1][s]
//   include this item: dp[i - 1][s - nums[i]] // assuming s >= nums[i]
//  so dp[i][s] = dp[i - 1][s] + dp[i - 1][s - nums[i]]

template <class t>
void test(int cycles, int problemSize, const string &name)
{
    cout << "testing " << name << " with cycles: " << cycles << ", problemSize: " << problemSize << endl;

    t solver;
    auto t1 = _clock::now();

    vector<int> nums{1, 1, 2, 3};
    int sum{4};
    cout << "verify simple case: " << solver.countSubsets(nums, sum) << endl;
    nums = {1, 2, 7, 1, 5};
    sum = 9;
    cout << "verify simple case: " << solver.countSubsets(nums, sum) << endl;
    nums = {1, 3, 100, 4};

    default_random_engine dre(t1.time_since_epoch().count());
    uniform_int_distribution<int> di_num(1, 25);
    uniform_int_distribution<int> di_sum(1, 200);

    float progress = 0;
    float increment = 1.0 / cycles;
    int width = 25;

    nums.assign(problemSize, 0);
    while (cycles-- > 0)
    {
        generate(nums.begin(), nums.end(), [&] { return di_num(dre); });
        sum = di_sum(dre);
        solver.countSubsets(nums, sum);

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
    test<naive>(100, 20, "naive recursive");
    test<memoization>(1000, 100, "top-down memoization");
    test<bottomup>(1000, 100, "bottom-up dynamic programming");
    test<onerow>(1000, 200, "one-row bottom-up dynamic programming");
}