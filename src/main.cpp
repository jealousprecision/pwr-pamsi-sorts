#include <cstdlib>
#include <ctime>

#include <fstream>
#include <vector>

#include <Sorts/SortAbstract.hpp>
#include <Test/Test.hpp>
#include <PrintTools.hpp>

const std::vector<size_t> arrayLengths =
    {algo::pow(10, 4), algo::pow(10, 4) * 5, algo::pow(10, 5), algo::pow(10, 5) * 5, algo::pow(10, 6)};

const std::vector<double> percentages =
    {0.0, 0.25, 0.5, 0.75, 0.9, 0.99, 0.997};

const std::vector<SortAbstract::Sorts> sorts =
    {SortAbstract::Sorts::merge, SortAbstract::Sorts::intro, SortAbstract::Sorts::quick};

const size_t testsLength = 100u;

int main()
{
    srand(time(nullptr));

    test::MainTestFactory factory(testsLength, arrayLengths, percentages);
    test::TestRunner testRunner(factory, sorts);

    testRunner.run();

    PrintTools::Sheet<unsigned> mainsheet;
    for (const auto& sheet : factory.getSheets())
        mainsheet += sheet;

    std::ofstream csv("result.csv");
    csv << "SEP=,\n";  // excel is dumb
    mainsheet.dump(csv);
    csv.close();

    return 0;
}
