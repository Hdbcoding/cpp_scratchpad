#include <iostream>
#include <chrono>
#include "naive.hpp"
#include "memo.hpp"
#include "dptable.hpp"
#include "notable.hpp"

using namespace std;

// fibonacci - calculated in many different ways
// f(n) = f(n - 1) + f(n - 2)
// calculated from the top down you get a horrific exponential runtime
// runtime can be saved with memoization or dynamic programming
//  ... or, you could use 3 variables and save on space as well

typedef chrono::high_resolution_clock _clock;

template <class tfib>
void test(int cycles, int depth, const string &name)
{
    cout << "testing " << name << " with cycles: " << cycles << ", depth: " << depth << endl;

    tfib solver;
    auto t1 = _clock::now();

    cout << "check 5: " << solver.calculate(5) << endl;

    while (cycles-- > 0)
    {
        solver.calculate(depth);
    }

    auto t2 = _clock::now();
    int elapsed = chrono::duration_cast<chrono::milliseconds>(t2 - t1).count();
    cout << "total test time: " << elapsed << "ms" << endl;
}

int main()
{
    test<naive>(100, 25, "naive recursive");
    test<memo>(10000, 100, "memo table");
    test<dptable>(10000, 100, "dp table");
    test<notable>(10000, 1000, "no table");
}