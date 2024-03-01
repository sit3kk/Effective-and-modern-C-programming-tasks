#include <iostream>
#include <initializer_list>
#include <algorithm>

class Matrix
{
private:
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
        m = initList.begin()->size();

        for (const auto &row : initList)
            m = std::min(m, row.size());

        // std::tie(n, m) = std::make_tuple(std::min(n, m), std::min(n, m));

        data = new int[n * m];

        size_t k = 0;
        for (const auto &row : initList)
        {
            size_t j = 0;
            for (const auto &elem : row)
            {
                if (j >= m)
                    break;
                data[k * m + j] = elem;
                ++j;
            }
            ++k;
        }

        std::cout << "constructor of " << n << "x" << m << " matrix from initializer_list" << std::endl;
    }

   


    int operator()(size_t row, size_t col) const {

        if (row >= n || col >= m)
            throw std::out_of_range("out of range");

        return data[row * m + col];
    }


     friend std::ostream& operator<<(std::ostream& os, const Matrix& matrix) {
        for (size_t i = 0; i < matrix.n; ++i) {
            for (size_t j = 0; j < matrix.m; ++j) {
                os << matrix.data[i * matrix.m + j] << " ";
            }
            os << std::endl;
        }
        return os;
     }

     Matrix(const Matrix &other) : n(other.n), m(other.m), data(new int[n * m]) {
        std::cout<<"copy constructor"<<std::endl;
        std::copy(other.data, other.data + n * m, data);
    }

    Matrix &operator=(const Matrix &other) {
        if (this != &other) {
            delete[] data;
            n = other.n;
            m = other.m;
            data = new int[n * m];
            std::copy(other.data, other.data + n * m, data);
            
        }
        std::cout<< "copy assignment operator"<<std::endl;
        return *this;
    }

    ~Matrix()
    {
        delete[] data;
    }

};

int main()
{
    Matrix m1;
    Matrix m2(3,4);
    Matrix m3({{1,2,3},{32, 23, 22},{3,234,23,44}});
    std::cout << m2(1,1) << std::endl;
    std::cout << m3(2,2) << std::endl;
    std::cout << m3; 

    std :: cout << "copy semantics" << std::endl;
    Matrix m4 = m2;
    m4 = m3;


    return 0;
}
