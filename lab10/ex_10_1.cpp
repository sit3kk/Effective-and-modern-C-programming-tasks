#include <iostream>
#include <type_traits>
#include <vector>

template <typename T>
class hasSize
{
private:
    template <typename U>
    static auto check(U *) -> decltype(std::declval<U>().size(), std::true_type());

    template <typename>
    static std::false_type check(...);

public:
    static constexpr bool value = decltype(check<T>(nullptr))::value;
};

template <typename T>
class hasValueType
{
private:
    template <typename U>
    static auto check(U *) -> decltype(typename U::value_type(), std::true_type());

    template <typename>
    static std::false_type check(...);

public:
    static constexpr bool value = decltype(check<T>(nullptr))::value;
};

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

int main()
{
    std::vector<int> v{1, 2, 3, 4, 5};
    std::cout << v1::getSize(5) << std::endl; // 4
    std::cout << v1::getSize(v) << std::endl; // 20
    std::cout << v2::getSize(5) << std::endl; // 4
    std::cout << v2::getSize(v) << std::endl; // 20
}
