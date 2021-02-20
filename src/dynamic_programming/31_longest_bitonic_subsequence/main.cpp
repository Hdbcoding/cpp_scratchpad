#include <iostream>
#include <chrono>
#include <algorithm>
#include <random>
#include <vector>
#include "naive.hpp"
#include "naiveFaster.hpp"
#include "memoization.hpp"
#include "memoizationFaster.hpp"
#include "bottomup.hpp"

using namespace std;

typedef chrono::high_resolution_clock _clock;

// longest bitonic subsequence
// given a set of integers, find the length of the longest bitonic subsequence
// a bitonic subsequence is monotonically increasing, then monotonically decreasing

// recursion
// concept - every number might be the peak of its subsequence
// so, we want the longest decreasing subsequence in both directions from every index, choose the biggest
// alternatively
// for each number
// if I am increasing
//   tryIncreasing
// also
//   tryDecreasing
// return the better result

// dynamic programming
// concept: one vector each for forward and reverse direction longest-decreasing-subsequence
// calculate each
// return max(sum(dp1[i] + dp2[i])) - 1 (double counting the center)
// as for longest decreasing subsequence:
// instantiation: dp = int[nums.size()]
// induction:
//    for i : nums.size()
//    for j < i
//       if (nums[i] < nums[j])
//          dp[i] = max(dp[i], dp[j] + 1);


struct settings
{
    int cycles;
    int problemSize;
    int maxValue;
};

template <class t>
void test(const settings &s, const string &name)
{
    cout << "testing " << name << " with cycles: " << s.cycles << ", problemSize: " << s.problemSize << endl;

    t solver;
    auto t1 = _clock::now();

    cout << "verify simple case: " << solver.lbs({4,2,3,6,10,1,12}) << endl;
    cout << "verify simple case: " << solver.lbs({4,2,5,9,7,6,10,3,1}) << endl;

    default_random_engine dre(t1.time_since_epoch().count());
    uniform_int_distribution<int> di_value(-1 * s.maxValue, s.maxValue);

    int cycles = s.cycles;
    float progress = 0;
    float increment = 1.0 / cycles;
    int width = 25;
    vector<int> problem(s.problemSize);
    while (cycles-- > 0)
    {
        generate(problem.begin(), problem.end(), [&] { return di_value(dre); });

        // for less boilerplate, guarantee that the smaller word is second
        solver.lbs(problem);

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
    test<naive>({100, 30, 100}, "naive recursive");
    test<naiveFaster>({100, 50, 100}, "naive recursive, should be faster");
    test<memoization>({100, 50, 100}, "memoization recursive");
    test<memoizationFaster>({500, 200, 100}, "memoization recursive, should be faster");
    test<bottomup>({500, 200, 100}, "bottom-up dynamic programming");
}