#pragma once

#include <list>
#include <vector>

#include <PrintTools.hpp>
#include <Test/ITestFactory.hpp>

namespace test
{

class MainTestFactory : public ITestFactory
{
public:
    using SheetContainer = std::list<PrintTools::Sheet<unsigned>>;

    MainTestFactory(
        size_t testsLength,
        std::vector<size_t> lengths,
        std::vector<double> percentages) :
            testsLength_(testsLength),
            lengths_(lengths),
            percentages_(percentages)
    {}

    TestContainer create() const override;
    SheetContainer& getSheets() { return sheets_; }

protected:
    mutable SheetContainer sheets_;

    size_t testsLength_;
    std::vector<size_t> lengths_;
    std::vector<double> percentages_;
};

}  // namespace test
