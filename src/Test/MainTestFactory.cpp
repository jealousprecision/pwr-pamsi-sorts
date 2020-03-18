#include "MainTestFactory.hpp"

#include <memory>
#include <Test/MainTest.hpp>

namespace test
{

ITestFactory::TestContainer MainTestFactory::create() const
{
    sheets_.emplace_back(new PrintTools::Sheet<unsigned>());
    TestContainer ret;

    ret.emplace_back(new MainTest(50, {algo::pow(10, 4), algo::pow(10, 6)}, {0.0, 0.997}, sheets_.back()));

    return ret;
}

}  // namespace test
