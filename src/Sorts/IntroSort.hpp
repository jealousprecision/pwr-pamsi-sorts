#pragma once

#include <cmath>
#include <functional>
#include <iterator>

#include <Algo.hpp>
#include <Sorts/HeapSort.hpp>

#include "SortsMacros.hpp"

template<typename Iter, typename Comp>
void intro_sort(Iter first, Iter end, unsigned maxdepth, Comp comp)
{
    if (std::distance(first, end) <= 1)
    {
        return;
    }
    else if (maxdepth == 0)
    {
        heap_sort(first, end, comp);
    }
    else
    {
        auto keyIt = std::next(first, std::distance(first, end) / 2);

        auto it = algo::partition_with_pivot(first, keyIt, end, comp);

        intro_sort(first, it, maxdepth - 1, comp);
        intro_sort(std::next(it), end, maxdepth - 1, comp);
    }
}

template<typename Iter, typename Comp>
void intro_sort(Iter first, Iter end, Comp comp)
{
    auto maxdepth = std::log(std::distance(first, end)) * 2;
    intro_sort(first, end, maxdepth, comp);
}

template<typename Iter>
void intro_sort(Iter first, Iter end)
{
    intro_sort(first, end, std::less<ValFromIter<Iter>>());
}
