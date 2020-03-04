#include <Sorts.hpp>

template<>
bool ChildrenIdx::childExists<1>(long size)
{
    return idx_ < size;
}

template<>
bool ChildrenIdx::childExists<2>(long size)
{
    return idx_ + 1 < size;
}
