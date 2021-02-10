#include <iostream>
#include <chrono>
#include "naive.hpp"
#include "memoization.hpp"
#include "bottomup.hpp"
#include "novector.hpp"

using namespace std;

typedef chrono::high_resolution_clock _clock;

// number factors
// given a number n
// count the number of ways you can add {1, 3, 4} together to get n
// reorderings are counted as distinct

// recursively
// if < 0 return 0
// if = 0 return 1
// return countWays(n - 1) + countWays(n - 3) + countWays(n - 4)

// dynamic programming:
// instantiation: dp = int[n] 
// initialization: dp[0] = dp[1] = 1
// induction: dp[i] = dp[i - 1] + dp[i - 3] + dp[i - 4]

struct settings
{
    int cycles;
    int number;
};

template <class t>
void test(const settings &s, const string &name)
{
    cout << "testing " << name << " with cycles: " << s.cycles << ", problemSize: " << s.number << endl;

    t solver;
    auto t1 = _clock::now();

    cout << "verify simple case: " << solver.countWays(4) << endl;
    cout << "verify simple case: " << solver.countWays(5) << endl;

    int cycles = s.cycles;
    float progress = 0;
    float increment = 1.0 / cycles;
    int width = 25;
    while (cycles-- > 0)
    {
        solver.countWays(s.number);

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
    test<novector>({1000, 2000}, "memory optimized dynamic programming");
}