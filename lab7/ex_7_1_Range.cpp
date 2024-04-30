#include <iostream>
#include <iterator>

template <typename T>
class Range
{
public:
    class Iterator
    {
    public:
        Iterator(T start, T step) : current(start), step(step) {}

        T operator*() const { return current; }
        Iterator &operator++()
        {
            current += step;
            return *this;
        }
        bool operator!=(const Iterator &other) const { return current < other.current; }

    private:
        T current;
        T step;
    };

    Range(T stop) : Range(T(0), stop, T(1)) {}
    Range(T start, T stop, T step = T(1)) : start(start), stop(stop), step(step) {}

    Iterator begin() const { return Iterator(start, step); }
    Iterator end() const { return Iterator(stop, step); }

private:
    T start;
    T stop;
    T step;
};

template <typename T>
Range<T> make_range(T start, T stop, T step = T(1))
{
    return Range<T>(start, stop, step);
}

template <typename T>
Range<T> make_range(T stop)
{
    return Range<T>(T(0), stop, T(1));
}

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