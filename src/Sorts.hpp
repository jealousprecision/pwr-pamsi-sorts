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

template<typename T>
class debug_vector
{
public:
    using value_type = typename std::vector<T>::value_type;

    debug_vector(std::vector<T>& parent, std::ostream& os) :
        parent_(parent), os_(os)
    {}

    void push_back(const T& val)
    {
        if (parent_.size() == parent_.capacity())
            os_ << "mystd::debug_vector::push_back(..) Warning! size () == capacity(), ie vector will grow\n";
        parent_.push_back(val);
    }

    auto begin() { return parent_.begin(); }
    auto end() { return parent_.end(); }
    auto begin() const { return parent_.begin(); }
    auto end() const { return parent_.end(); }

private:
    std::vector<T>& parent_;
    std::ostream& os_;
};

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

