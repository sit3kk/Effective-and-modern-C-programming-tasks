#include <iostream>
#include <type_traits>
#include <utility>
#include <limits>

template <int... Values>
class IntegerList
{
public:
  static constexpr int size = sizeof...(Values);

  template <std::size_t Index>
  static constexpr int get()
  {
    constexpr int values[] = {Values...};
    return values[Index];
  }

  static constexpr int max()
  {
    constexpr int values[] = {Values...};
    int max_val = values[0];
    for (int i = 1; i < size; ++i)
    {
      if (values[i] > max_val)
      {
        max_val = values[i];
      }
    }
    return max_val;
  }
};

template <std::size_t Index, typename IntegerList>
struct getInt;

template <std::size_t Index, int... Values>
struct getInt<Index, IntegerList<Values...>>
{
  static constexpr int value = IntegerList<Values...>::template get<Index>();
};

template <typename List1, typename List2>
struct Join;

template <int... Values1, int... Values2>
struct Join<IntegerList<Values1...>, IntegerList<Values2...>>
{
  using type = IntegerList<Values1..., Values2...>;
};

template <typename List>
struct IsSorted;

template <int First, int Second, int... Rest>
struct IsSorted<IntegerList<First, Second, Rest...>>
{
  static constexpr bool value = (First <= Second) && IsSorted<IntegerList<Second, Rest...>>::value;
};

template <int Last>
struct IsSorted<IntegerList<Last>>
{
  static constexpr bool value = true;
};

template <>
struct IsSorted<IntegerList<>>
{
  static constexpr bool value = true;
};

template <typename List>
struct Max;

template <int First, int... Rest>
struct Max<IntegerList<First, Rest...>>
{
  static constexpr int value = (First > Max<IntegerList<Rest...>>::value) ? First : Max<IntegerList<Rest...>>::value;
};

template <int Last>
struct Max<IntegerList<Last>>
{
  static constexpr int value = Last;
};

template <>
struct Max<IntegerList<>>
{
  static constexpr int value = std::numeric_limits<int>::min();
};

template <int... Values>
std::ostream &operator<<(std::ostream &os, IntegerList<Values...>)
{
  os << "{ ";
  ((os << Values << " "), ...);
  os << "}";
  return os;
}

int main()
{
  using listA = IntegerList<5, -1, 5, 2, 1>;
  using listB = IntegerList<1, 4, 6, 9>;

  std::cout << "List A : " << listA() << std::endl;
  std::cout << "List B : " << listB() << std::endl;

  std::cout << "A[1] = " << getInt<1, listA>::value << std::endl;
  std::cout << "B[3] = " << listB::get<3>() << std::endl;

  static_assert(getInt<1, listA>::value == -1);
  static_assert(listB::get<3>() == 9);
  static_assert(listB::get<1>() == 4);

  std::cout << std::boolalpha;
  std::cout << "Is A sorted? " << IsSorted<listA>::value << std::endl;
  std::cout << "Is B sorted? " << IsSorted<listB>::value << std::endl;

  using listC = Join<listA, listB>::type;

  std::cout << "List C : " << listC() << std::endl;
  std::cout << "Max of list C: " << Max<listC>::value << std::endl;
  std::cout << "Max of list A: " << listA::max() << std::endl;
  static_assert(listC::max() == 9);
  static_assert(listA::max() == 5);

  return 0;
}
