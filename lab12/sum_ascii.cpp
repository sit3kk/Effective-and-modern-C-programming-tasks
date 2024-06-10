#include <iostream>
#include <fstream>
#include <thread>
#include <future>
#include <vector>
#include <map>

void computeAsciiSum(std::promise<int> &&promise, const std::string &filename)
{
    std::ifstream file(filename);
    int sum = 0;
    char ch;
    if (file.is_open())
    {
        while (file.get(ch))
        {
            sum += static_cast<unsigned char>(ch);
        }
        file.close();
    }
    else
    {
        std::cerr << "Failed to open file: " << filename << std::endl;
    }
    promise.set_value(sum);
    std::cout << "Sum for " << filename << ": " << sum << std::endl;
}

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        std::cout << "Usage: " << argv[0] << " [file1] [file2] ..." << std::endl;
        return 1;
    }

    std::vector<std::future<int>> futures;
    std::vector<std::thread> threads;

    for (int i = 1; i < argc; ++i)
    {
        std::promise<int> promise;
        futures.push_back(promise.get_future());
        threads.emplace_back(computeAsciiSum, std::move(promise), argv[i]);
    }

    for (auto &thread : threads)
    {
        thread.join();
    }

    std::map<int, std::vector<std::string>> sumToFiles;
    for (int i = 1; i < argc; ++i)
    {
        int sum = futures[i - 1].get();
        sumToFiles[sum].push_back(argv[i]);
    }

    for (const auto &pair : sumToFiles)
    {
        if (pair.second.size() > 1)
        {
            std::cout << "Files with ASCII sum " << pair.first << ": ";
            for (const auto &file : pair.second)
            {
                std::cout << file << " ";
            }
            std::cout << std::endl;
        }
    }

    return 0;
}
