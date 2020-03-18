#pragma once

#include <memory>
#include <vector>
#include <Sorts/SortAbstract.hpp>
#include <Test/ITest.hpp>
#include <Test/ITestFactory.hpp>

namespace test
{

class NewTestRunner
{
public:
    NewTestRunner(ITestFactory& factory, std::vector<SortAbstract::Sorts> sorts) :
        factory_(factory), sorts_(std::move(sorts))
    {}
    virtual ~NewTestRunner() = default;

    virtual void run();

protected:
    ITestFactory& factory_;
    std::vector<SortAbstract::Sorts> sorts_;
};

}
