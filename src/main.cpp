#include <cstdlib>
#include <ctime>

#include <Sorts/SortAbstract.hpp>
#include <Test/Test.hpp>

int main()
{
    srand(time(nullptr));

    test::TestRunner testRunner(
        {
            //test::sorterSorts,
            //test::sorterPerformance,
            //test::sorterWorksWithLists,
            //test::sorterWorksWithComparators
            test::sorterExcercise
        },
        {
            SortAbstract::Sorts::quick,
            SortAbstract::Sorts::merge,
            //SortAbstract::Sorts::heap,
            SortAbstract::Sorts::intro
        });

    testRunner.run();
}
