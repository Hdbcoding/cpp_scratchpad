#include <iostream>
#include <chrono>
#include <algorithm>
#include <random>
#include <vector>
#include "naive.hpp"
#include "naiveSimpler.hpp"
#include "memoization.hpp"

using namespace std;

typedef chrono::high_resolution_clock _clock;

// longest alternating subsequence
// given a set of integers, find the length of the longest alternating sequence
// in an alternating sequence, , for each 3 numbers a, b, c:
//  a < b > c
//  OR
//  a > b < c
//  (no particular relationship between a and c)

// recursion
// for each number, pick it if you can
// need a pointer to the last two numbers
// if num[p2] > num[p], can pick = num[p] < num[current]
// if (num[p2 < num[p]]), can pick = num[p] > num[current]


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

    cout << "verify simple case: " << solver.las({1,2,3,4}) << endl;
    cout << "verify simple case: " << solver.las({3,2,1,4}) << endl;
    cout << "verify simple case: " << solver.las({1,3,2,4}) << endl;

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
        solver.las(problem);

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
    test<naive>({100, 25, 100}, "naive recursive");
    test<naiveSimpler>({100, 25, 100}, "simpler naive recursive");
    test<memoization>({500, 100, 100}, "memoization recursive");
}