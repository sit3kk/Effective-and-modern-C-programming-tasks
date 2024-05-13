#ifndef LAB6_FILTER_H
#define LAB6_FILTER_H

#include <iterator>
#include <utility>
#include <type_traits>

template <typename Container, typename Predicate>
class Filter;

template <typename Container, typename Predicate>
auto make_filter(Container &&c, Predicate p)
{
    return Filter<Container, Predicate>(std::forward<Container>(c), std::move(p));
}

template <typename Container, typename Predicate>
class Filter
{
public:
    using value_type = typename std::remove_reference<Container>::type::value_type;
    using iterator_type = typename std::remove_reference<Container>::type::iterator;

    Filter(Container &&c, Predicate p)
        : container_(std::forward<Container>(c)), pred_(std::move(p)) {}

    class iterator
    {
        iterator_type current_, end_;
        Predicate pred_;

    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = typename iterator_type::value_type;
        using difference_type = typename iterator_type::difference_type;
        using pointer = typename iterator_type::pointer;
        using reference = typename iterator_type::reference;

        iterator(iterator_type current, iterator_type end, Predicate pred)
            : current_(current), end_(end), pred_(pred)
        {
            advance_to_next_valid();
        }

        bool operator==(const iterator &other) const { return current_ == other.current_; }
        bool operator!=(const iterator &other) const { return current_ != other.current_; }
        reference operator*() const { return *current_; }

        iterator &operator++()
        {
            ++current_;
            advance_to_next_valid();
            return *this;
        }

        iterator operator++(int)
        {
            iterator tmp = *this;
            ++(*this);
            return tmp;
        }

    private:
        void advance_to_next_valid()
        {
            while (current_ != end_ && !pred_(*current_))
            {
                ++current_;
            }
        }
    };

    iterator begin() { return iterator(std::begin(container_), std::end(container_), pred_); }
    iterator end() { return iterator(std::end(container_), std::end(container_), pred_); }

private:
    Container container_;
    Predicate pred_;
};

#endif // LAB6_FILTER_H
