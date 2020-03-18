#pragma once

#include "ITestFactory.hpp"

#include <vector>
#include <PrintTools.hpp>

namespace test
{

class MainTestFactory : public ITestFactory
{
public:
    using SheetContainer = std::vector<std::shared_ptr<PrintTools::Sheet<unsigned>>>;

    TestContainer create() const override;

    SheetContainer& getSheets() { return sheets_; }

protected:
    mutable SheetContainer sheets_;
};

}  // namespace test
