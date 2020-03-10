#pragma once

#include <string>
#include <stdexcept>
#include <Sorts.hpp>

class SortAbstract
{
public:
    enum class Sorts
    {
        merge,
        quick,
        heap,
        heap_slow
    };

    static std::string toString(Sorts sort)
    {
        switch(sort)
        {
        case Sorts::merge:
            return "MergeSort";
        case Sorts::quick:
            return "QuickSort";
        case Sorts::heap:
            return "HeapSort";
        case Sorts::heap_slow:
            return "HeapSort_slow";
        default:
            return "";
        }
    }

    template<typename Iter, typename Comp>
    static void sortRange(Sorts sortType, Iter first, Iter end, Comp comp)
    {
        switch(sortType)
        {
        case Sorts::merge:
            merge_sort(first, end, comp);
            break;
        case Sorts::quick:
            quick_sort(first, end, comp);
            break;
        case Sorts::heap:
            heap_sort(first, end, comp);
            break;
        case Sorts::heap_slow:
            heap_sort_slow(first, end, comp);
            break;
        default:
            throw std::runtime_error("SortAbstract::sortRange(): sortType not found");
        }
    }

    template<typename Iter>
    static void sortRange(Sorts sortType, Iter first, Iter end)
    {
        sortRange(sortType, first, end, std::greater<ValFromIter<Iter>>());
    }
};
