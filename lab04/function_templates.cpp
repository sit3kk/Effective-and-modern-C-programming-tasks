#include <iostream>
#include <string>
#include <typeinfo>
#include <iterator>
#include <vector>
#include <list>
#include <cmath>

template <typename T>
T sqr(T x)
{
    return x * x;
};

template <>
std::string sqr<std::string>(std::string x)
{
    return x + x;
}

template <int N>
int mod(int a, int b)
{
    if constexpr (N == 0)
    {
        return a + b;
    }
    else
    {
        return (a + b) % N;
    }
}

template <typename Container>
void print(const Container &v)
{
    for (auto it = std::begin(v); it != std::end(v); ++it)
    {
        if (it != std::begin(v))
        {
            std::cout << " ";
        }
        std::cout << *it;
    }
    std::cout << std::endl;
}

template <typename T, std::size_t N>
void print(const T (&arr)[N])
{
    for (size_t i = 0; i < N; ++i)
    {
        if (i > 0)
        {
            std::cout << " ";
        }
        std::cout << arr[i];
    }
    std::cout << std::endl;
}

template <typename C, typename F>
C applyFun(const C &c, F f)
{
    C newContainer;
    for (const auto &elem : c)
    {
        newContainer.push_back(f(elem));
    }
    return newContainer;
}

template <typename T, T (*f)(T), std::size_t N>
void process(T (&array)[N])
{
    for (std::size_t i = 0; i < N; ++i)
    {
        array[i] = f(array[i]);
    }
}

template <typename T, std::size_t N>
void print(T (&array)[N])
{
    for (std::size_t i = 0; i < N; ++i)
    {
        std::cout << array[i];
        if (i < N - 1)
            std::cout << " ";
    }
    std::cout << std::endl;
}

int main()
{
    std::cout << sqr(4) << std::endl;                  // 16
    std::cout << sqr(14.5) << std::endl;               // 210.25
    std::cout << sqr(std::string("hey")) << std::endl; // heyhey

    std::cout << mod<5>(130, 1) << std::endl; // 1
    std::cout << mod<7>(1, 130) << std::endl; // 5
    std::cout << mod<0>(13, 14) << std::endl; // 27

    std::vector<int> v = {1, 21, 34, 4, 15};
    print(v); // 1 21 34 4 15

    std::list<double> l = {1, 2.1, 3.2, 6.3};
    print(l); // 1 2.1 3.2 6.3

    double tab[] = {1.2, 3.4, 5.5};
    print(tab);

    auto w = applyFun(v, [](int a)
                      { return a * a; });
    for (const auto &elem : w)
    {
        std::cout << elem << " ";
    }
    std::cout << std::endl;

    auto w3 = applyFun(w, [](int a)
                       { return a % 3; });
    for (const auto &elem : w3)
    {
        std::cout << elem << " ";
    }
    std::cout << std::endl;

    auto l2 = applyFun(l, [](double a)
                       { return a * a; });
    for (const auto &elem : l2)
    {
        std::cout << elem << " ";
    }
    std::cout << std::endl;

    double a[] = {1, 2, 3, 4};
    process<double, sin, 4>(a);
    print(a);

    return 0;
}
