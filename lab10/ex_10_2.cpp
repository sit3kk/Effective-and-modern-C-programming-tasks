#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <iterator>
#include <type_traits>

template <typename RandomAccessIterator>
double median_impl(RandomAccessIterator first, RandomAccessIterator last, std::random_access_iterator_tag)
{
    if (first == last)
    {
        throw std::invalid_argument("Container is empty");
    }
    auto size = std::distance(first, last);
    std::vector<typename std::iterator_traits<RandomAccessIterator>::value_type> temp(first, last);
    std::sort(temp.begin(), temp.end());
    if (size % 2 == 0)
    {
        return (temp[size / 2 - 1] + temp[size / 2]) / 2.0;
    }
    else
    {
        return temp[size / 2];
    }
}

template <typename ForwardIterator>
double median_impl(ForwardIterator first, ForwardIterator last, std::forward_iterator_tag)
{
    if (first == last)
    {
        throw std::invalid_argument("Container is empty");
    }
    std::vector<typename std::iterator_traits<ForwardIterator>::value_type> temp(first, last);
    std::sort(temp.begin(), temp.end());
    auto size = std::distance(first, last);
    if (size % 2 == 0)
    {
        return (temp[size / 2 - 1] + temp[size / 2]) / 2.0;
    }
    else
    {
        return temp[size / 2];
    }
}

template <typename Container>
double median(const Container &container)
{
    using Iterator = typename Container::const_iterator;
    using IteratorCategory = typename std::iterator_traits<Iterator>::iterator_category;
    return median_impl(container.begin(), container.end(), IteratorCategory());
}

int main()
{
    std::list<int> a{3, 2, 5, 1, 4};
    std::cout << median(a) << std::endl; // 3
    std::vector<int> v{3, 1, 4, 2};
    std::cout << median(v) << std::endl; // 2.5

    return 0;
}
