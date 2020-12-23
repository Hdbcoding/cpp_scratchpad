#include <iostream>
#include <limits>
#include <memory>
#include <vector>
#include <random>
#include "TestClass.hpp"
#include "LeakyClass.hpp"
#include "NotLeakyClass.hpp"

void ProcessRecordsMalloc(int count)
{
    std::cout << "ProcessRecordsMalloc" << std::endl;
    if (count < 10)
    {
        throw std::out_of_range("Must be greater than 10");
    }
    int *arr = (int *)malloc(count * sizeof(int));
    if (arr == nullptr)
    {
        throw std::runtime_error("Failed to allocate memory");
    }
    for (int i = 0; i < count; ++i)
    {
        arr[i] = i;
    }
    free(arr);
}

void ProcessRecordsNew(int count)
{
    std::cout << "ProcessRecordsNew" << std::endl;
    int *arr2 = new int[count];
    for (int i = 0; i < count; ++i)
    {
        arr2[i] = i;
    }
    delete[] arr2;
}

void ProcessRecordsVector(int count)
{
    std::cout << "ProcessRecordsVector" << std::endl;
    std::vector<int> arr2;
    arr2.reserve(count);
    for (int i = 0; i < count; ++i)
    {
        arr2.push_back(i);
    }
}

void StackVariable()
{
    std::cout << "StackVariable" << std::endl;
    TestClass t;
    throw std::runtime_error("get outaaa heaaaa");
}

void HeapVariable()
{
    std::cout << "HeapVariable" << std::endl;
    TestClass *t = new TestClass();
    throw std::runtime_error("get outaaa heaaaa");
    delete t;
}

void UniquePtr()
{
    std::cout << "UniquePtr" << std::endl;
    std::unique_ptr<TestClass> t{new TestClass()};
    throw std::runtime_error("get outaaa heaaaa");
}

// void processRecord(int i, std::default_random_engine &eng, std::bernoulli_distribution &dist){
//     std::cout << "Processing record # " << i << std::endl;
//     if (!dist(eng))
//         throw std::runtime_error("oof");
// }

void innerExceptions(int count)
{
    std::cout << "ProcessRecordsVector" << std::endl;
    std::vector<int> arr;
    arr.reserve(count);
    for (int i = 0; i < count; ++i)
    {
        arr.push_back(i);
    }

    std::default_random_engine eng;
    std::bernoulli_distribution dist;
    int errCount = 0;
    for (int i = 0; i < count; ++i)
    {
        try
        {
            std::cout << "Processing record # " << i << " ";
            if (!dist(eng))
                throw std::runtime_error("oof");
            std::cout << std::endl;
        }
        catch (std::runtime_error &ex)
        {
            errCount++;
            std::cout << "runtime error wow " << errCount << " " << ex.what() << std::endl;
            if (errCount >= 5)
            {
                std::runtime_error err{"too many errors, quitting"};
                // modify and re-throw original exception
                ex = err;
                throw;
            }
        }
    }
}

void reportExceptions(void (*doSomething)())
{
    try
    {
        doSomething();
    }
    catch (std::runtime_error &ex)
    {
        std::cout << "runtime error wow " << ex.what() << std::endl;
    }
    catch (std::out_of_range &ex)
    {
        std::cout << "out of range wow " << ex.what() << std::endl;
    }
    // thrown if new fails
    catch (std::bad_alloc &ex)
    {
        std::cout << "bad allocation wow " << ex.what() << std::endl;
    }
    // base type catch
    catch (std::exception &ex)
    {
        std::cout << "other exception hmm " << ex.what() << std::endl;
    }
    // wildcard catch - no exception info available!!!
    catch (...)
    {
        std::cout << "I dont know what happened D:" << std::endl;
    }
}

int main()
{
    reportExceptions([] {
        ProcessRecordsMalloc(std::numeric_limits<int>::max());
    });
    reportExceptions([] {
        ProcessRecordsMalloc(0);
    });
    reportExceptions([] {
        ProcessRecordsNew(std::numeric_limits<int>::max());
    });
    reportExceptions([] {
        ProcessRecordsVector(std::numeric_limits<int>::max());
    });
    reportExceptions(StackVariable);
    reportExceptions(HeapVariable);
    reportExceptions(UniquePtr);
    reportExceptions([] {
        innerExceptions(50);
    });
    reportExceptions([] {
        new LeakyClass();
    });
    reportExceptions([] {
        new NotLeakyClass();
    });

    return 0;
}