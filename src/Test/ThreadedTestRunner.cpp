#include "ThreadedTestRunner.hpp"

#include <atomic>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <functional>
#include <thread>
#include <vector>

namespace test
{

namespace
{

class ThreadEnvironment
{
public:
    ThreadEnvironment(ITestFactory::TestContainer tests, SortAbstract::Sorts sort) :
        tests_(std::move(tests)), sort_(sort), isDone(new std::atomic<bool>(false))
    {}

    void operator() ()
    {
        for (auto& test : tests_)
            test->run(sort_);
        *isDone = true;
    }

    double getCompletion() const { return tests_.front()->completion(); }
    std::string testname() const { return SortAbstract::toString(sort_); }

    std::unique_ptr<std::atomic<bool>> isDone;

protected:
    ITestFactory::TestContainer tests_;
    SortAbstract::Sorts sort_;
};

}  // namespace

void ThreadedTestRunner::run()
{
    constexpr auto deleteLine = "\033[2K\r";
    std::vector<ThreadEnvironment> envs;
    std::vector<std::thread> threads;

    for (auto sort : sorts_)
        envs.emplace_back(factory_.create(), sort);

    for (auto& env : envs)
        threads.emplace_back(std::reference_wrapper<ThreadEnvironment>(env));

    std::cout << std::setprecision(3);
    while (!std::all_of(envs.begin(), envs.end(), [](const auto& el)->bool{return *el.isDone;}))
    {
        for (const auto& env : envs)
            std::cout << env.testname() << ": " << env.getCompletion() << "|| ";

        std::cout << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        std::cout << deleteLine;
    }

    for (auto& thread : threads)
        thread.join();
}

}  // namespace test
