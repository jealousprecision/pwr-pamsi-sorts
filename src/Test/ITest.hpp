#pragma once

#include <Sorts/SortAbstract.hpp>

namespace test
{

class ITest
{
public:
    virtual ~ITest() = default;

    virtual void run(SortAbstract::Sorts) = 0;
    virtual double completion() const;
};

}  // namespace test
