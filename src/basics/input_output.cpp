#include <iostream>
// what's up mingw? why does std::string crash on startup?
#include <string>
// makes std:: namespace declaration redundant
using namespace std;

int main() {
    // console IO
    // class templates: std::basic_ostream, std::basic_istream
    // types: std::ostream, std::istream
    // objects: std::cout, std::cin
    // insertion operator: <<
    // extraction operator: >>

    cout << "Printing on the console via the insertion operator" << endl;
    cout << "Can insert primitives: " << 12345 << " " << 1.234f << endl;

    cout << "Tell me an int" << endl;
    int number;
    cin >> number;
    cout << "You gave me the number: " << number << endl;

    cin.clear();
    cin.sync();

    cout << "Tell me a string - using a char[] buffer" << endl;
    char buff[512];
    cin >> buff;
    cout << "You gave me the buffer: " << buff << endl;

    cin.clear();
    cin.sync();

    // after accepting input, typically need to flush the input buffer in some way

    cin.clear();
    cin.sync();

    cout << "Tell me a sentence - using cin.getline" << endl;
    char words[512];
    cin.getline(words, 64, '\n');
    cout << "You gave me the string: " << words << endl;

    // what's up mingw? why does this work with std::string immediately crash on startup?
    cin.clear();
    cin.sync();

    cout << "Tell me a sentence, using std::getline" << endl;
    string words2;
    getline(cin, words2);
    cout << "You gave me the string: " << words2 << endl;

    return 0;
}