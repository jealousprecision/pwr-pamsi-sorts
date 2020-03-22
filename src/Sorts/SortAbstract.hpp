#pragma once

#include <functional>
#include <string>
#include <stdexcept>
#include <Sorts/Sorts.hpp>

class SortAbstract
{
public:
    enum class Sorts
    {
        merge,
        quick,
        heap,
        insert,
        intro
    };

    static std::string toString(Sorts sort)
    {
        switch (sort)
        {
        case Sorts::merge:
            return "MergeSort";
        case Sorts::quick:
            return "QuickSort";
        case Sorts::heap:
            return "HeapSort";
        case Sorts::insert:
            return "InsertionSort";
        case Sorts::intro:
            return "IntrospectionSort";
        default:
            return "";
        }
    }

    template<typename Iter, typename Comp>
    static void sortRange(Sorts sortType, Iter first, Iter end, Comp comp)
    {
        switch (sortType)
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
        case Sorts::insert:
            insert_sort(first, end, comp);
            break;
        case Sorts::intro:
            intro_sort(first, end, comp);
            break;
        default:
            throw std::runtime_error("SortAbstract::sortRange(): sortType not found");
        }
    }

    template<typename Iter>
    static void sortRange(Sorts sortType, Iter first, Iter end)
    {
        sortRange(sortType, first, end, std::less<ValFromIter<Iter>>());
    }
};
