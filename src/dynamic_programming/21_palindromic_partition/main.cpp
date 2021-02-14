#include <iostream>
#include <chrono>
#include <algorithm>
#include <random>
#include "naive.hpp"
#include "memoization.hpp"
#include "bottomup.hpp"

using namespace std;

typedef chrono::high_resolution_clock _clock;

// palindromic partition
// cut a string into its largest component palindromes
// return the minimum number of cuts required

// recursively
// two pointers at the ends
// if we have a palindrome or nothing, we don't need to make any cuts
// if (left >= right || isPalindrome(left, right)) return 0
// at most, cut the string into individual characters
// int minCuts = right - left
// for each i between left and right
//   if (isPalindrome(left, i))
//     minCuts = min(minCuts, 1 + findMinCuts(i + 1, right))
// return minCuts

// dynamic programming
// two dp tables
//  isPalindrome: bool[s.size()][s.size()] <- true if substring between i and j is a palindrome
//  cuts: int[s.size()] <- number of cuts needed to partition the substring from i to end into palindromes
// after constructing isPalindrome
// induction for cuts:
//   for (left = end-1; left >= 0; --left)
//     minCuts = s.size()
//     for (right = end - 1; right >= left; --right)
//       if (isPalindrome[left][right])
//         minCuts = right == end - 1 
//             ? 0
//             : min(minCuts, 1 + cuts[right + 1])
//     dp[left] = minCuts

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

    cout << "verify simple case: " << solver.palindromePartition("abdba") << endl;
    cout << "verify simple case: " << solver.palindromePartition("abdbca") << endl;
    cout << "verify simple case: " << solver.palindromePartition("cddpd") << endl;
    cout << "verify simple case: " << solver.palindromePartition("pqr") << endl;
    cout << "verify simple case: " << solver.palindromePartition("pp") << endl;

    default_random_engine dre(t1.time_since_epoch().count());
    uniform_int_distribution<char> di_letter('a', 'z');

    int cycles = s.cycles;
    float progress = 0;
    float increment = 1.0 / cycles;
    int width = 25;
    string phrase(s.problemSize, 'a');
    while (cycles-- > 0)
    {
        generate(phrase.begin(), phrase.end(), [&] { return di_letter(dre); });

        solver.palindromePartition(phrase);

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
    test<naive>({200, 120}, "naive recursive");
    test<memoization>({500, 200}, "memoization recursive");
    test<bottomup>({500, 300}, "bottom-up dynamic programming");
}