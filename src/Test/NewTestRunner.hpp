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
    using TestContainer = std::vector<std::unique_ptr<ITest>>;

    NewTestRunner(std::unique_ptr<ITestFactory> factory, std::vector<SortAbstract::Sorts> sorts) :
        factory_(std::move(factory)), sorts_(std::move(sorts))
    {}

    void run();

protected:
    std::unique_ptr<ITestFactory> factory_;
    std::vector<SortAbstract::Sorts> sorts_;
};

}
