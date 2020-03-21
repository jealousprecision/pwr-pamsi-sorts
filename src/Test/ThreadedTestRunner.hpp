#pragma once

#include <Test/TestRunner.hpp>

namespace test
{

class ThreadedTestRunner : public TestRunner
{
public:
    ThreadedTestRunner(
        ITestFactory& factory,
        std::vector<SortAbstract::Sorts> sorts) :
            TestRunner(factory, std::move(sorts))
    {}

    void run() override;
};

}  // namespace test
