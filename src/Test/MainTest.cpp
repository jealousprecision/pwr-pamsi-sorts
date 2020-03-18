#include "MainTest.hpp"

#include <iomanip>
#include <sstream>
#include <vector>
#include <Algo.hpp>
#include <Timer.hpp>

namespace test
{

namespace
{
    const std::vector<unsigned> defaultLengths = {
        algo::pow(10, 4),
        algo::pow(10, 4) * 5,
        algo::pow(10, 5),
        algo::pow(10, 5) * 5,
        algo::pow(10, 6)};

    const std::vector<double> defaultPercentages = {
        0.0, 0.25, 0.5, 0.75, 0.9, 0.99, 0.997};

    constexpr size_t defaultAvgLength = 100u;
}  // namespace

MainTest::MainTest(std::shared_ptr<PrintTools::Sheet<unsigned>> sheet) :
    MainTest(defaultAvgLength, defaultLengths, defaultPercentages, std::move(sheet))
{}

MainTest::MainTest(size_t avgLength, std::shared_ptr<PrintTools::Sheet<unsigned>> sheet) :
    MainTest(avgLength, defaultLengths, defaultPercentages, std::move(sheet))
{}

MainTest::MainTest(
        size_t avgLength,
        std::vector<unsigned> lengths,
        std::vector<double> percentages,
        std::shared_ptr<PrintTools::Sheet<unsigned>> sheet) :
        avgLength_(avgLength),
        lengths_(lengths),
        percentages_(percentages),
        sheet_(std::move(sheet)),
        allTestsSize_(lengths_.size() * percentages_.size()),
        doneTests_(0)
{}

std::string MainTest::formatLenPercentage(unsigned length, double percentage)
{
    std::stringstream ss;
    ss << length << " " << std::setprecision(3) << percentage << "\%";
    return ss.str();
}

void MainTest::run(SortAbstract::Sorts sort)
{
    Timer timer;
    const std::string testname = "[" + SortAbstract::toString(sort) + "] ";
    std::vector<int> toSort;

    for (auto len : lengths_)
    {
        toSort.resize(len);
        for (auto percentage : percentages_)
        {
            auto row = sheet_->newRow();
            row.setName(testname + formatLenPercentage(len, percentage));

            for (int i = 0; i < avgLength_; ++i)
            {
                algo::fill_random(toSort.begin(), toSort.end());

                timer.reset();
                SortAbstract::sortRange(sort, toSort.begin(), toSort.end());
                row->push_back(timer.checkNowUs());
            }

            doneTests_ += 1;
        }
    }
}

double MainTest::completion() const
{
    return static_cast<double>(doneTests_) / allTestsSize_;
}

}  // namespace test
