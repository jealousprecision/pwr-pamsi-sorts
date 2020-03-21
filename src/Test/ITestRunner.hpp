#pragma once

namespace test
{

class ITestRunner
{
public:
    virtual void run() = 0;

    virtual ~ITestRunner() = default;
};

}  // namespace test
