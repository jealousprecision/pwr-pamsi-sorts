#pragma once

#include <Test/NewTestRunner.hpp>

namespace test
{

class ThreadedTestRunner : public NewTestRunner
{
public:
    ThreadedTestRunner(
        ITestFactory& factory,
        std::vector<SortAbstract::Sorts> sorts) :
        NewTestRunner(factory, std::move(sorts))
    {}

    void run() override;

};

}  // namespace test
