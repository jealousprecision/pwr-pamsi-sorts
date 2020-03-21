#include "TestRunner.hpp"

#include <iostream>

#include <PrintTools.hpp>

namespace test
{

void TestRunner::run()
{
    auto tests = factory_.create();
    auto size = tests.size() * sorts_.size();
    size_t done = 0;

    for (auto sort : sorts_)
    {
        std::cout << SortAbstract::toString(sort) << std::endl;
        for (const auto& test : tests)
        {
            std::cout << "Done: " << done++ << "/" << size << " Current: " << test->getName() << std::flush;
            test->run(sort);
            std::cout << PrintTools::deleteLine;
        }
    }
}

}  // namespace test
