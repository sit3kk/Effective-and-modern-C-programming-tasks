
#ifndef LAB8_VECTOR_H
#define LAB8_VECTOR_H

#include <memory>
#include <iostream>
#include <cassert>
#include <vector>
#include <cmath>

template <typename T, size_t N >
class Vector {
  T data[N];
 public:
  typedef T value_type;
  typedef std::size_t  size_type;
  typedef T* pointer;
  typedef T& reference;
  typedef const T& const_reference;

  Vector() = default;
  Vector(const Vector & v) = default;
  Vector &operator=(const Vector & m) = default;

  Vector(const std::initializer_list<T> &list){
	std::copy(list.begin(), list.end(), data);
  }
  size_type size() const {
	return N;
  }

  const_reference get(size_type index) const {
	return data[index];
  }

  void set(size_type index, const_reference value) {
	data[index] = value;
  }

  friend Vector operator* (const T & x, const Vector & v ){
	Vector result;
	for(int i=0; i < v.size(); ++i){
	  result.set(i, x * v.get(i));
	}
	return result;
  }

  friend std::ostream &operator<<(std::ostream &out, const Vector & v) {
	for(int i=0; i < v.size(); ++i){
	  out << v.get(i) << " ";
	}
	return out;
  }

  friend std::istream &operator>>(std::istream &in, Vector & v) {
	Vector::value_type value;
	for(int i=0; i < v.size(); ++i){
	  in >> value;
	  if(in)
		v.set(i, value);
	}
	return in;
  }

};

#endif // LAB8_VECTOR_H