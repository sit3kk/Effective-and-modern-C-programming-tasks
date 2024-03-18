#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;
class Printer
{
  ostream &out;
  string prefix;
  string postfix;

public:
  Printer(ostream &output, const string &pre, const string &post)
      : out(output), prefix(pre), postfix(post) {}

  template <typename T>
  void operator()(const T &x) const
  {
    out << prefix << x << postfix;
  }
};

int main()
{
  /// Creates unary functor that takes one argument x (of any type)
  /// and outputs to given stream x surrounded by given prefix na postfix
  /// e.g. in the following  [ x ]
  /// Hint: define function template.
  Printer printer(std::cout, "[ ", " ] ");
  printer("hello"); // [ hello ]
  std::cout << "\nv = ";
  std::vector<int> v = {1, 2, 3, 4};
  std::for_each(v.begin(), v.end(), printer); // v = [ 1 ] [ 2 ] [ 3 ] [ 4 ]
  std::cout << std::endl;

  std::ofstream file("myFile.txt");
  if (!file.is_open())
  {
    std::cerr << "Failed to open myFile.txt" << std::endl;
    return -1;
  }
  Printer filePrinter(file, "- ", "\n");
  filePrinter(5);
  filePrinter("My text");
  file.close();
  return 0;
}
/** myFile.txt
- 5
- My text
*/
