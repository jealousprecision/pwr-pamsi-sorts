#include "BasicTestFactory.hpp"

#include <Algo.hpp>
#include <Test/SimpleTests.hpp>

namespace test
{

ITestFactory::TestContainer BasicTestFactory::create() const
{
    TestContainer ret;

    ret.emplace_back(new SortsCorrectlyTest(100, algo::pow(10, 5)));
    ret.emplace_back(new WorksWithListsTest(1, algo::pow(10, 5)));

    return ret;
}

}  // namespace test
