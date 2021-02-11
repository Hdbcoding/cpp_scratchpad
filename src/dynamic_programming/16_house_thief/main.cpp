#include <iostream>
#include <chrono>
#include <vector>
#include <algorithm>
#include <random>
#include "naive.hpp"
#include "memoization.hpp"
#include "bottomup.hpp"
#include "novector.hpp"

using namespace std;

typedef chrono::high_resolution_clock _clock;

// house thief
// given a set of positive integers representing the possible loot in a row of houses
// and the restriction that you can't steal from two houses in a row
// how should a thief rob the neighborhood to maximize their loot?

// recursively
//   if I'm past the last house, return 0
//   return max(loot[i] + recurse(i + 2), recurse(i + 1))

// dynamic programming
// instantiation: dp = int[loot.size() + 1]
// initialization: dp[1] = loot[0]
// induction: dp[i + 1] = max(dp[i-1] + loot[i], dp[i])

struct settings
{
    int cycles;
    int problemSize;
    int lootCap{15};
};

template <class t>
void test(const settings &s, const string &name)
{
    cout << "testing " << name << " with cycles: " << s.cycles << ", problemSize: " << s.problemSize << endl;

    t solver;
    auto t1 = _clock::now();

    vector<int> loot{2, 5, 1, 3, 6, 2, 4};
    cout << "verify simple case: " << solver.maxLoot(loot) << endl;
    loot = {2, 10, 14, 8, 1};
    cout << "verify simple case: " << solver.maxLoot(loot) << endl;

    default_random_engine dre(t1.time_since_epoch().count());
    uniform_int_distribution<int> di_loot(0, s.lootCap);

    int cycles = s.cycles;
    float progress = 0;
    float increment = 1.0 / cycles;
    int width = 25;
    loot.assign(s.problemSize, 0);
    while (cycles-- > 0)
    {
        generate(loot.begin(), loot.end(), [&] { return di_loot(dre); });

        solver.maxLoot(loot);

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
    test<bottomup>({1000, 2000}, "bottomup dynamic programming");
    test<novector>({1000, 2000}, "memory optimized dynamic programming");
}