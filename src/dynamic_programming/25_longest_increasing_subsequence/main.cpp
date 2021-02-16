#include <iostream>
#include <chrono>
#include <algorithm>
#include <random>
#include <vector>
#include "naive.hpp"
#include "memoization.hpp"
#include "bottomup.hpp"

using namespace std;

typedef chrono::high_resolution_clock _clock;

// longest increasing subsequence
// given an array of positive integers
// what is the length of the longest subsequence where the elements are strictly increasing?

// recursion:
// consider each number in order
//   if we're past the end of the set, return 0
//   if it's bigger than the last number we included, try including it
//   either way, try skipping it
//   return the better result

// dynamic programming
// idea - start with a vector of all 1 - a number by itself is an increasing subsequence
// for each ending index [1 : nums.size]
// for each previous index [0 : i]
//   if nums[i] > nums[j] - dp[i] = dp[j] + 1

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

    cout << "verify simple case: " << solver.lis({4,2,3,6,10,1,12}) << endl;
    cout << "verify simple case: " << solver.lis({-4,10,3,7,15}) << endl;

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
        solver.lis(problem);

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
    test<naive>({100, 60, 100}, "naive recursive");
    test<memoization>({500, 200, 100}, "memoization recursive");
    test<bottomup>({1000, 500, 100}, "bottom-up dynamic programming recursive");
}