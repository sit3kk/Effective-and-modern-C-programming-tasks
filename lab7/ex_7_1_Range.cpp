#include <iostream>
#include <iterator>
#include "Range.h"

int main()
{
    for (auto x : Range<int>(1, 9, 2))
        std::cout << x << " ";
    std::cout << "\n";

    Range<double> r2(1, 9, 1.5);
    for (auto x : r2)
        std::cout << x << " ";
    std::cout << "\n";

    for (auto x : Range<int>(1, 5))
        std::cout << x << ", ";
    std::cout << "\n";

    for (auto x : Range<int>(7))
        std::cout << x << " ";
    std::cout << "\n";

    auto r3 = make_range(-4.0, 3.5, 1.2);
    for (auto x : r3)
        std::cout << x << " ";
    std::cout << "\n";

    for (auto x : make_range(6))
        std::cout << x << " ";
    std::cout << "\n";

    return 0;
}

/**
 * Expected output :
 * ----------------
1 3 5 7
--------
1 2.5 4 5.5 7 8.5
------------
1, 2, 3, 4,
------------
0 1 2 3 4 5 6
------------
-4 -2.8 -1.6 -0.4 0.8 2 3.2
------------
0 1 2 3 4 5
------------
 */