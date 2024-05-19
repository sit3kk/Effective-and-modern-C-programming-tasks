#include <iostream>
#include <fstream>
#include <vector>
#include <map>
using namespace std;
/**
 * Trie structure
 *
 * HINT: use std::map to implement it!
 *       My implementation adds less than 25 lines of code.
 */
class Trie
{
private:
    struct TrieNode
    {
        map<string, TrieNode *> children;
        bool isEndOfSentence;
        TrieNode() : isEndOfSentence(false) {}
    };

    TrieNode *root;

    void addHelper(TrieNode *node, const vector<string> &sentence, int index)
    {
        if (index == sentence.size())
        {
            node->isEndOfSentence = true;
            return;
        }
        if (node->children.find(sentence[index]) == node->children.end())
        {
            node->children[sentence[index]] = new TrieNode();
        }
        addHelper(node->children[sentence[index]], sentence, index + 1);
    }

    void printEndingsHelper(TrieNode *node, vector<string> currentSentence)
    {
        if (node->isEndOfSentence)
        {
            printSentence(currentSentence);
            cout << endl;
        }
        for (auto &child : node->children)
        {
            currentSentence.push_back(child.first);
            printEndingsHelper(child.second, currentSentence);
            currentSentence.pop_back();
        }
    }

    TrieNode *findNode(TrieNode *node, const vector<string> &sentence, int index)
    {
        if (index == sentence.size())
        {
            return node;
        }
        if (node->children.find(sentence[index]) == node->children.end())
        {
            return nullptr;
        }
        return findNode(node->children[sentence[index]], sentence, index + 1);
    }

    void deleteTrie(TrieNode *node)
    {
        for (auto &child : node->children)
        {
            deleteTrie(child.second);
        }
        delete node;
    }

public:
    Trie()
    {
        root = new TrieNode();
    }

    ~Trie()
    {
        deleteTrie(root);
    }

    static void printSentence(const vector<string> &sentence)
    {
        for (const auto &w : sentence)
            cout << w << " ";
    }

    void add(const vector<string> &sentence)
    {
        cout << "Adding: ";
        printSentence(sentence);
        cout << "\n";
        addHelper(root, sentence, 0);
    }

    void printPossibleEndings(const vector<string> &beginningOfSentence)
    {
        cout << "Endings for \"";
        printSentence(beginningOfSentence);
        cout << "\" are:\n";
        TrieNode *node = findNode(root, beginningOfSentence, 0);
        if (node)
        {
            printEndingsHelper(node, beginningOfSentence);
        }
        else
        {
            cout << "No endings found.\n";
        }
    }

    void load(const string &fileName)
    {
        ifstream file(fileName);
        if (!file)
        {
            cerr << "Error opening file " << fileName << endl;
            return;
        }
        string word;
        vector<string> sentence;
        while (file >> word)
        {
            sentence.push_back(word);

            if (word.find_last_of('.') != string::npos)
            {
                add(sentence);
                sentence.clear();
            }
        }
    }
};

int main()
{
    Trie dictionary;
    dictionary.load("../sample.txt");
    // dictionary.load("hamletEN.txt");

    dictionary.printPossibleEndings({"Curiosity"});
    dictionary.printPossibleEndings({"Curiosity", "killed"});
    dictionary.printPossibleEndings({"The", "mouse", "was", "killed"});

    /* cout << "Beginning of sentence (ended with single .): ";
    string word;
    vector<string> sentence;
    while(true){
        cin >> word;
        if(word == ".")
            break;
        sentence.push_back(word);
        dictionary.printPossibleEndings(sentence);
    }*/
    return 0;
}
/* Expected output:
Adding : Curiosity killed the cat.
Adding : Curiosity killed the mouse.
Adding : Curiosity saved the cat.
Adding : Curiosity killed the cat and the mouse.
Adding : The cat was killed by curiosity.
Adding : The mouse was killed by cat.
Adding : The mouse was killed by curiosity.
Endings for "Curiosity " are :
 > killed the cat.
 > killed the mouse.
 > killed the cat and the mouse.
 > saved the cat.

Endings for "Curiosity killed " are :
 > killed the cat.
 > killed the mouse.
 > killed the cat and the mouse.

Endings for "The mouse was killed " are :
 > by cat.
 > by curiosity.

 */