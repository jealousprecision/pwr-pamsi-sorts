#pragma once

#include <memory>
#include <string>
#include <vector>
#include <functional>
#include <stdexcept>
#include <limits>
#include <Test/ITest.hpp>
#include <PrintTools.hpp>

namespace test
{

class SimpleMainTest : public ITest
{
public:
    using Container = std::vector<int>;
    using RangeMaker = std::function<void (Container::iterator, Container::iterator)>;
    using Sheet = PrintTools::Sheet<unsigned>;

    SimpleMainTest(
        size_t testLength,
        size_t arrayLength,
        RangeMaker rangeMaker,
        Sheet& sheet,
        const std::string& name) :
            testLength_(testLength),
            arrayLength_(arrayLength),
            name_(name),
            rangeMaker_(rangeMaker),
            sheet_(sheet)
    {}

    void run(SortAbstract::Sorts sort) override;
    const std::string& getName() const override;

protected:
    size_t testLength_;
    size_t arrayLength_;
    std::string name_;
    RangeMaker rangeMaker_;
    Sheet& sheet_;
};

struct SortedRangeMaker
{
    SortedRangeMaker(double percentage)
    {
        if (percentage > 1.0 || percentage < 0.0)
            throw std::logic_error("SortedRangeMaker::SortedRangeMaker(): percentage not in [0, 1] range");

        percentage_ = percentage;
    }

    SortedRangeMaker(double percentage, size_t max) :
        SortedRangeMaker(percentage)
    {
        max_ = max;
    }

    template<typename Iter>
    void operator() (Iter iter, Iter end)
    {
        algo::fill_random(iter, end, max_);

        auto size = std::distance(iter, end);
        auto middleEnd = std::next(iter, percentage_ * size);

        intro_sort(iter, middleEnd);
    }

protected:
    double percentage_;
    size_t max_ = std::numeric_limits<size_t>::max();
};

struct ReverseRangeMaker
{
    ReverseRangeMaker() = default;
    ReverseRangeMaker(size_t max) :
        max_(max)
    {}

    template<typename Iter>
    void operator() (Iter iter, Iter end)
    {
        algo::fill_random(iter, end, max_);
        intro_sort(iter, end, std::greater<ValFromIter<Iter>>());
    }

protected:
    size_t max_ = std::numeric_limits<size_t>::max();
};

}  // namespace test
