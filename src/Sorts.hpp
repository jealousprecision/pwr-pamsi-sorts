#pragma once

#include <algorithm>
#include <iostream>
#include <functional>
#include <iterator>
#include <vector>
#include <type_traits>
#include <utility>

// get value type from templated Iterator typename without initializing any variables
#define GET_VAL_T_FROM_ITER_T(Iter_t) typename std::remove_reference<decltype(*std::declval<Iter_t>())>::type

template<typename Iter, typename Comp, typename size_t>
void merge(Iter first, Iter halfRangeEnd, Iter end, size_t size, Comp comp)
{
    std::vector<GET_VAL_T_FROM_ITER_T(Iter)> temp; 
    temp.reserve(size);  // optimization

    auto halfRangeIt = halfRangeEnd;
    auto it = first;
    while (true)
    {
        if (it == halfRangeEnd)
        {
            std::copy(halfRangeIt, end, std::back_inserter(temp));
            break;
        }
        if (halfRangeIt == end)
        {
            std::copy(it, halfRangeEnd, std::back_inserter(temp));
            break;
        }

        if (comp(*it, *halfRangeIt))
            temp.push_back(*halfRangeIt++);
        else
            temp.push_back(*it++);
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

    merge(first, halfRangeEnd, end, size, comp);
}

template<typename Iter>
void merge_sort(Iter it, Iter end)
{
    merge_sort(it, end, std::greater<GET_VAL_T_FROM_ITER_T(Iter)>());
}

template<typename Iter, typename Comp>
void quick_sort(Iter first, Iter end, Comp comp)
{
    auto size = std::distance(first, end);
    if (size <= 1)
        return;
    
    auto key = *first;

    GET_VAL_T_FROM_ITER_T(Iter) temp[size];

    auto firstIt = temp;
    auto endIt = temp + size;
    std::for_each(first + 1, end, 
        [&](const auto& el)
        {
            if (comp(key, el))
            {
                *firstIt = el;
                firstIt++;
            }
            else
            {
                endIt--;
                *endIt = el;
            }
        });
    
    *firstIt = key;

    std::cout << "temp: ";
    for (int i=0; i<size; ++i)
        std::cout << temp[i] << ", ";
    std::cout << std::endl;

    quick_sort(temp, firstIt, comp);
    quick_sort(endIt, temp + size, comp);

    std::copy(temp, temp + size, first);
}

template<typename Iter>
void quick_sort(Iter first, Iter end)
{
    quick_sort(first, end, std::greater<GET_VAL_T_FROM_ITER_T(Iter)>());
}
