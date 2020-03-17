#pragma once

#include "ITest.hpp"

#include <Algo.hpp>

namespace test
{

class SortsCorrectlyTest : public ITest
{
public:
    SortsCorrectlyTest(size_t times = 100, size_t length = algo::pow(10, 5)) :
        times_(times), length_(length)
    {}

    void run(SortAbstract::Sorts) override;

protected:
    size_t times_;
    size_t length_;
};

class WorksWithListsTest : public ITest
{
public:
    WorksWithListsTest(size_t times = 1, size_t length = algo::pow(10, 5)) :
        times_(times), length_(length)
    {}

    void run(SortAbstract::Sorts) override;

protected:
    size_t times_;
    size_t length_;
};

}  // namespace test
