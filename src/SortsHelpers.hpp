#pragma once

#include <functional>

template<typename T>
using RefTo = std::reference_wrapper<T>;

template<typename T>
RefTo<T> getMaxEl(RefTo<T> max)
{
    return max;
}

template<typename T, typename... Args>
RefTo<T> getMaxEl(RefTo<T> max, T& newArg, Args&... args)
{
    if (max.get() < newArg)
        max = newArg;

    return getMaxEl(max, args...);
}

template<typename T, typename... Args>
RefTo<T> getMaxEl(T& val, Args&... args)
{
    RefTo<T> ref = val;
    return getMaxEl(ref, args...);
}