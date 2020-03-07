#pragma once

template<typename Iter_t>
using ValFromIter = typename std::remove_reference<decltype(*std::declval<Iter_t>())>::type;
