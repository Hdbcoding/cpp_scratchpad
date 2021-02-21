#include <iostream>
#include <chrono>
#include <algorithm>
#include <random>
#include "naive.hpp"

using namespace std;

typedef chrono::high_resolution_clock _clock;

// edit distance
// given two strings, count the number of edit operations required to transform w1 into w2
// an edit operation is a delete, insert, or replace operation

// recursion
// iterate through the characters of the two strings
// if w1[i] == w2[j], don't need to edit, can recurse(i + 1, j + 1)
// otherwise, try the edit operations:
//   delete from w1: recurse(i + 1, j)
//   insert to w1: recurse(i, j + 1)
//   replace in w1: recurse(i + 1, j + 1)

struct settings
{
    int cycles;
    int wordSize;
};

template <class t>
void test(const settings &s, const string &name)
{
    cout << "testing " << name << " with cycles: " << s.cycles << ", wordSize: " << s.wordSize << endl;

    t solver;
    auto t1 = _clock::now();

    cout << "verify simple case: " << solver.editDistance("bat", "but") << endl;
    cout << "verify simple case: " << solver.editDistance("abdca", "cbda") << endl;
    cout << "verify simple case: " << solver.editDistance("passpot", "ppsspqrt") << endl;

    default_random_engine dre(t1.time_since_epoch().count());
    uniform_int_distribution<char> di_letter('a', 'z');
    uniform_int_distribution<int> di_word(1, s.wordSize);

    int cycles = s.cycles;
    float progress = 0;
    float increment = 1.0 / cycles;
    int width = 25;
    while (cycles-- > 0)
    {
        int ws1 = di_word(dre);
        int ws2 = di_word(dre);

        string w1(ws1, 'a');
        string w2(ws2, 'a');

        generate(w1.begin(), w1.end(), [&] { return di_letter(dre); });
        generate(w2.begin(), w2.end(), [&] { return di_letter(dre); });

        // for less boilerplate, guarantee that the smaller word is second
        solver.editDistance(w1, w2);

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
    test<naive>({100, 12}, "naive recursive");
}