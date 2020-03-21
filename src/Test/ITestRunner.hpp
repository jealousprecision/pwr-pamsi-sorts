#pragma once

namespace test
{

class ITestRunner
{
public:
    virtual ~ITestRunner() = default;

    virtual void run() = 0;
};

}  // namespace test
