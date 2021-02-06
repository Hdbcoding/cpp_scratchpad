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

// equal sumset sum partition
//   given a set of positive integers, can I partition them to create two sets with an equal sum?
// logically, we have the same idea as knapsack:
//    for each item, do I include it in the first set or not?

// skipping the case where the sum of all numbers in the set is odd (answer would be false)
// we can recursively consider if the current number is less than the remaining sum (remaining sum starts as total sum / 2)
//    if it is less, recursively check the next number with the sum reduced by the current number
//    also consider the next number with the same sum
//    return true if either is true

// for dp: dp[i][s] is true if a sum of s can be achieved with a subset of nums 0-i
//  vector<vector<bool>> dp[nums.size()][sum / 2 + 1];
// initialization:
//   a sum of 0 can always be achieved with the empty subset
//   dp[i][0] = true
//   if the 0th number is less than half the total sum, then it can be used to achieve a subset sum by itself
//   dp[0][nums[0]] = true
// induction:
//   like with recursion, see if we have a sum size of s with and without this index
//      with:    dp[i - 1][s - nums[i]] (if s >= nums[i])
//      without: dp[i - 1][s]
//   dp[i][s] = dp[i - 1][s] || dp[i - 1][s - nums[i]];

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