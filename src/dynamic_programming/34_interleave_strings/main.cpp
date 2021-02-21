#include <iostream>
#include <chrono>
#include <algorithm>
#include <random>
#include "naive.hpp"
#include "memoization.hpp"

using namespace std;

typedef chrono::high_resolution_clock _clock;

// interleave strings
// given 3 strings, find out if the 3rd string could be constructed by interleaving the first two
// interleaving would maintain the relative order of the characters in the strings

// recursion, use 3 pointers
// if I have reached the end of all strings, return true
// if I can't make any matches, return false
// if the first word matches, see if the rest matches
// if the second word matches, see if the rest matches

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

    cout << "verify simple case: " << solver.interleaved("abd", "cef", "abcdef") << endl;
    cout << "verify simple case: " << solver.interleaved("abd", "cef", "adcbef") << endl;
    cout << "verify simple case: " << solver.interleaved("abc", "def", "abdccf") << endl;
    cout << "verify simple case: " << solver.interleaved("abcdef", "mnop", "mnaobcdepf") << endl;

    default_random_engine dre(t1.time_since_epoch().count());
    uniform_int_distribution<char> di_letter('a', 'z');
    uniform_int_distribution<int> di_word(1, s.wordSize);
    uniform_int_distribution<int> di_coin(0, 1);

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
        string w3(ws1 + ws2, 'a');

        generate(w1.begin(), w1.end(), [&] { return di_letter(dre); });
        generate(w2.begin(), w2.end(), [&] { return di_letter(dre); });

        if (di_coin(dre) == 0)
        {
            // generate an interleaved string
            int j = 0;
            int k = 0;
            for (int i = 0; i < w3.size(); ++i)
            {
                if (j < ws1 && k < ws2)
                {
                    if (di_coin(dre) == 0)
                    {
                        w3[i] = w1[j++];
                    }
                    else
                    {
                        w3[i] = w2[k++];
                    }
                }
                else if (j < ws1)
                {
                    w3[i] = w1[j++];
                }
                else if (k < ws2)
                {
                    w3[i] = w2[k++];
                }
            }
            // sometimes shuffle that string
            if (di_coin(dre) == 0) 
                shuffle(w3.begin(), w3.end(), dre);
        }
        // sometimes generate a random string
        else
            generate(w3.begin(), w3.end(), [&] { return di_letter(dre); });

        solver.interleaved(w1, w2, w3);

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
    test<naive>({1000, 1000}, "naive recursive");
    test<memoization>({1000, 200}, "memoization recursive");
}