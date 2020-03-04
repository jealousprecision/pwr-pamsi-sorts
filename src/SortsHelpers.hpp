#pragma once

#include <functional>

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
