#pragma once

#include <memory>
#include <string>
#include <vector>
#include <Test/ITest.hpp>
#include <PrintTools.hpp>

namespace test
{

class MainTest : public ITest
{
public:
    MainTest(std::shared_ptr<PrintTools::Sheet<unsigned>> sheet);
    MainTest(size_t avgLengths, std::shared_ptr<PrintTools::Sheet<unsigned>> sheet);
    MainTest(
        size_t avgLength,
        std::vector<unsigned> lengths,
        std::vector<double> percentages,
        std::shared_ptr<PrintTools::Sheet<unsigned>> sheet);

    void run(SortAbstract::Sorts sort) override;
    double completion() const override;

protected:
    std::string formatLenPercentage(unsigned length, double percentage);

    size_t avgLength_;
    std::vector<unsigned> lengths_;
    std::vector<double> percentages_;

    size_t allTestsSize_;
    size_t doneTests_;
    std::shared_ptr<PrintTools::Sheet<unsigned>> sheet_;
};

}  // namespace test
