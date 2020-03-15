#pragma once

#include <iterator>
#include <Algo.hpp>

#include "SortsMacros.hpp"

template<typename Iter, typename Comp>
void merge_sort(Iter first, Iter end, Comp comp)
{
    auto size = std::distance(first, end);
    if (size <= 1)
        return;

    auto halfRangeEnd = std::next(first, size / 2);

    merge_sort(first, halfRangeEnd, comp);
    merge_sort(halfRangeEnd, end, comp);

    algo::merge(first, halfRangeEnd, end, comp);
}

template<typename Iter>
void merge_sort(Iter it, Iter end)
{
    merge_sort(it, end, std::less<ValFromIter<Iter>>());
}
