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

long getChildrenIdx(long idx)
{
    auto parentRow = getRowInHeap(idx);
    auto parentRowOffset = exp2(parentRow) - 1;

    auto childrenRow = parentRow + 1;
    auto childrenRowOffset = exp2(childrenRow) - 1;

    auto parentOffset = idx - parentRowOffset;
    auto childrenOffset = parentOffset * 2;

    auto childrenIdxFirst = childrenRowOffset + childrenOffset;
    return childrenIdxFirst;
}

template<typename T>
class Node
{
public:
    using type = T;

    Node() = default;
    Node(long idx) :
        idx_(idx)
    {}
    Node(long idx, T& obj) :
        idx_(idx), obj_(&obj)
    {}        
    
    T& get() { return *obj_; }
    const T& get() const { return *obj_; }

    operator bool() const { return obj_ != nullptr; }
    //operator T&() { return *obj_; }
    //operator const T&() const { return *obj_; }

    long index() const { return idx_; }

private:
    long idx_ = 0;
    T* obj_ = nullptr;
};

template<typename T>
using Children = std::pair<Node<T>, Node<T>>;

class ChildFactory
{
public:
    template<typename Iter>
    static Children<ValFromIter<Iter>> makeChildren(Iter iter, long size, long parentIdx)
    {
        auto firstIdx = getChildrenIdx(parentIdx);
        
        if (firstIdx + 1 < size)
        {
            std::advance(iter, firstIdx);
            return 
            {
                Node<ValFromIter<Iter>>(firstIdx, *iter),
                Node<ValFromIter<Iter>>(firstIdx + 1, *++iter)
            };
        }
        else if (firstIdx < size)
        {
            std::advance(iter, firstIdx);
            return
            {
                Node<ValFromIter<Iter>>(firstIdx, *iter),
                {}
            };
        }
        else
        {
            return { {}, {} };
        }
    }

    template<typename Iter>
    static Children<ValFromIter<Iter>> makeChildren(Iter first, Iter end, long parentIdx)
    {
        makeChildren(first, std::distance(first, end), parentIdx);
    }
};

/*
template<typename Iter, typename Comp>
void pushDownMaxHeap(
    Iter first,
    long size,
    long idx,
    Comp comp)
{
    auto childBiggerVal = 
        [&](const auto& c1, const auto& c2)
        {
            return comp(c1.get(), c2.get());
        };

    if (idx >= size)
        return;

    auto children = ChildFactory::makeChildren(first, size, idx);
    if (children.first)
    {
        if (children.second)
        {
            Node<ValFromIter<Iter>> parent(idx, *());
            auto max = getMaxEl(
                childBiggerVal,
                parent,
                children.first,
                children.second);

            if (idx != max.index())
            {
                std::swap(el, max.get());
                pushDownMaxHeap(first, size, max.index(), comp);
            }
        }
        else
        {
            // doesn't have second child
            // i.e end of tree
            if (comp(children.first.get(), el))
                std::swap(el, children.first.get());
        }
    }
}
*/
template<typename Iter, typename Comp>
void pushDownMaxHeap(Iter first, long size, long idx, Comp comp)
{
    auto childBiggerVal = 
        [&](const auto& c1, const auto& c2)
        {
            return comp(c1.get(), c2.get());
        };   

    if (idx >= size)
        return;

    auto children = ChildFactory::makeChildren(first, first + size, idx);
    Node<ValFromIter<Iter>> parent(idx, *(first + idx));

    std::vector<decltype(parent)> parentAndChildren{parent};
    if (children.first) parentAndChildren.push_back(children.first);
    if (children.second) parentAndChildren.push_back(children.second);

    auto max = getMaxEl(parentAndChildren.begin(), parentAndChildren.end(), childBiggerVal);
    if (max.index() != parent.index())
    {
        std::swap(max.get(), parent.get());
        pushDownMaxHeap(first, size, max.index(), comp);
    }
}

/*
template<typename Iter, typename Comp>
void makeHeapMax(
    Iter first,
    long size,
    long idx,
    Comp comp)
{
    auto childBiggerVal = 
        [](const auto& c1, const auto& c2)
        {
            return c1.get() > c2.get();
        };

    if (idx >= size)
        return;
    
    auto iter = first;
    std::advance(iter, idx);
    auto& el = *iter;

    auto children = ChildFactory::makeChildren(first, size, idx);
    if (children.first)
    {
        makeHeapMax(first, size, children.first.index(), comp);
        if (children.second)
        {
            makeHeapMax(first, size, children.second.index(), comp);
            Node<ValFromIter<Iter>> parent(idx, el);
            auto& max = getMaxEl(
                childBiggerVal,
                parent, 
                children.first, 
                children.second);
            
            if (max.index() != idx)
            {
                std::swap(el, max.get());
                pushDownMaxHeap(first, size, max.index(), comp);
            }
        }
        else
        {
            Node<ValFromIter<Iter>> parent(idx, el);
            auto& max = getMaxEl(
                childBiggerVal,
                parent,
                children.first);
            
            if (max.index() != idx)
            {
                std::swap(el, max.get());
                pushDownMaxHeap(first, size, max.index(), comp);
            }
        }
    }
}
*/

template<typename Iter, typename Comp>
void makeHeapMax(Iter first, long size, long idx, Comp comp)
{
    auto childBiggerVal = 
        [&](const auto& c1, const auto& c2)
        {
            return comp(c1.get(), c2.get());
        };

    if (idx >= size)
        return;
    
    auto children = ChildFactory::makeChildren(first, first+size, idx);
    
    if (children.first)
        makeHeapMax(first, size, children.first.index(), comp);
    if (children.second)
        makeHeapMax(first, size, children.second.index(), comp);  
    
    children = ChildFactory::makeChildren(first, first+size, idx);
    Node<ValFromIter<Iter>> parent(idx, *(first + size));
    
    std::vector<decltype(parent)> parentAndChildren{parent};
    if (children.first) parentAndChildren.push_back(children.first);
    if (children.second) parentAndChildren.push_back(children.second);

    auto max = getMaxEl(parentAndChildren.begin(), parentAndChildren.end(), childBiggerVal);
    if (max.index() != parent.index())
    {
        std::swap(max.get(), parent.get());
        pushDownMaxHeap(first, size, max.index(), comp);
    }
}

template<typename Iter, typename Comp>
void heap_sort_internal(
    Iter first,
    Iter end,
    Comp comp)
{
    if(first == end)
        return;

    pushDownMaxHeap(first, std::distance(first, end), 0, comp);
    std::swap(*first, *--end);
    heap_sort_internal(first, end, comp);
}

template<typename Iter, typename Comp>
void heap_sort(
    Iter first, 
    Iter end, 
    Comp comp)
{
    if (first == end)
        return;

    auto size = std::distance(first, end);
    makeHeapMax(first, size, 0, comp);
    std::swap(*first, *--end);
    heap_sort_internal(first, end, comp);
}

template<typename Iter>
void heap_sort(
    Iter first, 
    Iter end)
{
    heap_sort(first, end, std::greater<ValFromIter<Iter>>());
}    

/*
template<typename Iter, typename Comp>
void makeHeapMax(Iter first, Iter end, long idx, Comp comp)
{
    if (std::distance(first, end) <= idx)
        return;

    auto& el =  *(first + idx);
    auto children = getChildren(first, end, idx);

    if (children.first)
    {
        makeHeapMax(first, end, children.first.idx, comp);
        if(children.second)
        {
            makeHeapMax(first, end, children.second.idx, comp);
            auto max = getMaxEl(el, children.first.get(), children.second.get());
            std::swap(el, max.get());
        }
        else
        {
            auto max = getMaxEl(el, children.first.get());
            std::swap(el, max.get());
        }
    }
}

template<typename Iter>
void makeHeapMax(Iter first, Iter end)
{
    makeHeapMax(first, end, 0, std::greater<GET_VAL_T_FROM_ITER_T(Iter)>());
}

/**
 * !!! Function assumes that elemetn we want to push down
 * is in the root of container
 *
template<typename Iter, typename Comp>
void pushDownHeap(Iter first, Iter end, long idx, Comp comp)
{
    auto& el = *first;
    auto possibleChildren = getChildren(first, end, idx);

    auto maxChild = getMaxEl(possibleChildren.first, possibleChildren.second);
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

*/
