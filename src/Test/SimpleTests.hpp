#pragma once

#include <string>

#include <Test/ITest.hpp>
#include <Algo.hpp>

namespace test
{

class SortsCorrectlyTest : public ITest
{
public:
    SortsCorrectlyTest(size_t times, size_t length) :
        times_(times), length_(length)
    {}

    void run(SortAbstract::Sorts) override;
    const std::string& getName() const override;

protected:
    size_t times_;
    size_t length_;
    std::string name_ = "SortsCorrectlyTest";
};

class WorksWithListsTest : public ITest
{
public:
    WorksWithListsTest(size_t times, size_t length) :
        times_(times), length_(length)
    {}

    void run(SortAbstract::Sorts) override;
    const std::string& getName() const override;

protected:
    size_t times_;
    size_t length_;
    std::string name_ = "WorksWithListsTest";
};

}  // namespace test
