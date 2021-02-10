#include <iostream>
#include <chrono>
#include "naive.hpp"
#include "memoization.hpp"
#include "bottomup.hpp"
#include "novector.hpp"

using namespace std;

typedef chrono::high_resolution_clock _clock;

// staircase
// given a staircase with n steps
// you can step up one, two, or three stairs at a time
// how many ways can you climb the staircase?

// recursively works a lot like fibonacci
// if negative steps, return 0
// if there are 0 or 1 steps remaining, return 1
// return countWays(n - 1) + countWays(n - 2) + countWays(n - 3)

// dynamic programming:
// instantiation: dp = int[n] 
// initialization: dp[0] = dp[1] = 1
// induction: dp[i] = dp[i - 1] + dp[i - 2] + dp[i - 3]

struct settings
{
    int cycles;
    int steps;
};

template <class t>
void test(const settings &s, const string &name)
{
    cout << "testing " << name << " with cycles: " << s.cycles << ", problemSize: " << s.steps << endl;

    t solver;
    auto t1 = _clock::now();

    cout << "verify simple case: " << solver.countWays(3) << endl;
    cout << "verify simple case: " << solver.countWays(4) << endl;
    cout << "verify simple case: " << solver.countWays(5) << endl;

    int cycles = s.cycles;
    float progress = 0;
    float increment = 1.0 / cycles;
    int width = 25;
    while (cycles-- > 0)
    {
        solver.countWays(s.steps);

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
    test<naive>({50, 30}, "naive recursive");
    test<memoization>({1000, 2000}, "memoization recursive");
    test<bottomup>({1000, 2000}, "bottom-up dynamic programming");
    test<novector>({1000, 2000}, "memory-optimized dynamic programming");
}