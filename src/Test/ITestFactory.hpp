#pragma once

#include <memory>
#include <vector>

#include <Test/ITest.hpp>

namespace test
{

class ITestFactory
{
public:
    using TestContainer = std::vector<std::unique_ptr<ITest>>;

    virtual ~ITestFactory() = default;

    virtual TestContainer create() const = 0;
};

}  // namespace test
