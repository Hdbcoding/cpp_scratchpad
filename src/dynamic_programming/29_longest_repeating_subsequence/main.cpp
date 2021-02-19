#include <iostream>
#include <chrono>
#include <algorithm>
#include <random>
#include "naive.hpp"
#include "memoization.hpp"

using namespace std;

typedef chrono::high_resolution_clock _clock;

// longest repeating subsequence
// given a string, find the longest subsequence of characters that repeats
// between two subsequences, the same character must never appear in the same index of the subsequence

// recursion idea: do a two pointer search for the longest common subsequence as if there were two strings
// but both pointers are in the same string
// and the two pointer indices may not be equal to eachother, but the characters must be equal to each other.

struct settings
{
    int cycles;
    int problemSize;
};

template <class t>
void test(const settings &s, const string &name)
{
    cout << "testing " << name << " with cycles: " << s.cycles << ", problemSize: " << s.problemSize << endl;

    t solver;
    auto t1 = _clock::now();

    cout << "verify simple case: " << solver.lrs("tomorrow") << endl;
    cout << "verify simple case: " << solver.lrs("aabdbcec") << endl;
    cout << "verify simple case: " << solver.lrs("fmff") << endl;
    cout << "verify simple case: " << solver.lrs("dynamic") << endl;

    default_random_engine dre(t1.time_since_epoch().count());
    uniform_int_distribution<char> di_letter('a', 'z');
    uniform_int_distribution<int> di_size(1, s.problemSize);

    int cycles = s.cycles;
    float progress = 0;
    float increment = 1.0 / cycles;
    int width = 25;
    while (cycles-- > 0)
    {
        int s1 = di_size(dre);

        string w1(s1, 'a');

        generate(w1.begin(), w1.end(), [&] { return di_letter(dre); });

        // for less boilerplate, guarantee that the smaller word is second
        solver.lrs(w1);

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
    test<naive>({100, 14}, "naive recursive");
    test<memoization>({500, 250}, "memoization recursive");
}