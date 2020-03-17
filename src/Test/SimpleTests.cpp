#include "SimpleTests.hpp"

#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <list>
#include <vector>

#include <Timer.hpp>

namespace test
{

namespace
{

template<typename Iter>
void fillRandom(Iter iter, Iter end)
{
    for (; iter != end; ++iter)
        *iter = std::rand();
}

}  // namespace

void SortsCorrectlyTest::run(SortAbstract::Sorts sort)
{
    std::vector<int> vec;
    vec.resize(length_);
    bool passed = true;
    std::string testname =
        "SortsCorrectlyTest: [" + SortAbstract::toString(sort) + "]: ";

    for (int i = 0; i < times_; ++i)
    {
        fillRandom(vec.begin(), vec.end());
        SortAbstract::sortRange(sort, vec.begin(), vec.end());

        if (!std::is_sorted(vec.begin(), vec.end()))
        {
            passed = false;
            break;
        }
    }

    std::cout << testname << "passed: " << passed << std::endl;
}

void WorksWithListsTest::run(SortAbstract::Sorts sort)
{
    std::list<int> list;
    list.resize(length_);
    unsigned durations[times_];
    Timer timer;
    std::string testname =
        "WorksWithListsTest: [" + SortAbstract::toString(sort) + "]: ";

    for (int i = 0; i < times_; ++i)
    {
        fillRandom(list.begin(), list.end());

        timer.reset();
        SortAbstract::sortRange(sort, list.begin(), list.end());
        durations[i] = timer.checkNowUs();
    };

    std::cout << testname << "Average time: "
        << algo::average(durations, durations + times_, 0.0) / 1000 << " ms" << std::endl;
}

}  // namespace test
