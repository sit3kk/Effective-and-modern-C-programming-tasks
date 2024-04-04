
#ifndef STATIC_VECTOR_H
#define STATIC_VECTOR_H

#include <memory>
#include <iostream>
#include <cassert>
#include <vector>
#include <cmath>

template <typename T, size_t N>
class Vector
{
    T data[N];

public:
    typedef T value_type;
    typedef std::size_t size_type;
    typedef T *pointer;
    typedef T &reference;
    typedef const T &const_reference;

    Vector() : data{} {}

    Vector(const Vector &v)
    {
        std::copy(v.data, v.data + N, data);
    }

    Vector &operator=(const Vector &m)
    {
        std::swap_ranges(data, data + N, m.data);
        return *this;
    }

    Vector(const std::initializer_list<T> &list)
    {
        std::copy(list.begin(), list.end(), data);
        std::fill(data + list.size(), data + N, T{});
    }

    explicit Vector(const Vector<T, 0> &dynamicVector)
    {
        assert(dynamicVector.size() <= N);
        for (size_t i = 0; i < dynamicVector.size(); ++i)
        {
            data[i] = dynamicVector[i];
        }

        for (size_t i = dynamicVector.size(); i < N; ++i)
        {
            data[i] = T{};
        }
    }

    Vector<T, N> operator+(const Vector<T, 0> &dynamicVec) const
    {

        assert(dynamicVec.size() <= N && "Dynamic vector size exceeds static vector capacity.");

        Vector<T, N> result;
        for (size_t i = 0; i < dynamicVec.size(); ++i)
        {
            result[i] = this->data[i] + dynamicVec[i];
        }

        for (size_t i = dynamicVec.size(); i < N; ++i)
        {
            result[i] = this->data[i];
        }
        return result;
    }

    friend Vector operator+(const Vector &u, const Vector &v)
    {
        Vector sum;

        for (size_t i = 0; i < N; ++i)
        {
            sum.data[i] = u.data[i] + v.data[i];
        }
        return sum;
    }

    constexpr size_type size() const
    {
        return N;
    }

    const_reference get(size_type index) const
    {
        return data[index];
    }

    void set(size_type index, const_reference value)
    {
        data[index] = value;
    }

    reference operator[](size_type index)
    {
        return data[index];
    }
    const_reference operator[](size_type index) const
    {
        return data[index];
    }

    friend std::ostream &operator<<(std::ostream &out, const Vector &v)
    {
        for (auto elem : v.data)
        {
            out << elem << " ";
        }
        return out;
    }
};

#endif