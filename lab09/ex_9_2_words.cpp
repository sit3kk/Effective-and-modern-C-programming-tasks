#include <iostream>
#include <map>
#include <unordered_map>
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>

using namespace std;

/**
 * Converts a given string to lowercase and removes non-alphanumeric characters.
 * @param[in,out] word The string to be transformed.
 */
void toLowerAlpha(string& word) {
    string cleaned;
    for (char ch : word) {
        if (isalnum(ch)) {
            cleaned += tolower(ch);
        }
    }
    word = cleaned;
}

int main() {
    string word;

    map<string, int> wordsCount;
   

    while (cin >> word) {
        toLowerAlpha(word);  
        if (!word.empty()) {
            wordsCount[word]++;
        }
    }

    
    cout << "Number of distinct words: " << wordsCount.size() << endl;

    
    multimap<int, string, greater<int>> sortedWords;


    for (const auto& pair : wordsCount) {
        sortedWords.insert({pair.second, pair.first});
    }

    cout << "\nThe top 20 most popular words:\n";

    
    int counter = 0;
    for (const auto& pair : sortedWords) {
        cout << pair.second << " : " << pair.first << '\n';
        if (++counter == 20) break;
    }

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