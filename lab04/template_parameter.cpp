#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <iterator>

bool biggerThan5(int x)
{
    return x > 5;
}

template <template <typename, typename> class OutContainer, typename T, typename Alloc, typename Predicate>
OutContainer<T, Alloc> selectIf(const std::vector<T, Alloc> &c, Predicate p)
{
    OutContainer<T, Alloc> out;
    std::copy_if(c.begin(), c.end(), std::back_inserter(out), p);
    return out;
}

int main()
{
    std::vector<int> v = {1, 2, 13, 4, 5, 54};
    std::list<int> result = selectIf<std::list>(v, biggerThan5);

    for (int elem : result)
    {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
    return 0;
}
