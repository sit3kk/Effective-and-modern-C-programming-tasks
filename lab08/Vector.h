#ifndef LAB8_VECTOR_H
#define LAB8_VECTOR_H

#include <memory>
#include <iostream>
#include <cassert>
#include <vector>
#include <cmath>
#include <string>
#include <stdexcept>

struct SafePolicy
{
  static constexpr bool init = true;
  static constexpr bool check = true;

  static void check_index(size_t index, size_t size)
  {
    if (index >= size)
    {
      throw std::out_of_range("Index out of range");
    }
  }
};

struct FastPolicy
{
  static constexpr bool init = false;
  static constexpr bool check = false;

  static void check_index(size_t index, size_t size) {}
};

struct InitFastPolicy
{
  static constexpr bool init = true;
  static constexpr bool check = false;

  static void check_index(size_t index, size_t size) {}
};

template <typename T>
struct VectorTraits
{
  using param_type = typename std::conditional<
      std::is_arithmetic<T>::value && !std::is_same<T, long double>::value,
      T,
      const T &>::type;

  using scalar_type = typename std::conditional<
      std::is_same<T, std::string>::value,
      int,
      T>::type;

  static T multiply(const scalar_type &a, const T &b)
  {
    if constexpr (std::is_same<T, std::string>::value)
    {
      std::string result;
      for (int i = 0; i < a; ++i)
      {
        result += b;
      }
      return result;
    }
    else
    {
      return a * b;
    }
  }

  static T default_value()
  {
    if constexpr (std::is_arithmetic<T>::value)
    {
      return T{0};
    }
    else if constexpr (std::is_same<T, std::string>::value)
    {
      return T{""};
    }
    else
    {
      return T{};
    }
  }
};

template <typename T, size_t N, typename P = FastPolicy>
class Vector
{
  T data[N];

public:
  typedef T value_type;
  typedef std::size_t size_type;
  typedef T *pointer;
  typedef T &reference;
  typedef const typename VectorTraits<T>::param_type const_reference;

  Vector()
  {
    if constexpr (P::init)
    {
      std::fill(data, data + N, T{});
    }
  }

  Vector(const Vector &v) = default;
  Vector &operator=(const Vector &m) = default;

  Vector(std::initializer_list<T> list)
  {
    if (list.size() > N)
    {
      throw std::out_of_range("Initializer list too long");
    }
    std::copy(list.begin(), list.end(), data);
    if constexpr (P::init)
    {
      std::fill(data + list.size(), data + N, T{});
    }
  }

  size_type size() const
  {
    return N;
  }

  T get(size_t index) const
  {
    if constexpr (P::check)
    {
      P::check_index(index, N);
    }
    return data[index];
  }

  void set(size_t index, const T &value)
  {
    if constexpr (P::check)
    {
      P::check_index(index, N);
    }
    data[index] = value;
  }
  friend Vector operator*(const typename VectorTraits<T>::scalar_type &x, const Vector &v)
  {
    Vector result;
    for (size_t i = 0; i < v.size(); ++i)
    {
      result.set(i, VectorTraits<T>::multiply(x, v.get(i)));
    }
    return result;
  }

  friend std::ostream &operator<<(std::ostream &out, const Vector &v)
  {
    for (size_t i = 0; i < v.size(); ++i)
    {
      out << v.get(i) << " ";
    }
    return out;
  }

  friend std::istream &operator>>(std::istream &in, Vector &v)
  {
    T value;
    for (size_t i = 0; i < v.size(); ++i)
    {
      in >> value;
      if (in)
        v.set(i, value);
    }
    return in;
  }
};

#endif // LAB8_VECTOR_H
