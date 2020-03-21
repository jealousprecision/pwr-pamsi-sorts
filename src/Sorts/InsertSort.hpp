#pragma once

#include <vector>
#include <iterator>

#include "SortsMacros.hpp"

template<typename Iter, typename Comp>
void insert_sort(Iter first, Iter end, Comp comp)
{
    for (auto it = std::next(first, 1); it != end; ++it)
    {
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
