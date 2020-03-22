#pragma once

#include <algorithm>
#include <iterator>
#include <utility>

#include "SortsMacros.hpp"

template<typename Iter, typename Comp>
void push_down(Iter rootIt, size_t size, size_t idx, Comp comp)
{
    auto largest = rootIt;
    auto largestIdx = idx;
    auto end = std::next(rootIt, size);

    auto lIt = 2 * idx + 1 < size ? std::next(rootIt, idx + 1) : end;
    auto rIt = 2 * idx + 2 < size ? std::next(lIt, 1) : end;

    if (lIt != end && comp(*largest, *lIt))
    {
        largest = lIt;
        largestIdx = 2 * idx + 1;
    }

    if (rIt != end && comp(*largest, *rIt))
    {
        largest = rIt;
        largestIdx = 2 * idx + 2;
    }

    if (largestIdx != idx)
    {
        std::swap(*largest, *rootIt);
        push_down(largest, size, largestIdx, comp);
    }
}

template<typename Iter, typename Comp>
void heap_sort(Iter first, Iter end, Comp comp)
{
    auto size = std::distance(first, end);
    auto lastParent = std::next(first, size / 2 - 1);
    for (size_t i = size / 2 - 1; i >= 0; --i)
    {
        push_down(lastParent, size, i, comp);
        lastParent--;
    }

    auto dynamicSize = size;
    for (auto newEnd = std::next(end, -1); newEnd != first; newEnd--)
    {
        std::swap(*first, *newEnd);
        dynamicSize -= 1;
        push_down(first, dynamicSize, 0, comp);
    }
}
