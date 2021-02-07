#include <iostream>
#include <chrono>
#include <vector>
#include <algorithm>
#include <random>
#include "naive.hpp"
#include "smarter_naive.hpp"
#include "bottomup.hpp"
#include "singlerow.hpp"

using namespace std;

typedef chrono::high_resolution_clock _clock;

// Target sum
// Given a set of positive integers and a desired sum
// count the number of ways these numbers can be added or subtracted from eachother to get the desired sum

// recursively, let's either add or subtract the current number from the sum
//    return (number of ways if we add this number) + (number of ways if we subtract this number)

// if we're clever we can do some math, and find that we're trying to find a sumset whose size is:
//    (totalSum + targetSum) / 2
//    (failing if this total < target or isOdd(total + target))
//    then we can use the same algorithm as subsetsum_count, trying to find subsets of size (total + target) / 2

template <class t>
void test(int cycles, int problemSize, const string &name)
{
    cout << "testing " << name << " with cycles: " << cycles << ", problemSize: " << problemSize << endl;

    t solver;
    auto t1 = _clock::now();

    vector<int> nums{1, 1, 2, 3};
    int sum{1};
    cout << "verify simple case: " << solver.countWays(nums, sum) << endl;
    nums = {1, 2, 7, 1};
    sum = 9;
    cout << "verify simple case: " << solver.countWays(nums, sum) << endl;

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
        solver.countWays(nums, sum);

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
    test<smarter_naive>(180, 20, "naive recursive, but a little smarter");
    test<bottomup>(500, 100, "bottom-up dynamic programming");
    test<singlerow>(1000, 100, "single-row bottom-up dynamic programming");
}