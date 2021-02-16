#include <iostream>
#include <chrono>
#include <algorithm>
#include <random>
#include "tworow.hpp"

using namespace std;

typedef chrono::high_resolution_clock _clock;

// minimum deletions and insertions to transform one string to another

// exactly the same as longest common subsequence.
// deletions: longerWord.size() - lcs
// insertions: shorterWord.size() - lcs

ostream &operator<<(ostream &os, pair<int, int> const &a)
{
    return os << "{ " << a.first << ", " << a.second << " }";
}

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

    cout << "verify simple case: " << solver.minEdits("abc", "fbc") << endl;
    cout << "verify simple case: " << solver.minEdits("abdca", "cbda") << endl;
    cout << "verify simple case: " << solver.minEdits("passport", "ppsspt") << endl;

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
        int s2 = di_size(dre);

        string w1(s1, 'a');
        string w2(s1, 'a');

        generate(w1.begin(), w1.end(), [&] { return di_letter(dre); });
        generate(w2.begin(), w2.end(), [&] { return di_letter(dre); });

        // for less boilerplate, guarantee that the smaller word is second
        if (s1 < s2)
            solver.minEdits(w2, w1);
        else
            solver.minEdits(w1, w2);

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
    test<tworow>({500, 200}, "two-row-bottom-up");
}