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

// min jump
// given an array of positive integers
// each integer represents a maximum distance you can jump from this location
// find the minimum number of jumps needed to land at the last location
// (you cannot jump from a 0 space)

// super gross, but I guess recursively you could try every possible length jump.
// if you can reach the end from here, return 1
// if you're at a 0, return -1
// let min = int::max
// for (int i = jumps[current]; i > 0; --i) min = min(min, minJumps(current + i))
// return min

// dynamic programming
// instantiation: dp = int[jumps.size()] (all int::max)
// initialization: dp[jumps.size() - 1] = 0
// induction: dp[i] = min of dp[j] for j in i : i + jumps[i]

struct settings
{
    int cycles;
    int problemSize;
    int jumpCap{15};
};

template <class t>
void test(const settings &s, const string &name)
{
    cout << "testing " << name << " with cycles: " << s.cycles << ", problemSize: " << s.problemSize << endl;

    t solver;
    auto t1 = _clock::now();

    vector<int> jumps{2, 1, 1, 1, 4};
    cout << "verify simple case: " << solver.minJumps(jumps) << endl;
    jumps = {1, 1, 3, 6, 9, 3, 0, 1, 3};
    cout << "verify simple case: " << solver.minJumps(jumps) << endl;

    default_random_engine dre(t1.time_since_epoch().count());
    uniform_int_distribution<int> di_jump(0, s.jumpCap);

    int cycles = s.cycles;
    float progress = 0;
    float increment = 1.0 / cycles;
    int width = 25;
    jumps.assign(s.problemSize, 0);
    while (cycles-- > 0)
    {
        generate(jumps.begin(), jumps.end(), [&] { return di_jump(dre); });

        solver.minJumps(jumps);

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
    test<naive>({100, 30}, "naive recursive");
    test<memoization>({1000, 2000}, "memoization recursive");
    test<bottomup>({1000, 2000}, "bottom-up dynamic programming");
}