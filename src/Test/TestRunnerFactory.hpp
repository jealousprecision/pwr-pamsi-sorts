#pragma once

#include <memory>
#include <stdexcept>

#include <Test/TestRunner.hpp>
#include <Test/ThreadedTestRunner.hpp>
#include <Test/ITestFactory.hpp>
#include <Sorts/SortAbstract.hpp>

namespace test
{

class TestRunnerFactory
{
public:
    static std::unique_ptr<ITestRunner> makeTestRunner(
        ITestFactory& factory,
        std::vector<SortAbstract::Sorts> sorts,
        unsigned threads)
    {
        if (threads == 0)
            throw std::runtime_error("Threads can't be equal to 0");

        if (threads == 1)
            return std::make_unique<TestRunner>(factory, sorts);
        else
            return std::make_unique<ThreadedTestRunner>(factory, sorts, threads);
    }
};

}  // namespace test
