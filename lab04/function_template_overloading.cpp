#include <cstring>
#include <iostream>

template <typename T>
int compare(T a, T b)
{
    if (a < b)
        return 1;
    else if (b < a)
        return -1;
    else
        return 0;
}

template <typename T>
int compare(T *a, T *b)
{
    return compare(*a, *b);
}

template <>
int compare<const char *>(const char *a, const char *b)
{
    int result = std::strcmp(a, b);
    if (result < 0)
        return 1;
    else if (result > 0)
        return -1;
    else
        return 0;
}

int main()
{
    int a = 1, b = -6;
    float x = 1.0, y = 1.0 + 1e20 - 1e20;

    std::cout << compare(a, b) << " " << compare(b, a) << " " << compare(a, a) << std::endl;
    std::cout << compare(x, y) << " " << compare(y, x) << " " << compare(x, x) << std::endl;
    std::cout << compare(&a, &b) << " " << compare(&b, &a) << " " << compare(&a, &a) << std::endl;
    std::cout << compare(&x, &y) << " " << compare(&y, &x) << " " << compare(&x, &x) << std::endl;
    std::cout << compare("Alpha", "Alfa") << std::endl;

    return 0;
}
