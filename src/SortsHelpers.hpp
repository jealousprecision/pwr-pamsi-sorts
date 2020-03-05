#pragma once

#include <functional>

#include <SortsMacros.hpp>

template<typename T, typename Comp>
T& getMaxEl(Comp comp, T& t1, T& t2)
{
    return comp(t1, t2) ? t1 : t2;
}

template<typename T, typename Comp, typename... Args>
T& getMaxEl(Comp comp, T& t1, T& t2, Args... args)
{
    if (comp(t1, t2))
        return getMaxEl(comp, t1, args...);
    else
        return getMaxEl(comp, t2, args...);
}

template<typename T, typename... Args>
T& getMaxEl(T& t1, T& t2, Args... args)
{
    return getMaxEl(std::greater<T>(), t1, t2, args...);
}

template<typename Iter, typename Comp>
ValFromIter<Iter>& getMaxEl(Iter first, Iter end, Comp comp)
{
    auto max = first;

    while (first++ != end)
        if (comp(*first, *max))
            max = first;
    
    return *max;
}
