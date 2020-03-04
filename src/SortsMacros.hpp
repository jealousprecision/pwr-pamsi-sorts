#pragma once

// get value type from templated Iterator typename without initializing any variables
#define GET_VAL_T_FROM_ITER_T(Iter_t) typename std::remove_reference<decltype(*std::declval<Iter_t>())>::type

template<typename Iter_t>
using ValFromIter = typename std::remove_reference<decltype(*std::declval<Iter_t>())>::type;
