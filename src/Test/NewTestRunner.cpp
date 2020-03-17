#include "NewTestRunner.hpp"

namespace test
{

void NewTestRunner::run()
{
    for (auto sort : sorts_)
        for (const auto& test : factory_->create())
            test->run(sort);
}

}  // namespace test
