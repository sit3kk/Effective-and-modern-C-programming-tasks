#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <numeric>
#include <cctype>

template <typename Container>
void print(const Container & c){
    //1.  Print elements of the container separated by ", "
    //    using std::copy and std::ostream_iterator
    // <<>> (1 line)
    std::cout << std::endl;
}

/**
 * Removes all non alphanumeric characters from given word and converts to lower case.
 * @param[in,out] word on return word consist only of lower case characters.
 */
void toLowerAlpha(std::string & s1) {
    //2. Implement using stl algorithms only
    //   Hint: use remove_if, transform, erase
}
/**
  Checks if the first word is an anagram of the second word.

     - All non alphanumeric chars are ignored (remove them).
     - It is case insensitive (convert to lower case).
     - Words cannot be the same (at least one change needed).
     - They should contain the same letters (sort letters in each word to compare).

  @param word1 not empty string
  @param word2 not empty string
  @return true if and only if word1 is an anagram of word2.
*/
bool isAnagram(std::string word1, std::string word2){
//3. Implement isAnagram function using stl algorithms only
//   Hint: use toLowerAlpha, sort, equal
// <<>> (several lines)
    return false;
}
void isAnagramTest(const std::string & s1, const std::string & s2, bool expected){
    std::cout << "isAnagram(\"" << s1 << "\", \""<< s2 << "\") = ";
    bool result = isAnagram(s1, s2);
    std::cout << std::boolalpha << result
      << ((result == expected)? " [OK]": " [ERROR]") << std::endl;
}
int main(){

    constexpr int N = 10;
    std::vector<int> v(N);

    //4. Fill vector v with consecutive numbers starting with -5. (Hint: use std::iota)
    // <<>> (1 line)
    print(v);

    std::vector<int> odd;
    //5. Copy to odd all odd numbers from v (Hint: use copy_if and back_inserter)
    // <<>> (1 line)
    print(odd);

    //6. Each number x in v replace with x*x-1 (Hint std::transform)
    // <<>> (1 line)
    print(v);

    std::vector<int> intersect;
    //7. Sort v and compute intersection of vectors odd and v (treated as sets)
    // <<>> (2 lines)
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
