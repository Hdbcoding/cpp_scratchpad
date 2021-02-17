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

// maximum sum increasing subsequence
// given an array of integers
// return the sum of the increasing subsequence with the greatest overall sum

// recursion
// consider each number in order
//  if it's bigger than the last number we included and greater than 0, try including it
//  (can skip any number less than 0, because the empty set would suffice if the entire set is negative)
//  either way, also try skipping this number
//  return the greater sum

// dynamic programming
// start with a vector which is a copy of the original nums array
// for each ending index i in 1-nums.size(), and starting index j in 0-i
// if nums[i] > nums[j], dp[i] = dp[j] + nums[i]
// in other words - what would the sum of the sequence be if j were the predecessor of i
// at each iteration, dp[i] will hold the largest increasing subsequence sum 

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

    cout << "verify simple case: " << solver.maxSum({4,1,2,6,10,1,12}) << endl;
    cout << "verify simple case: " << solver.maxSum({-4,10,3,7,15}) << endl;

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
        solver.maxSum(problem);

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
    test<naive>({100, 110, 100}, "naive recursive");
    test<memoization>({500, 200, 100}, "memoization recursive");
    test<bottomup>({500, 200, 100}, "bottom-up dynamic programming");
}