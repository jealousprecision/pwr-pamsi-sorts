#include "ThreadedTestRunner.hpp"

#include <cctype>

#include <atomic>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <functional>
#include <thread>
#include <vector>
#include <mutex>

#include <PrintTools.hpp>

namespace test
{

namespace
{

class ThreadEnvironment
{
public:
    ThreadEnvironment(ITestFactory::TestContainer tests, SortAbstract::Sorts sort) :
        tests_(std::move(tests)), sort_(sort)
    {}

    void operator() ()
    {
        for (int i = 0, n = tests_.size(); i < n; ++i)
        {
            setCurrentName(*tests_[i]);
            tests_[i]->run(sort_);
            completion_ = static_cast<double>(i) / n;
        }

        isDone_ = true;
    }

    double getCompletion() const
    {
        return completion_;
    }

    bool isDone() const
    {
        return isDone_;
    }

    std::string getName()
    {
        while (!nameMutex_.try_lock());

        auto ret = name_;
        nameMutex_.unlock();

        return ret;
    }

protected:
    void setCurrentName(const ITest& test)
    {
        while(!nameMutex_.try_lock());

        name_ = test.getName() + "; " + SortAbstract::toString(sort_);
        nameMutex_.unlock();
    }

    ITestFactory::TestContainer tests_;
    SortAbstract::Sorts sort_;

    std::atomic<bool> isDone_{false};
    std::atomic<double> completion_{0.0};

    std::mutex nameMutex_;
    std::string name_;
};

}  // namespace

void ThreadedTestRunner::run()
{
    constexpr auto deleteLine = "\033[2K\r";
    const auto isThreadDone = [](const std::unique_ptr<ThreadEnvironment>& env) { return env->isDone(); };

    std::vector<std::unique_ptr<ThreadEnvironment>> envs;
    std::vector<std::thread> threads;

    for (auto sort : sorts_)
        envs.emplace_back(new ThreadEnvironment(factory_.create(), sort));

    for (const auto& env : envs)
        threads.emplace_back(std::reference_wrapper<ThreadEnvironment>(*env));

    while (!std::all_of(envs.begin(), envs.end(), isThreadDone))
    {
        for (const auto& env : envs)
            std::cout << env->getName() <<  ": "
                << PrintTools::to_string_with_precision(env->getCompletion() * 100, 4) << "\% || ";

        std::cout << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        std::cout << deleteLine;
    }

    for (auto& thread : threads)
        thread.join();
}

}  // namespace test
