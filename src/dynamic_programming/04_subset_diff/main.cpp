#include <iostream>
#include <chrono>
#include <vector>
#include <algorithm>
#include <random>
#include "naiveslow.hpp"
#include "memoizationslow.hpp"
#include "dpslow.hpp"

using namespace std;

typedef chrono::high_resolution_clock _clock;

// minimum subset sum difference
// given a set of positive integers, partition the set into two subsets, 
//   and minimize the difference between the sums of the subsets
//   return that difference

// recursively, we check each item and see what the difference would be if we included or excluded that item
//    then, return the smaller difference
//    to do that, we track the left and the right sum, and add the current item to the left or the right sum
//    when we're out of items, return the absolute difference between left and right

// a memoization table can track if we have seen a left-sum and an index already
//   if we're at a left-sum and an index we've already seen, then we already know what the solution will be
//   and we can skip that subproblem

// for dp, we flip this script a bit, and instead do something similar to the equal subset sum partition
// the ideal subset difference would be 0, or sum == totalSum / 2
// for equal subset sum partition, we would define a bool[index][sum] table which tells us if we can construct
//    a subset of a particular size with a particular set of items
// we can reuse the same concept for this problem, 
//    but instead of returning dp[nums.size() - 1][sum / 2] (i.e., can we make a half-size sum?)
//    we find the largest record in the table where we can construct a subset of that size
//    then, we return what the difference would be between that subset size and its counterpart

// instantiation:
//   dp = vector<vector<bool>> [nums.size()][totalSum / 2 + 1]
// initialization:
//   dp[i][0] = true -- we can always construct the empty set
//   dp[0][nums[0]] = true -- we can construct a set containing the first item (if its weight is < totalSum / 2)
// induction:
//   for each index, for each sum, can we construct a subset of size sum with or without item index?
//   with:    dp[i - 1][s - nums[i]] (if s >= nums[i])
//   without: dp[i - 1][s]
//   dp[i][s] = dp[i - 1][s] || dp[i - 1][s - nums[i]]

template <class t>
void test(int cycles, int problemSize, const string &name)
{
    cout << "testing " << name << " with cycles: " << cycles << ", problemSize: " << problemSize << endl;

    t solver;
    auto t1 = _clock::now();

    vector<int> nums{1, 2, 3, 9};
    cout << "verify simple case: " << solver.canPartition(nums) << endl;
    nums = {1, 2, 7, 1, 5};
    cout << "verify simple case: " << solver.canPartition(nums) << endl;
    nums = {1, 3, 100, 4};
    cout << "verify simple case: " << solver.canPartition(nums) << endl;

    default_random_engine dre(t1.time_since_epoch().count());
    uniform_int_distribution<int> di(1, 25);

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
    // o(2 ^ n) - quite a bit slower than partition and subsetsum because this solution explores the whole tree
    test<naiveslow>(100, 20, "naive recursive - slow version");
    // when you're exploring the entire recursive tree, memoization provides a real improvement
    test<memoizationslow>(100, 100, "memoized recursive for slow version");
    test<dpslow>(100, 200, "dp for the slow version");
}