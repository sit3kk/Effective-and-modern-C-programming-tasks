#include <iostream>
#include <string>
#include <vector>
using namespace std;

template <typename... Types>
class MultiVector;

template <>
class MultiVector<>
{
public:
  template <typename T>
  void push_back(T &&) {}
  void print() const
  {
    cout << endl;
  }
};

template <typename T, typename... Types>
class MultiVector<T, Types...> : public MultiVector<Types...>
{
  vector<T> data;

public:
  using MultiVector<Types...>::push_back;

  void push_back(T arg) { data.push_back(arg); }

  void print() const
  {
    printCurrentVector();
    MultiVector<Types...>::print();
  }

private:
  void printCurrentVector() const
  {
    cout << "[ ";
    for (const auto &item : data)
    {
      cout << item << " ";
    }
    cout << "]";
    if constexpr (sizeof...(Types) > 0)
    {
      cout << " ";
    }
  }
};

int main()
{
  MultiVector<int, string, double> m;
  m.push_back(5);
  m.push_back("text");
  m.push_back(7);
  m.push_back(1.2);
  m.print(); // [ 5 7 ] [ text ] [ 1.2 ]

  auto v = std::move(m); // After move, m is empty
  for (auto x : {1, 2, 3})
  {
    v.push_back(x + 10);
    v.push_back(to_string(x));
    v.push_back(x / 10.0);
  }
  m.print(); // Expected to be empty
  v.print(); // [ 5 7 11 12 13 ] [ text 1 2 3 ] [ 1.2 0.1 0.2 0.3 ]

  MultiVector<int, double, int> w;
  w.push_back(1);
  w.push_back(2.0);
  w.print(); // [ 1 ] [ 2 ] [ ]
}

/*
[ 5 7 ] [ text ] [ 1.2 ]
[ ] [ ] [ ]
[ 5 7 11 12 13 ] [ text 1 2 3 ] [ 1.2 0.1 0.2 0.3 ]
[ 1 ] [ ] [ 2 ] [ ]
 */