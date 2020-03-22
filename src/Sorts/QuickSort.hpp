#pragma once

#include <functional>
#include <iterator>
#include <Algo.hpp>

#include "SortsMacros.hpp"

template<typename Iter, typename Comp>
void quick_sort(Iter first, Iter end, Comp comp)
{
    if (first == end)
        return;

    auto keyIt = std::next(first, std::distance(first, end) / 2);
    auto it = algo::partition_with_pivot(first, keyIt, end, comp);

    quick_sort(first, it, comp);
    quick_sort(std::next(it), end, comp);
}

template<typename Iter>
void quick_sort(Iter first, Iter end)
{
    quick_sort(first, end, std::less<ValFromIter<Iter>>());
}
