#include <array>
#include <iostream>

/**
 * Exercise 2a:
 * Implement function power that computes x^n
 * during compilation using recurrent formula
 *   x^2n = (x^n)^2
 *   x^2n+1 = (x^2n)*x
 */
consteval auto power(auto x, int n)
{
  if (n == 0)
    return 1;
  if (n == 1)
    return x;
  if (n % 2 == 0)
    return power(x, n / 2) * power(x, n / 2);
  return power(x, n / 2) * power(x, n / 2) * x;
}

constinit double fiveToPowerFour = power(5, 4);

/**
 *  Exercise 2b:
 * Implement function generate_triangle that during compilation
 * generates the Pascal triangle of the given size N.
 * Pascal triangle
 * https://en.wikipedia.org/wiki/Pascal%27s_triangle
 */

template <size_t N>
class PascalTriangle
{
private:
  std::array<std::array<int, N + 1>, N + 1> triangle{};

public:
  consteval PascalTriangle()
  {
    for (size_t n = 0; n <= N; ++n)
    {
      triangle[n][0] = 1;
      for (size_t m = 1; m <= n; ++m)
      {
        triangle[n][m] = triangle[n - 1][m - 1] + triangle[n - 1][m];
      }
    }
  }

  consteval int operator()(size_t n, size_t m) const
  {
    return triangle[n][m];
  }
};

template <auto N>
consteval PascalTriangle<N> generatePascalTriangle()
{
  return PascalTriangle<N>{};
}

constexpr size_t n = 10;
constexpr auto triangle = generatePascalTriangle<n>();

int main()
{
  static_assert(triangle(0, 0) == 1);
  static_assert(triangle(5, 3) == 10);
  static_assert(triangle(9, 4) == 126);

  std::cout << "5^4 = " << fiveToPowerFour << std::endl;

  return 0;
}
