#include "TestRunner.hpp"

namespace test
{

void TestRunner::run()
{
    for (auto test : tests_)
        for (auto sort : sorts_)
            test(sort);
}

}  // namespace test
