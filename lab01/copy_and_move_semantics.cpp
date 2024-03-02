#include <iostream>
#include <initializer_list>
#include <algorithm>
#include <utility>

class Matrix
{
public:
    size_t n = 0;
    size_t m = 0;
    int *data = nullptr;

public:
    Matrix() : n(0), m(0), data(nullptr)
    {
        std::cout << "default constructor" << std::endl;
    }

    Matrix(size_t n, size_t m) : n(n), m(m), data(new int[n * m]())
    {
        std::cout << "constructor of " << n << "x" << m << " matrix" << std::endl;
    }

    Matrix(std::initializer_list<std::initializer_list<int>> initList)
    {
        n = initList.size();
        m = 0;

        for (const auto &row : initList)
        {
            m = std::max(m, row.size());
        }

        data = new int[n * m]();

        size_t row_index = 0;
        for (const auto& row : initList) {
            std::copy_n(row.begin(), std::min(row.size(), m), data + row_index * m);
     
            ++row_index;
        }

        std::cout << "Constructor of " << n << "x" << m << " matrix from initializer_list" << std::endl;
    }

    Matrix(Matrix &&other) noexcept
        : data(std::exchange(other.data, nullptr)),
          n(std::exchange(other.n, 0)),
          m(std::exchange(other.m, 0))
    {
        std::cout << "Move constructor" << std::endl;
    }



    Matrix &operator=(Matrix &&other) noexcept
    {
        if (this != &other)
        {
            delete[] data;
            data = std::exchange(other.data, nullptr);
            n = std::exchange(other.n, 0);
            m = std::exchange(other.m, 0);
        }
        std::cout << "move assignment operator" << std::endl;
        return *this;
    }

     Matrix(const Matrix &other) : n(other.n), m(other.m), data(new int[n * m])
    {
        std::cout << "copy constructor" << std::endl;
        std::copy(other.data, other.data + n * m, data);
    }

    Matrix operator-() const
    {
        Matrix result(n, m);
        for (size_t i = 0; i < n; ++i)
        {
            for (size_t j = 0; j < m; ++j)
            {
                result.data[i * m + j] = -data[i * m + j];
            }
        }
      
        return result;
    }

    int operator()(size_t x, size_t y) const
    {

        if (x > n || y > m)
            throw std::out_of_range("out of range");

        return data[(x-1) * m + (y-1)];
    }

    friend std::ostream &operator<<(std::ostream &os, const Matrix &matrix)
    {
        for (size_t i = 0; i < matrix.n; ++i)
        {
            for (size_t j = 0; j < matrix.m; ++j)
            {
                os << matrix.data[i * matrix.m + j] << " ";
            }
            os << std::endl;
        }
        return os;
    }

   

    Matrix &operator=(const Matrix &other)
    {
        if (this != &other)
        {
            delete[] data;
            n = other.n;
            m = other.m;
            data = new int[n * m];
            std::copy(other.data, other.data + n * m, data);
        }
        std::cout << "copy assignment operator" << std::endl;
        return *this;
    }

    ~Matrix()
    {
        // std::cout<< "deconstrucor"<<std::endl;
        delete[] data;
    }
};

int main()
{

    Matrix m1;
    Matrix m2(3, 4);
    Matrix m3({{1, 2, 3}, {32, 23, 22}, {3, 234, 23, 44}});
    std::cout << m2(1, 1) << std::endl;
    std::cout << m3(2, 2) << std::endl;
    std::cout << m3;

    std ::cout << "copy semantics" << std::endl;
    Matrix m4 = m2;
    
    m4 = m3;

    std::cout << "Move semantics" << std::endl;
    Matrix m7 = std::move(m2);
    m4 = -m3;
    std::cout << "Copy elision" << std::endl;
    Matrix m6 = -m4;

    Matrix *pm = new Matrix(-m4);
    std::cout << m6(2, 1) << std::endl;



    return 0;
}
