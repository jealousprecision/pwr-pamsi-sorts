#pragma once

#include <functional>
#include <vector>

#include <Sorts/SortAbstract.hpp>

namespace test
{

class TestRunner
{
public:
    using test_t = std::function<void(SortAbstract::Sorts)>;

    TestRunner(
        std::vector<test_t> tests,
        std::vector<SortAbstract::Sorts> sorts) :
        tests_(tests), sorts_(sorts)
    {}

    void run();

private:
    std::vector<test_t> tests_;
    std::vector<SortAbstract::Sorts> sorts_;
};

}  // namespace test
