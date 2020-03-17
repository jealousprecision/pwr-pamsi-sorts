#pragma once

#include "ITestFactory.hpp"

namespace test
{

class BasicTestFactory : public ITestFactory
{
public:
    TestContainer create() const override;
};

}
