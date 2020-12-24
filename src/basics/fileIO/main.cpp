#include <iostream>
#include <fstream>
#include <string>

void demonstrateRawStrings()
{
    // just demonstrating some raw string literals
    // R"(string in here, ignores all special characters except for `)"` )"
    std::string m{R"(c:/a/b/c)"};
    std::cout << m << std::endl;
    // can add any edge delimiter you want to raw string literal to allow )" within the string
    // R"whatever()whatever"
    std::string m2{R"MSG(abc""123::456"d" )"  s"/"\")MSG"};
    std::cout << m2 << std::endl;
}

void write(const std::string &filename)
{
    std::ofstream out{filename};
    // or out.open(filename)

    if (!out.is_open())
    {
        std::cout << "could not open file " << filename << std::endl;
        return;
    }

    out << "Hello world" << std::endl;
    out << 10 << std::endl;

    out.close();
}

bool checkIfStreamState(const std::ifstream &in)
{
    if (!in.is_open())
    {
        std::cout << "file stream failed to open" << std::endl;
        return false;
    }
    else if (in.good())
    {
        std::cout << "file io successful" << std::endl;
        return true;
    }
    else if (in.bad())
    {
        std::cout << "unrecoverable io error" << std::endl;
        return false;
    }
    else if (in.eof())
    {
        std::cout << "end of file reached" << std::endl;
        return false;
    }
    else if (in.fail())
    {
        std::cout << "some io operation failed" << std::endl;
        return false;
    }
}

void read(const std::string &filename)
{
    std::ifstream in{filename};
    // or in.open(filename)

    if (!checkIfStreamState(in))
    {
        return;
    }

    std::string m;
    std::getline(in, m);
    int v{};
    in >> v;
    in >> v;

    checkIfStreamState(in);

    in.close();

    std::cout << m << v << std::endl;
}

int main()
{
    demonstrateRawStrings();
    std::string filename{"data.txt"};
    write(filename);
    read(filename);
}