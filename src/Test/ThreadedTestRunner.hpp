#pragma once

#include <Test/TestRunner.hpp>

namespace test
{

class ThreadedTestRunner : public TestRunner
{
public:
    ThreadedTestRunner(
        ITestFactory& factory,
        std::vector<SortAbstract::Sorts> sorts,
        size_t threads) :
            TestRunner(factory, std::move(sorts))
    {
        threads_ = threads;
    }

    void run() override;

protected:
    size_t threads_;
};

}  // namespace test
