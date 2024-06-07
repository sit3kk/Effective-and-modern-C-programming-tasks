#include <array>
#include <cstddef>
#include <iostream>

template <typename T>
constexpr T power(T x, int n)
{
    if (n == 0)
        return 1;
    if (n == 1)
        return x;
    if (n % 2 == 0)
    {
        T half_power = power(x, n / 2);
        return half_power * half_power;
    }
    else
    {
        T half_power = power(x, (n - 1) / 2);
        return half_power * half_power * x;
    }
}

constexpr double fiveToPowerFour = power(5.0, 4);

template <std::size_t N>
constexpr auto generatePascalTriangle()
{
    std::array<std::array<size_t, N>, N> triangle{};

    for (std::size_t i = 0; i < N; ++i)
    {
        triangle[i][0] = 1;
        triangle[i][i] = 1;
        for (std::size_t j = 1; j < i; ++j)
        {
            triangle[i][j] = triangle[i - 1][j - 1] + triangle[i - 1][j];
        }
    }

    return triangle;
}

constexpr size_t n = 10;
constexpr auto triangle = generatePascalTriangle<n>();

static_assert(triangle[0][0] == 1);
static_assert(triangle[5][3] == 10);
static_assert(triangle[9][4] == 126);

int main()
{

    for (std::size_t i = 0; i < n; ++i)
    {
        for (std::size_t j = 0; j <= i; ++j)
        {
            std::cout << triangle[i][j] << " ";
        }
        std::cout << std::endl;
    }
    return 0;
}
