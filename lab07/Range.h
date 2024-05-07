

#ifndef LAB6_RANGE_H
#define LAB6_RANGE_H

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

#endif // LAB6_RANGE_H
