#include <iostream>
#include <vector>
#include <concepts>
#include <numeric>
#include <type_traits>

template<typename T>
concept HasPrintMethod = requires(T t) {
    { t.print() } -> std::same_as<void>;
};

template<typename T>
concept HasOStreamOperator = requires(std::ostream &out, T t) {
    { out << t } -> std::same_as<std::ostream&>;
};

template<typename T>
concept Printable = HasPrintMethod<T> || HasOStreamOperator<T>;

template<typename T>
concept Container = requires(T t) {
    typename T::value_type;
    { t.begin() } -> std::input_iterator;
    { t.end() } -> std::input_iterator;
    requires std::convertible_to<decltype(*t.begin()), typename T::value_type>;
};

template<Printable T>
void print(const T& obj) {
    if constexpr (HasOStreamOperator<T>) {
        std::cout << obj << std::endl;
    } else if constexpr (HasPrintMethod<T>) {
        obj.print();
        std::cout << std::endl;
    }
}

template<Container C>
void print(const C& container) {
    int index = 0;
    for (const auto& elem : container) {
        std::cout << index++ << " : ";
        print(elem);
    }
    std::cout << "-------" << std::endl;
}

template<typename T>
concept Addable = requires(T a, T b) {
    { a + b } -> std::same_as<T>;
};

template<Container C>
requires Addable<typename C::value_type>
auto sum(const C& container) {
    return std::accumulate(container.begin(), container.end(), typename C::value_type{});
}

template<Addable T>
T sum(const std::vector<T>& v) {
    return std::accumulate(v.begin(), v.end(), T{});
}

template<Addable T>
T sum(const T& value) {
    return value;
}

// Classes A and B
template <typename T>
class A {
protected:
    T x;
public:
    A(T x = T()) : x(x) {}
    void print() const {
        std::cout << "[" << x << "]";
    }
    friend A operator+(const A& a, const A& b) {
        return A(a.x + b.x);
    }
};

template <typename T>
class B : public A<T> {
public:
    using A<T>::A;
    B(const A<T>& a) : A<T>(a) {}
    friend std::ostream& operator<<(std::ostream& out, const B& b) {
        return (out << "#" << b.x << "#");
    }
    friend B operator+(const B& a, const B& b) {
        return B(a.x + b.x);
    }
};

// Main function
int main() {
    std::vector<int> v{1, 2, 4, 5};
    print(v);
    A<int> a{5};
    print(a);
    B<double> b{3.14};
    print(b);
    print(2.7);
    std::vector<A<int>> va{4, 5, 7, 9};
    std::vector<B<int>> vb{4, 5, 7, 9};
    print(va);
    print(vb);
    print(sum(v));
    print(sum(vb));
    return 0;
}

/**
* Expected output
0 : 1
1 : 2
2 : 4
3 : 5
-------
[5]
#3.14#
2.7
0 : [4]
1 : [5]
2 : [7]
3 : [9]
-------
0 : #4#
1 : #5#
2 : #7#
3 : #9#
-------
12
#25#
*/
