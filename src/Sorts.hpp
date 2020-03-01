#pragma once

#include <cmath>

#include <algorithm>
#include <iostream>
#include <functional>
#include <iterator>
#include <vector>
#include <type_traits>
#include <utility>

// get value type from templated Iterator typename without initializing any variables
#define GET_VAL_T_FROM_ITER_T(Iter_t) typename std::remove_reference<decltype(*std::declval<Iter_t>())>::type

template<typename Iter, typename Comp>
void merge(Iter first, Iter halfRangeEnd, Iter end, Comp comp)
{
    std::vector<GET_VAL_T_FROM_ITER_T(Iter)> temp; 
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
    merge_sort(it, end, std::greater<GET_VAL_T_FROM_ITER_T(Iter)>());
}

template<typename Iter, typename Comp>
void quick_sort(Iter first, Iter end, Comp comp)
{
    auto size = std::distance(first, end);
    if (size <= 1)
        return;

    std::vector<GET_VAL_T_FROM_ITER_T(Iter)> temp;
    temp.resize(size);

    
    auto tempIt = first;
    std::advance(tempIt, size / 2);
    auto key = *tempIt;
    
    auto firstIt = temp.begin();
    auto endIt = temp.end();
    auto insertEl = [&](const GET_VAL_T_FROM_ITER_T(Iter)& el)
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
    quick_sort(first, end, std::greater<GET_VAL_T_FROM_ITER_T(Iter)>());
}

long getRowInHeap(long idx)
{
    return log2(idx + 1);
}

std::pair<long, long> getChildrenIdx(long idx)
{
    auto parentRow = getRowInHeap(idx);
    auto parentRowOffset = exp2(parentRow) - 1;

    auto childrenRow = parentRow + 1;
    auto childrenRowOffset = exp2(childrenRow) - 1;

    auto parentOffset = idx - parentRowOffset;
    auto childrenOffset = parentOffset * 2;

    auto childrenIdxFirst = childrenRowOffset + childrenOffset;
    return {childrenIdxFirst, childrenIdxFirst + 1};
}

std::ostream& operator<<(std::ostream& os, const std::pair<long, long>& obj)
{
    return os << obj.first << ", " << obj.second;
}

template<typename T>
struct PtrIndexPair
{
    operator T&() {return *ptr;}
    operator const T&() const {return *ptr;}

    T& get() {return *ptr;}
    const T& get() const {return *ptr;}

    operator bool() {return ptr != nullptr;}

    T* ptr;
    long idx;
};

template<typename T>
using Children = std::pair<PtrIndexPair<T>, PtrIndexPair<T>>;

template<typename Iter>
Children<GET_VAL_T_FROM_ITER_T(Iter)> getChildren(Iter first, Iter end, long idx)
{    
    Children<GET_VAL_T_FROM_ITER_T(Iter)> ret;

    auto chIdx = getChildrenIdx(idx);
    auto possibleChildren = std::make_pair(first + chIdx.first, first + chIdx.second);
    
    if (possibleChildren.first < end)
    {
        ret.first.ptr = &*possibleChildren.first;
        ret.first.idx = chIdx.first;
    }
    else
        ret.first.ptr = nullptr;
    
    if (possibleChildren.second < end)
    {
        ret.second.ptr = &*possibleChildren.second;
        ret.second.idx = chIdx.second;
    }
    else
        ret.second.ptr = nullptr;
    
    return ret;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const Children<T>& children)
{
    if (children.first.ptr != nullptr)
        os << children.first;
    if (children.second.ptr != nullptr)
        os << ", " << children.second;
    
    return os;
}

template<typename Iter, typename Comp>
void makeHeapMax(Iter first, Iter end, long idx, Comp comp)
{
    if (std::distance(first, end) <= idx)
        return;

    auto& el =  *(first + idx);
    auto children = getChildren(first, end, idx);

    if (children.first.ptr != nullptr)
    {
        makeHeapMax(first, end, children.first.idx, comp);
        if (comp(children.first, el))
        {
            std::swap(*children.first.ptr, el);
            makeHeapMax(first, end, children.first.idx, comp);
        }
    }
    if (children.second.ptr != nullptr)
    {
        makeHeapMax(first, end, children.second.idx, comp);
        if (comp(children.second, el))
        {
            std::swap(*children.second.ptr, el);
            makeHeapMax(first, end, children.second.idx, comp);
        }
    }   
}

template<typename Iter>
void makeHeapMax(Iter first, Iter end)
{
    makeHeapMax(first, end, 0, std::greater<GET_VAL_T_FROM_ITER_T(Iter)>());
}

template<typename Iter, typename Comp>
void heap_sort(Iter first, Iter end, Comp comp)
{
    if (first == end)
        return;

    makeHeapMax(first, end, 0, comp);
    std::swap(*first, *(end - 1));
    heap_sort(first, end - 1, comp);
}

template<typename Iter>
void heap_sort(Iter first, Iter end)
{
    heap_sort(first, end, std::greater<GET_VAL_T_FROM_ITER_T(Iter)>());
}


#undef GET_VAL_T_FROM_ITER_T
