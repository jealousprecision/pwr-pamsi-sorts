#pragma once

#include <cmath>

#include <algorithm>
#include <iostream>
#include <functional>
#include <iterator>
#include <vector>
#include <utility>

#include <SortsMacros.hpp>
#include <Algo.hpp>
#include <PrintTools.hpp>

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

template<typename Iter, typename Comp>
void quick_sort(Iter first, Iter end, Comp comp)
{
    if (first == end)
        return;

    auto preEnd = std::next(end, -1);
    auto& key = *std::next(first, std::distance(first, end) / 2);
    auto predicate = [&comp, key](const ValFromIter<Iter>& el) { return comp(el, key); };

    std::swap(key, *preEnd);
    auto it = algo::partition(first, preEnd, predicate);
    std::rotate(it, preEnd, end);

    quick_sort(first, it, comp);
    quick_sort(std::next(it), end, comp);
}

template<typename Iter>
void quick_sort(Iter first, Iter end)
{
    quick_sort(first, end, std::less<ValFromIter<Iter>>());
}

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
    for (long i = size / 2 - 1; i >= 0; --i)
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

template<typename Iter, typename Comp>
void insert_sort(Iter first, Iter end, Comp comp)
{
    for (
            auto it = std::next(first, 1);
            it != end;
            ++it
        )
    {
        std::vector<ValFromIter<Iter>> vec(first, end);

        auto key = *it;
        auto prev = std::next(it, -1);

        while (comp(key, *prev))
        {
            std::swap(*prev, *it);
            it = prev;
            if (it == first)
                break;
            prev = std::next(it, -1);
        }
    }
}

using PrintTools::prettyPrint;

template<typename Iter, typename Comp>
void intro_sort(Iter first, Iter end, unsigned maxdepth, Comp comp)
{
    if (std::distance(first, end) <= 1)
        return;

    else if (maxdepth == 0)
        heap_sort(first, end, comp);

    else
    {
        auto preEnd = std::next(end, -1);
        auto& key = *std::next(first, std::distance(first, end) / 2);
        auto predicate = [&comp, key](const ValFromIter<Iter>& el) { return comp(el, key); };

        std::swap(key, *preEnd);
        //std::cout << prettyPrint(first, end) << std::endl;
        auto it = algo::partition(first, preEnd, predicate);
        //std::cout << prettyPrint(first, end) << std::endl;
        std::rotate(it, preEnd, end);
        //std::cout << prettyPrint(first, end) << std::endl;

        //std::vector<ValFromIter<Iter>> test(first, end);

        intro_sort(first, it, maxdepth - 1, comp);
        intro_sort(std::next(it), end, maxdepth - 1, comp);
    }
}

template<typename Iter, typename Comp>
void intro_sort(Iter first, Iter end, Comp comp)
{
    auto maxdepth = log(std::distance(first, end)) * 2;
    intro_sort(first, end, maxdepth, comp);
}
