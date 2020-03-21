#include <cstdlib>
#include <ctime>

#include <fstream>
#include <numeric>

#include <Sorts/SortAbstract.hpp>
#include <Test/Test.hpp>
#include <PrintTools.hpp>

const std::vector<size_t> arrayLengths = {algo::pow(10, 5) * 5, algo::pow(10, 6)};

const std::vector<double> percentages = {0.0, 0.25, 0.5, 0.75, 0.9, 0.99, 0.997};

const size_t testsLength = 100u;

int main()
{
    srand(time(nullptr));

    test::MainTestFactory factory(testsLength, arrayLengths, percentages);
    test::ThreadedTestRunner testRunner(
        factory,
        {
            SortAbstract::Sorts::merge,
            SortAbstract::Sorts::intro,
            SortAbstract::Sorts::quick
        });

    testRunner.run();

    PrintTools::Sheet<unsigned> mainsheet;
    for (const auto& sheet : factory.getSheets())
        mainsheet += sheet;

    std::ofstream csv("result.csv");
    csv << "SEP=,\n"; // excel is dumb
    mainsheet.dump(csv);
    csv.close();
}
