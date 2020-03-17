#include <cstdlib>
#include <ctime>

#include <fstream>

#include <Sorts/SortAbstract.hpp>
#include <Test/Test.hpp>
#include <PrintTools.hpp>

int main()
{
    srand(time(nullptr));

    std::ofstream csvFile;
    csvFile.open("testresults.csv");
    if (!csvFile)
        throw std::runtime_error("Can't open csv file");

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

    PrintTools::getSheetInstance()->dump(csvFile);
    csvFile.close();
}
