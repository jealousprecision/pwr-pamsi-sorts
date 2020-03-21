#include "MainTest.hpp"

#include <iomanip>
#include <sstream>
#include <vector>
#include <Algo.hpp>
#include <Timer.hpp>

namespace test
{

void SimpleMainTest::run(SortAbstract::Sorts sort)
{
    auto row = sheet_.newRow();
    row.setName(name_ + "; " + SortAbstract::toString(sort));

    Timer timer;

    Container container;
    container.resize(arrayLength_);

    for (int i = 0; i < testLength_; ++i)
    {
        rangeMaker_(container.begin(), container.end());

        timer.reset();
        SortAbstract::sortRange(sort, container.begin(), container.end());
        row->push_back(timer.checkNowUs());
    }
}

const std::string& SimpleMainTest::getName() const
{
    return name_;
}

}  // namespace test
