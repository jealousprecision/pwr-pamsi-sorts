#include <cstdlib>
#include <ctime>

#include <fstream>

#include <Sorts/SortAbstract.hpp>
#include <Test/Test.hpp>
#include <PrintTools.hpp>

test::NewTestRunner::TestContainer getTests()
{
    test::NewTestRunner::TestContainer ret;

    ret.emplace_back(new test::SortsCorrectlyTest());
    ret.emplace_back(new test::WorksWithListsTest(100));

    return ret;
}

int main()
{
    srand(time(nullptr));

    test::NewTestRunner testRunner(
        std::make_unique<test::BasicTestFactory>(),
        {
            SortAbstract::Sorts::merge,
            SortAbstract::Sorts::intro,
            SortAbstract::Sorts::quick
        });

    testRunner.run();
}
