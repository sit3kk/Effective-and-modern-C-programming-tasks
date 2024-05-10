#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <numeric>
#include <cctype>

template <typename Container>
void print(const Container &c)
{
    std::copy(c.begin(), c.end(), std::ostream_iterator<typename Container::value_type>(std::cout, ", "));
    std::cout << std::endl;
}

void toLowerAlpha(std::string &s)
{
    s.erase(std::remove_if(s.begin(), s.end(), [](char c)
                           { return !std::isalnum(c); }),
            s.end());
    std::transform(s.begin(), s.end(), s.begin(), [](char c)
                   { return std::tolower(c); });
}

bool isAnagram(std::string word1, std::string word2)
{
    toLowerAlpha(word1);
    toLowerAlpha(word2);
    if (word1 == word2 || word1.empty() || word2.empty())
        return false;

    std::sort(word1.begin(), word1.end());
    std::sort(word2.begin(), word2.end());
    return word1 == word2;
}

void isAnagramTest(const std::string &s1, const std::string &s2, bool expected)
{
    std::cout << "isAnagram(\"" << s1 << "\", \"" << s2 << "\") = ";
    bool result = isAnagram(s1, s2);
    std::cout << std::boolalpha << result
              << ((result == expected) ? " [OK]" : " [ERROR]") << std::endl;
}

int main()
{
    constexpr int N = 10;
    std::vector<int> v(N);

    // Fill vector v with consecutive numbers starting with -5
    std::iota(v.begin(), v.end(), -5);
    print(v);

    std::vector<int> odd;
    // Copy to odd all odd numbers from v
    std::copy_if(v.begin(), v.end(), std::back_inserter(odd), [](int x)
                 { return x % 2 != 0; });
    print(odd);

    // Each number x in v replace with x*x-1
    std::transform(v.begin(), v.end(), v.begin(), [](int x)
                   { return x * x - 1; });
    print(v);

    std::vector<int> intersect;
    // Sort v and compute intersection of vectors odd and v (treated as sets)
    std::sort(v.begin(), v.end());
    std::sort(odd.begin(), odd.end());
    std::set_intersection(v.begin(), v.end(), odd.begin(), odd.end(), std::back_inserter(intersect));
    print(intersect);

    isAnagramTest("male", "lame", true);
    isAnagramTest(" Ala $%", "%%Ala%%ska%", false);
    isAnagramTest(" Ala $%", "%%la%%a%", true);
    isAnagramTest("A l a", "ALA", false);
}

/* Expected output
 *
-5, -4, -3, -2, -1, 0, 1, 2, 3, 4,
-5, -3, -1, 1, 3,
24, 15, 8, 3, 0, -1, 0, 3, 8, 15,
-1, 3,
isAnagram("male", "lame") = true [OK]
isAnagram(" Ala $%", "%%Ala%%ska%") = false [OK]
isAnagram(" Ala $%", "%%la%%a%") = true [OK]
isAnagram("A l a", "ALA") = false [OK]
 */
