#pragma once

#include <Sorts/SortAbstract.hpp>

namespace test
{

class ITest
{
public:
    virtual void run(SortAbstract::Sorts) = 0;
};

}  // namespace test
