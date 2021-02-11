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

// min jump with fee
// you are given a staircase with n steps, where each step has a fee
// you can jump 1, 2, or 3 steps from each step
// what is the minimum fee to reach one beyond the last step?

// recursively - like fibonacci
// if at or above top, return 0
// otherwise, return min(recurse(n + 1), recurse(n + 2), recurse(n + 3)) + cost(n)

// dynamic programming
// dp[i] = min cost to get to jump i
// instantiation: dp = int[n]
// initialization: dp[0] = 0
// induction: dp[i] = min(dp[i - 3] + cost[i - 3], dp[i - 2] + cost[i - 2], dp[i - 1] + cost[i - 1])

struct settings
{
    int cycles;
    int problemSize;
    int costCap{15};
};

template <class t>
void test(const settings &s, const string &name)
{
    cout << "testing " << name << " with cycles: " << s.cycles << ", problemSize: " << s.problemSize << endl;

    t solver;
    auto t1 = _clock::now();

    vector<int> cost{1, 2, 5, 2, 1, 2};
    cout << "verify simple case: " << solver.minCost(cost) << endl;
    cost = {2, 3, 4, 5};
    cout << "verify simple case: " << solver.minCost(cost) << endl;

    default_random_engine dre(t1.time_since_epoch().count());
    uniform_int_distribution<int> di_cost(0, s.costCap);

    int cycles = s.cycles;
    float progress = 0;
    float increment = 1.0 / cycles;
    int width = 25;
    cost.assign(s.problemSize, 0);
    while (cycles-- > 0)
    {
        generate(cost.begin(), cost.end(), [&] { return di_cost(dre); });

        solver.minCost(cost);

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
    test<naive>({100, 25}, "naive recursive");
    test<memoization>({1000, 2000}, "memoization recursive");
    test<bottomup>({1000, 2000}, "memoization recursive");
}