#pragma once

#include <string>
#include <Sorts/SortAbstract.hpp>

namespace test
{

class ITest
{
public:
    virtual ~ITest() = default;

    virtual void run(SortAbstract::Sorts) = 0;
    virtual const std::string& getName() const = 0;
};

}  // namespace test
