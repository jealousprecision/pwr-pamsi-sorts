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
    merge_sort(it, end, std::greater<ValFromIter<Iter>>());
}

template<typename Iter, typename Comp>
void quick_sort(Iter first, Iter end, Comp comp)
{
    if (first == end)
        return;

    auto keyIt = std::next(first, std::distance(first, end) / 2);
    auto key = *keyIt;
    auto predicate = [&](const ValFromIter<Iter>& el) { return comp(key, el); };

    auto preEnd = std::next(end, -1);
    std::swap(*keyIt, *preEnd);
    auto it = algo::partition(first, preEnd, predicate);
    std::rotate(it, preEnd, end);

    quick_sort(first, it, comp);
    quick_sort(std::next(it, 1), end, comp);
}

template<typename Iter>
void quick_sort(Iter first, Iter end)
{
    quick_sort(first, end, std::greater<ValFromIter<Iter>>());
}

template<typename T, typename Comp>
void push_down(T arr[], size_t size, size_t idx, Comp comp)
{
    int largest = idx;
    int l = 2*idx + 1;
    int r = 2*idx + 2;

    if (l < size && comp(arr[l], arr[largest]))
        largest = l;

    if (r < size && comp(arr[r], arr[largest]))
        largest = r;

    if (largest != idx)
    {
        std::swap(arr[idx], arr[largest]);
        push_down(arr, size, largest, comp);
    }
}

template<typename Iter, typename Comp>
void push_down_slow(Iter rootIt, size_t size, size_t idx, Comp comp)
{
    auto largest = rootIt;
    auto largestIdx = idx;
    auto end = std::next(rootIt, size);

    auto lIt = 2 * idx + 1 < size ? std::next(rootIt, idx + 1) : end;
    auto rIt = 2 * idx + 2 < size ? std::next(lIt, 1) : end;

    if (lIt != end && comp(*lIt, *largest))
    {
        largest = lIt;
        largestIdx = 2 * idx + 1;
    }

    if (rIt != end && comp(*rIt, *largest))
    {
        largest = rIt;
        largestIdx = 2 * idx + 2;
    }

    if (largestIdx != idx)
    {
        std::swap(*largest, *rootIt);
        push_down_slow(largest, size, largestIdx, comp);
    }
}

template<typename Iter, typename Comp>
void heap_sort_slow(Iter first, Iter end, Comp comp)
{
    auto size = std::distance(first, end);
    auto lastParent = std::next(first, size / 2 - 1);
    for (long i = size / 2 - 1; i >= 0; --i)
    {
        push_down_slow(lastParent, size, i, comp);
        lastParent--;
    }

    auto dynamicSize = size;
    for (auto newEnd = std::next(end, -1); newEnd != first; newEnd--)
    {
        std::swap(*first, *newEnd);
        dynamicSize -= 1;
        push_down_slow(first, dynamicSize, 0, comp);
    }
}

template<typename T, typename Comp>
void heap_sort(T arr[], size_t size, Comp comp)
{
    for (int i = size/2 - 1; i >= 0; i--)
        push_down(arr, size, i, comp);

    for (int i = size - 1; i >= 0; i--)
    {
        std::swap(arr[0], arr[i]);
        push_down(arr, i, 0, comp);
    }
}

template<typename T>
void heap_sort(T arr[], size_t size)
{
    heap_sort(arr, size, std::greater<T>());
}

template<typename Iter, typename Comp>
void heap_sort(Iter first, Iter end, Comp comp)
{
    std::vector<ValFromIter<Iter>> arr(first, end);

    heap_sort(arr.data(), std::distance(first, end), comp);

    std::copy(arr.begin(), arr.end(), first);
}

template<typename Iter>
void heap_sort(Iter first, Iter end)
{
    heap_sort(first, end, std::greater<ValFromIter<Iter>>());
}
