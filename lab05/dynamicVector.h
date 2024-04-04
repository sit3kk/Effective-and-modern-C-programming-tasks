#ifndef DYNAMIC_VECTOR_H
#define DYNAMIC_VECTOR_H

#include <memory>
#include <iostream>
#include <initializer_list>
#include <algorithm>
#include <stdexcept>

class VectorException : public std::runtime_error
{
public:
  VectorException(const char *message) : std::runtime_error(message) {}
};

template <typename T, size_t N>
class Vector;

template <typename T>
class Vector<T, 0>
{
private:
  std::unique_ptr<T[]> data;
  size_t size_;

public:
  typedef T value_type;
  typedef std::size_t size_type;
  typedef T *pointer;
  typedef T &reference;
  typedef const T &const_reference;

  explicit Vector(size_t size = 0) : size_(size), data(std::make_unique<T[]>(size))
  {
    std::fill_n(data.get(), size_, T{});
  }

  Vector(std::initializer_list<T> list) : Vector(list.size())
  {
    std::copy(list.begin(), list.end(), data.get());
  }

  Vector(const Vector &other) : size_(other.size_), data(std::make_unique<T[]>(other.size_))
  {
    std::copy_n(other.data.get(), other.size_, data.get());
  }

  Vector(Vector &&other) noexcept : size_(other.size_), data(std::move(other.data))
  {
    other.size_ = 0;
  }

  Vector &operator=(const Vector &other)
  {
    if (this != &other)
    {
      Vector temp(other);
      *this = std::move(temp);
    }
    return *this;
  }

  Vector &operator=(Vector &&other) noexcept
  {
    size_ = other.size_;
    data = std::move(other.data);
    other.size_ = 0;
    return *this;
  }

  void resize(size_t newSize)
  {
    std::unique_ptr<T[]> newData = std::make_unique<T[]>(newSize);
    std::fill_n(newData.get(), newSize, T{});
    size_t minSize = std::min(size_, newSize);
    std::copy_n(data.get(), minSize, newData.get());
    data = std::move(newData);
    size_ = newSize;
  }

  friend Vector operator+(const Vector &lhs, const Vector &rhs)
  {
    if (lhs.size_ != rhs.size_)
    {
      throw VectorException("incompatible sizes in Vector::operator+");
    }
    Vector sum(lhs.size_);
    for (size_t i = 0; i < lhs.size_; ++i)
    {
      sum.data[i] = lhs.data[i] + rhs.data[i];
    }
    return sum;
  }

  reference operator[](size_t index)
  {
    return data[index];
  }

  const_reference operator[](size_t index) const
  {
    return data[index];
  }

  size_t size() const
  {
    return size_;
  }

  friend std::ostream &operator<<(std::ostream &os, const Vector &v)
  {
    for (size_t i = 0; i < v.size_; ++i)
    {
      os << v.data[i] << " ";
    }
    return os;
  }
};

#endif
