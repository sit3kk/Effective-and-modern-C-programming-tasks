#include <algorithm>
#include <chrono>
#include <iostream>
#include <map>
#include <unordered_map>
#include <vector>
using namespace std;

/**
 * Removes all non alphanumeric characters from given word and converts to lower case.
 * @param[in,out] word on return word consist only of lower case characters.
 */
void toLowerAlpha(std::string &s1) {
    s1.erase(remove_if(s1.begin(), s1.end(), [](const char c) {
      return !isalnum(c);
    }), s1.end());

    transform(s1.begin(), s1.end(), s1.begin(), ::tolower);
}

template <typename T>
void printTopWords(const T &wordCount) {
    std::multimap<int, std::string> countWord;

    for (const auto & [key, value] : wordCount)
        countWord.insert({value, key});

    int count = 0;
    auto iter = countWord.rbegin();
    while (iter != countWord.rend() && count < 20) {
        std::cout << iter->first << ": " << iter->second << std::endl;
        ++iter;
        ++count;
    }
}

int main(){
    const auto start = std::chrono::high_resolution_clock::now();

    int count = 0;
    std::string word;
    //map<string, int> c;
    unordered_map<string, int> c;
    std::vector<int> v;
    while (cin >> word) {
       toLowerAlpha(word);

       if (!word.empty())
           if (c[word]++ == 0) ++count;
    }

    cout << "Number of distinct words : " << count << endl;
    cout << "\nThe top 20 most popular words: \n";

    printTopWords(c);

    const auto end = std::chrono::high_resolution_clock::now();
    const std::chrono::duration<double> duration = end - start;
    std::cout << "\nFunction execution time: " << duration.count() << " seconds" << std::endl;

    return 0;
}
/*
 * Expected output for ./words < hamletEN.txt

Number of distinct words : 4726

The top 20 most popular words:
the : 1145
and : 967
to : 745
of : 673
i : 569
you : 550
a : 536
my : 514
hamlet : 465
in : 437
it : 417
that : 391
is : 340
not : 315
lord : 311
this : 297
his : 296
but : 271
with : 268
for : 248
your : 242

 */