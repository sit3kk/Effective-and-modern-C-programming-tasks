#include <iostream>
#include <chrono>
#include <string>
#include <type_traits>
#include <vector>

class Timer
{
    std::string name;
    std::chrono::time_point<std::chrono::high_resolution_clock> start;

public:
    Timer(const std::string &name) : name(name), start(std::chrono::high_resolution_clock::now()) {}
    ~Timer()
    {
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> duration = end - start;
        std::cout << name << " : " << duration.count() << " ms. " << std::endl;
    }
    auto durationInNanoseconds()
    {
        auto end = std::chrono::high_resolution_clock::now();
        return std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    }
};

// SFINAE detection
template <typename T, typename = std::void_t<>>
struct hasSize : std::false_type
{
};

template <typename T>
struct hasSize<T, std::void_t<decltype(std::declval<T>().size())>> : std::true_type
{
};

template <typename T, typename = std::void_t<>>
struct hasValueType : std::false_type
{
};

template <typename T>
struct hasValueType<T, std::void_t<typename T::value_type>> : std::true_type
{
};

// v1 namespace with enable_if
namespace v1
{
    template <typename T>
    typename std::enable_if<hasSize<T>::value && hasValueType<T>::value, size_t>::type
    getSize(const T &x)
    {
        return x.size() * sizeof(typename T::value_type);
    }

    template <typename T>
    typename std::enable_if<!hasSize<T>::value || !hasValueType<T>::value, size_t>::type
    getSize(const T &x)
    {
        return sizeof(x);
    }
}

// v2 namespace with if constexpr
namespace v2
{
    template <typename T>
    size_t getSize(const T &x)
    {
        if constexpr (hasSize<T>::value && hasValueType<T>::value)
        {
            return x.size() * sizeof(typename T::value_type);
        }
        else
        {
            return sizeof(x);
        }
    }
}

long fibonacci(unsigned n)
{
    if (n < 2)
        return n;
    return fibonacci(n - 1) + fibonacci(n - 2);
}

int main()
{
    Timer total("Total time");
    for (auto n : {1, 5, 15, 20, 25, 40, 45})
    {
        {
            Timer t("fibonacci(" + std::to_string(n) + ")"); // RAII
            fibonacci(n);
        }
    }
    std::cout << "Elapsed " << total.durationInNanoseconds() << " ns.\n";
}
/** Expected output similar to:

fibonacci(1) : 0.000619 ms.
fibonacci(5) : 0.000891 ms.
fibonacci(15) : 0.01025 ms.
fibonacci(20) : 0.094905 ms.
fibonacci(25) : 1.04443 ms.
fibonacci(40) : 989.97 ms.
fibonacci(45) : 8537.47 ms.
Elapsed 9528821533 ns.
Total time : 9528.84 ms.
*/