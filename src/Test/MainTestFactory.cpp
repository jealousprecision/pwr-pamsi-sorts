#include "MainTestFactory.hpp"

#include <memory>
#include <Test/MainTest.hpp>

namespace test
{

ITestFactory::TestContainer MainTestFactory::create() const
{
    sheets_.emplace_back();
    auto& sheet = sheets_.back();
    TestContainer ret;

    for (auto arrayLength : lengths_)
    {
        for (auto percentage : percentages_)
        {
            ret.emplace_back(new SimpleMainTest(
                testsLength_,
                arrayLength,
                SortedRangeMaker(percentage),
                sheet,
                "MainTest; " + PrintTools::to_string_with_precision(arrayLength, 4) + "; "
                    + PrintTools::to_string_with_precision(percentage * 100, 4)
            ));
        }

        ret.emplace_back(new SimpleMainTest(
            testsLength_,
            arrayLength,
            ReverseRangeMaker(),
            sheet,
            "MainTest; " + PrintTools::to_string_with_precision(arrayLength, 4) + "; rvrs"
        ));
    }

    return ret;
}

}  // namespace test
