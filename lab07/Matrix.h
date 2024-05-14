#ifndef MATRIX_H
#define MATRIX_H
#pragma include once

#include <algorithm>
#include <iomanip>
#include <iostream>
using namespace std;

template <typename T, size_t N, size_t M>
class Matrix {
    T data[N*M];
public:
    static constexpr size_t numberOfRows() noexcept { return N; }
    static constexpr size_t numberOfColumns() noexcept { return M; }

    Matrix() noexcept {
        std::fill_n(data, N*M, T{});
    }

    Matrix(const std::initializer_list<std::initializer_list<T>>& list) {
        T* p = data;
        for (const auto& row : list) {
            T* p2 = std::copy(row.begin(), row.end(), p);
            std::fill(p2, p += M, T{});
        }
    }

    Matrix(const Matrix& m) noexcept {
        std::copy_n(m.data, N*M, data);
    }

    Matrix& operator=(const Matrix& m) noexcept {
        if (&m != this) {
            std::copy_n(m.data, N*M, data);
        }
        return *this;
    }

    T& operator()(const int i, const int j) {
        return data[(i-1)*M + j-1];
    }

    const T& operator()(const int i, const int j) const {
        return data[(i-1)*M + j-1];
    }

    friend Matrix operator+(const Matrix& a, const Matrix &b) noexcept {
        Matrix r;
        for (int i = 1; i <= N; ++i)
            for (int j = 1; j <= M; ++j)
                r(i,j) = a(i,j) + b(i,j);
        return r;
    }

    class iterator {
        T* current_ptr;
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = ptrdiff_t;
        using pointer = T*;
        using reference = T&;

        explicit iterator(pointer p) : current_ptr(p) {}

        reference operator*() const { return *current_ptr; }
        pointer operator->() const { return current_ptr; }

        iterator& operator++() {
            ++current_ptr;
            return *this;
        }

        iterator operator++(int) {
            iterator temp = *this;
            ++(*this);
            return temp;
        }

        bool operator==(const iterator& other) const { return current_ptr == other.current_ptr; }
        bool operator!=(const iterator& other) const { return current_ptr != other.current_ptr; }
    };

    iterator begin() { return iterator(data); }
    iterator end() { return iterator(data + N*M); }

    class const_iterator {
        const T* current_ptr;
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = const T;
        using difference_type = ptrdiff_t;
        using pointer = const T*;
        using reference = const T&;

        explicit const_iterator(pointer p) : current_ptr(p) {}

        reference operator*() const { return *current_ptr; }
        pointer operator->() const { return current_ptr; }

        const_iterator& operator++() {
            ++current_ptr;
            return *this;
        }

        const_iterator operator++(int) {
            const_iterator temp = *this;
            ++(*this);
            return temp;
        }

        bool operator==(const const_iterator& other) const { return current_ptr == other.current_ptr; }
        bool operator!=(const const_iterator& other) const { return current_ptr != other.current_ptr; }
    };

    const_iterator begin() const { return const_iterator(data); }
    const_iterator end() const { return const_iterator(data + N*M); }

    class row_iterator {
        T* ptr;
    public:
        explicit row_iterator(T* start) : ptr(start) {}

        T& operator*() const { return *ptr; }

        row_iterator& operator++() {
            ++ptr;
            return *this;
        }

        row_iterator operator++(int) {
            row_iterator temp = *this;
            ++(*this);
            return temp;
        }

        bool operator==(const row_iterator& other) const { return ptr == other.ptr; }
        bool operator!=(const row_iterator& other) const { return ptr != other.ptr; }
    };

    row_iterator row_begin(size_t row) { return row_iterator(data + (row - 1) * M); }
    row_iterator row_end(size_t row) { return row_iterator(data + row * M); }

    class col_iterator {
        T* ptr;
    public:
        explicit col_iterator(T* start) : ptr(start) {}

        T& operator*() const { return *ptr; }

        col_iterator& operator++() {
            ptr += M;
            return *this;
        }

        col_iterator operator++(int) {
            col_iterator temp = *this;
            ++(*this);
            return temp;
        }

        bool operator==(const col_iterator& other) const { return ptr == other.ptr; }
        bool operator!=(const col_iterator& other) const { return ptr != other.ptr; }
    };

    col_iterator col_begin(size_t col) { return col_iterator(data + (col - 1)); }
    col_iterator col_end(size_t col) { return col_iterator(data + (col - 1) + M * N); }
};

template <typename T, size_t N, size_t M>
void printMatrix(const Matrix<T,N,M>& m, const int width = 10) {
    for (int i = 1; i <= m.numberOfRows(); ++i) {
        for (int j = 1; j <= m.numberOfColumns(); ++j) {
            if (j != 1)
                cout << " ";
            cout << setw(width) <<  m(i,j) ;
        }
        cout << endl;
    }
}
#endif // MATRIX_H
