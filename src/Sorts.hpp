#pragma once

#include <cmath>

#include <algorithm>
#include <iostream>
#include <functional>
#include <iterator>
#include <vector>
#include <type_traits>
#include <utility>

#include <SortsMacros.hpp>
#include <SortsHelpers.hpp>

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

        if (comp(*it, *halfRangeIt))
            *inserterIt++ = *halfRangeIt++;
        else
            *inserterIt++ = *it++;
    }

    std::copy(temp.begin(), temp.end(), first);
}

template<typename Iter, typename Comp>
void merge_sort(Iter first, Iter end, Comp comp)
{
    auto size = std::distance(first, end);
    if (size <= 1)
        return;

    auto halfRangeEnd = first;
    std::advance(halfRangeEnd, size / 2);

    merge_sort(first, halfRangeEnd, comp);
    merge_sort(halfRangeEnd, end, comp);

    merge(first, halfRangeEnd, end, comp);
}

template<typename Iter>
void merge_sort(Iter it, Iter end)
{
    merge_sort(it, end, std::greater<ValFromIter<Iter>>());
}

template<typename Iter, typename Comp>
void quick_sort(Iter first, Iter end, Comp comp)
{
    auto size = std::distance(first, end);
    if (size <= 1)
        return;

    std::vector<ValFromIter<Iter>> temp;
    temp.resize(size);

    auto tempIt = first;
    std::advance(tempIt, size / 2);
    auto key = *tempIt;

    auto firstIt = temp.begin();
    auto endIt = temp.end();
    auto insertEl = [&](const ValFromIter<Iter>& el)
        {
            if (comp(key, el))
                *firstIt++ = el;
            else
                *--endIt = el;
        };

    std::for_each(first, tempIt, insertEl);
    std::for_each(++tempIt, end, insertEl);

    *firstIt = key;

    quick_sort(temp.begin(), firstIt, comp);
    quick_sort(endIt, temp.end(), comp);

    std::copy(temp.begin(), temp.end(), first);
}

template<typename Iter>
void quick_sort(Iter first, Iter end)
{
    quick_sort(first, end, std::greater<ValFromIter<Iter>>());
}

void push_down(int arr[], int size, int idx)
{
    int largest = idx;
    int l = 2*idx + 1;
    int r = 2*idx + 2;

    if (l < size && arr[l] > arr[largest])
        largest = l;
    
    if (r < size && arr[r] > arr[largest])
        largest = r;
    
    if (largest != idx)
    {
        std::swap(arr[idx], arr[largest]);
        push_down(arr, size, largest);
    }
}

void heap_sort(int arr[], int size)
{
    for (int i = size/2 - 1; i >= 0; i--)
        push_down(arr, size, i);

    for (int i = size - 1; i >= 0; i--)
    {
        std::swap(arr[0], arr[i]);
        push_down(arr, i, 0);
    }
}   
