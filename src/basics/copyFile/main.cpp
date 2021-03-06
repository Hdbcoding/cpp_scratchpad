#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <filesystem>

void copyChunk(std::ifstream &in, std::ofstream &out, char *buf, int length)
{
    if (!in.read(buf, length))
        throw std::runtime_error("could not read input data");

    if (!out.write(buf, length))
        throw std::runtime_error("could not write output data");
}

void copyChunks(std::ifstream &in, std::ofstream &out, int length)
{
    const unsigned int BUFFER_SIZE = 512;
    char buffer[BUFFER_SIZE]{};
    if (length < BUFFER_SIZE)
    {
        // if the file size is smaller than the buffer, copy in one go
        copyChunk(in, out, buffer, length);
    }
    else
    {
        // otherwise, copy in chunks
        auto chunks{length / BUFFER_SIZE};
        int remaining{length % BUFFER_SIZE};
        int progress{};
        int oldProgress{};
        std::cout << "Progress: ";
        for (int i = 0; i < chunks; i++)
        {
            copyChunk(in, out, buffer, BUFFER_SIZE);
            progress = static_cast<int>(10.0 * static_cast<float>(i) / chunks);
            if (progress != oldProgress)
                std::cout << "." << std::flush;
            oldProgress = progress;
        }

        if (remaining > 0)
        {
            copyChunk(in, out, buffer, remaining);
            std::cout << "." << std::endl;
        }
    }
}

void copyFile(const std::string &src, const std::string &dest)
{
    std::cout << "copying file " << src << " to " << dest << std::endl;

    // check if output exists - complain if does
    if (std::filesystem::exists(dest))
        throw std::runtime_error("output file already exists");

    auto length = std::filesystem::file_size(src);
    std::cout << "total file size of input file: " << length << std::endl;

    // open input file stream
    std::ifstream in{src, std::ios::in | std::ios::binary};
    if (!in)
        throw std::runtime_error("could not open src file");

    // open output file stream
    std::ofstream out{dest, std::ios::out | std::ios::binary};
    if (!out)
        throw std::runtime_error("could not open dest file");

    copyChunks(in, out, length);

    std::cout << "finished copying file " << src << " to " << dest << std::endl;
}

void copyDirectory(const std::string &src, const std::string &dest)
{
    auto found = dest.find('.');
    if (found != std::string::npos)
        throw std::runtime_error("copying to output directory, but it looks like a file path");

    bool outExists = std::filesystem::exists(dest);
    if (!outExists)
        std::filesystem::create_directory(dest);

    std::cout << "Copying all direct child files of " << src << " to " << dest << std::endl;
    for (auto &p : std::filesystem::directory_iterator(src))
    {
        if (p.is_regular_file())
        {
            std::filesystem::path dDir{dest};
            std::filesystem::path filename{p.path().filename()};
            std::filesystem::path dPath = dDir / filename;

            try
            {
                copyFile(p.path().string(), dPath.string());
            }
            catch (std::runtime_error ex)
            {
                std::cout << "error copying " << p.path().string() << " to " << dPath.string() << ": " << ex.what() << std::endl;
            }
        }
        else
        {
            std::cout << p.path() << " is not a regular file, skipping" << std::endl;
        }
    }
}

void copy(const std::string &src, const std::string &dest)
{
    std::cout << "attempting to copy " << src << " to " << dest << std::endl;

    // check if input exists - complain if does not
    if (!std::filesystem::exists(src))
        throw std::runtime_error("input file or directory does not exist");

    // copy cases:
    // inFile to outFile
    //   - inFile must exist
    //   - outFile must not exist
    //   - inFile and outFile extensions must match
    // inFile to outDirectory'
    //   - inFile must exist
    //   - outDirectory need not exist
    //   - must copy inFile.filename to end of outDirectory
    //   - must complain if outDirectory/inFile.filename exists
    // inDirectory to outFile
    //   - treat dest as directory
    // inDirectory to outDirectory
    //   - iterate over each file of inDirectory (recursively?)
    //   - copy inFile to outFile

    bool inFile = std::filesystem::is_regular_file(src);
    bool inDirectory = std::filesystem::is_directory(src);
    bool outExists = std::filesystem::exists(dest);
    bool outDirectory = std::filesystem::is_directory(dest);

    if (!inFile && !inDirectory)
        throw std::runtime_error("input src is not regular file or directory");

    if (outExists && !outDirectory)
        throw std::runtime_error("output file already exists");

    if (inDirectory)
    {
        copyDirectory(src, dest);
    }
    else
    {
        copyFile(src, dest);
    }

    std::cout << "finished copying " << src << " to " << dest << std::endl;
}

// todo - take in arguments to copy files by name
// todo - support detection of file vs directory, for directory copy whole directoyy
// todo - if target directory does not exist, create it
int main(int argc, char **argv)
{
    std::cout << "num arguments: " << argc << std::endl;
    for (int i = 0; i < argc; i++)
    {
        std::cout << "arg " << i << ": " << argv[i] << std::endl;
    }
    // quirk of my debugging setup in vscode, the actual command line arguments i want are in positions 1 and 2
    std::string src{argv[1]};
    std::string dest{argv[2]};

    std::cout << "src: " << src << "; dest: " << dest << std::endl;

    try
    {
        copy(src, dest);
    }
    catch (std::runtime_error ex)
    {
        std::cout << "exception thrown during copy: " << ex.what() << std::endl;
    }

    return 0;
}