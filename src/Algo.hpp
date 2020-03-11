#pragma once

#include <SortsMacros.hpp>

namespace algo
{

template<typename Iter, typename Predicate>
Iter partition(Iter first, Iter end, Predicate pred)
{
    auto endIt = end;
    auto it = first;

    while (it != endIt)
    {
        if (pred(*it))
            ++it;
        else
            std::swap(*it, *--endIt);
    }

    return it;
}

template<typename Iter, typename Comp>
void merge(Iter first, Iter halfRangeEnd, Iter end, Comp comp)
{
    std::vector<ValFromIter<Iter>> temp;
    temp.resize(std::distance(first, end));

    auto halfRangeIt = halfRangeEnd;
    auto it = first;
    auto inserterIt = temp.begin();
    while (true)
    {
        if (it == halfRangeEnd)
        {
            std::copy(halfRangeIt, end, inserterIt);
            break;
        }
        if (halfRangeIt == end)
        {
            std::copy(it, halfRangeEnd, inserterIt);
            break;
        }

        if (comp(*halfRangeIt, *it))
            *inserterIt++ = *halfRangeIt++;
        else
            *inserterIt++ = *it++;
    }

    std::copy(temp.begin(), temp.end(), first);
}

}  // namespace algo
