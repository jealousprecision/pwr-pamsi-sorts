#pragma once

#include <vector>

#include <utility>

#include <Sorts/SortAbstract.hpp>
#include <Test/ITest.hpp>
#include <Test/ITestFactory.hpp>
#include <Test/ITestRunner.hpp>

namespace test
{

class TestRunner : public ITestRunner
{
public:
    TestRunner(ITestFactory& factory, std::vector<SortAbstract::Sorts> sorts) :
        factory_(factory), sorts_(std::move(sorts))
    {}

    void run() override;

protected:
    ITestFactory& factory_;
    std::vector<SortAbstract::Sorts> sorts_;
};

}  // namespace test
