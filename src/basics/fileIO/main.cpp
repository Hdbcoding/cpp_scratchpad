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
    std::cout << "writing to file " << filename << std::endl;
    std::ofstream out{filename};
    // or out.open(filename)

    if (!out.is_open())
    {
        std::cout << "could not open file " << filename << std::endl;
        return;
    }

    out << "Hello world" << std::endl;
    out << 10 << std::endl;

    std::string m2{"here's another message"};
    for (char ch : m2)
        out.put(ch);

    out.seekp(5, std::ios::beg);
    out.put('#');

    out.close();
}

void copy(const std::string &src, const std::string &dest)
{
    std::cout << "attempting to copy " << src << " to " << dest << std::endl;
    std::ifstream in{src};
    if (!in)
    {
        std::cout << "could not open " << src << std::endl;
        return;
    }

    std::ofstream out{dest};
    std::string line;
    while (!std::getline(in, line).eof())
    {
        out << line << std::endl;
    }
    in.close();
    out.close();

    std::cout << "finished copying " << src << " to " << dest << std::endl;
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
    return false;
}

void read(const std::string &filename)
{
    std::cout << "reading from file " << filename << std::endl;
    std::ifstream in{filename};
    // or in.open(filename)

    if (!checkIfStreamState(in))
    {
        return;
    }

    in.seekg(5, std::ios::beg);
    std::cout << "current stream position: " << in.tellg() << std::endl;

    std::string m;
    std::getline(in, m);
    int v{};
    in >> v;

    std::cout << m << v << std::endl;

    char ch{};
    while (in.get(ch))
        std::cout << ch;
    std::cout << std::endl;

    checkIfStreamState(in);

    in.close();
}

void editFileFstream(const std::string &filename)
{
    std::cout << "editing file " << filename << std::endl;
    std::fstream fs{filename};
    if (!fs)
    {
        std::cout << filename << " does not exist, creating..." << std::endl;
        std::ofstream o{filename};
        o.close();
        fs.open(filename);
    }

    fs << "Hello world!" << std::endl;

    std::string line;
    fs.seekg(0, std::ios::beg);
    std::getline(fs, line);
    std::cout << line << std::endl;
}

void binaryFile()
{
    int num{12345678};

    // as before, write the number as text data
    std::ofstream out{"numTxt"};
    out << num;

    out.close();
    out.clear();

    // alternatively, write the number as binary data
    out.open("numBin", std::ios::binary | std::ios::out);
    out.write((const char *)&num, sizeof(num));
    out.close();

    int num2{0};
    std::ifstream in{"numBin", std::ios::binary | std::ios::in};
    in.read((char *)&num2, sizeof(num2));
    in.close();

    std::cout << num2 << std::endl;
}

struct Record
{
    int id;
    char name[10];
};

void writeRecord(const Record *p, const std::string &filename)
{
    std::cout << "writing record for " << p->name << " to file " << filename << std::endl;
    std::ofstream out{filename, std::ios::binary | std::ios::out};
    out.write((const char *)p, sizeof(Record));
}

void readRecord(const std::string &filename)
{
    std::cout << "reading record from " << filename << std::endl;
    std::ifstream in{filename, std::ios::binary | std::ios::in};
    Record r;
    in.read((char *)&r, sizeof(Record));
    std::cout << r.id << ": " << r.name << std::endl;
}

int main()
{
    demonstrateRawStrings();
    std::string filename{"data.txt"};
    write("data.txt");
    read("data.txt");
    copy("data1.txt", "data2.txt");
    copy("data.txt", "data2.txt");
    editFileFstream("data3.txt");
    binaryFile();

    Record r{1234, "bob"};
    writeRecord(&r, "bob");
    readRecord("bob");

    return 0;
}