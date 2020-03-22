#include "SimpleTests.hpp"

#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <list>
#include <stdexcept>
#include <string>
#include <vector>

#include <Timer.hpp>

namespace test
{

void SortsCorrectlyTest::run(SortAbstract::Sorts sort)
{
    std::vector<int> vec;
    vec.resize(length_);
    bool passed = true;
    std::string testname =
        "SortsCorrectlyTest: [" + SortAbstract::toString(sort) + "]: ";

    for (size_t i = 0; i < times_; ++i)
    {
        algo::fill_random(vec.begin(), vec.end());
        SortAbstract::sortRange(sort, vec.begin(), vec.end());

        if (!std::is_sorted(vec.begin(), vec.end()))
        {
            passed = false;
            break;
        }
    }

    std::cout << testname << "passed: " << passed << std::endl;
}

const std::string& SortsCorrectlyTest::getName() const
{
    return name_;
}

void WorksWithListsTest::run(SortAbstract::Sorts sort)
{
    std::list<int> list;
    list.resize(length_);
    std::vector<unsigned> durations;
    durations.resize(times_);

    Timer timer;
    std::string testname =
        "WorksWithListsTest: [" + SortAbstract::toString(sort) + "]: ";

    for (size_t i = 0; i < times_; ++i)
    {
        algo::fill_random(list.begin(), list.end());

        timer.reset();
        SortAbstract::sortRange(sort, list.begin(), list.end());
        durations[i] = timer.checkNowUs();
    };

    std::cout << testname << "Average time: "
        << algo::average(durations.begin(), durations.end(), 0.0) / 1000 << " ms" << std::endl;
}

const std::string& WorksWithListsTest::getName() const
{
    return name_;
}

}  // namespace test
