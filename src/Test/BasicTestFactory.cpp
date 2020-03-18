#include "BasicTestFactory.hpp"

#include <Test/SimpleTests.hpp>

namespace test
{

ITestFactory::TestContainer BasicTestFactory::create() const
{
    TestContainer ret;

    ret.emplace_back(new SortsCorrectlyTest());
    ret.emplace_back(new WorksWithListsTest());

    return ret;
}

}  // namespace test
