#include <cstdlib>
#include <ctime>

#include <fstream>

#include <Sorts/SortAbstract.hpp>
#include <Test/Test.hpp>
#include <PrintTools.hpp>

int main()
{
    srand(time(nullptr));

    test::MainTestFactory factory;
    test::ThreadedTestRunner testRunner(
        factory,
        {
            SortAbstract::Sorts::merge,
            SortAbstract::Sorts::intro,
            SortAbstract::Sorts::quick
        });

    testRunner.run();

    auto sheets = factory.getSheets();
    auto sheet = std::accumulate(sheets.begin() + 1, sheets.end(), sheets.front(),
        [](const auto& ret, const auto& toSum)
        {
            (*ret) += (*toSum);
            return ret;
        });

    std::ofstream csv("tests.csv");
    sheet->dump(csv);
    csv.close();
}
