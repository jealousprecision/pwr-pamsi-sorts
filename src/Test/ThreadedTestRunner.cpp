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
    ThreadEnvironment(std::unique_ptr<ITest>&& test, SortAbstract::Sorts sort) :
        test_(std::move(test)), sort_(sort)
    {}

    void operator() ()
    {
        test_->run(sort_);

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

    std::unique_ptr<ITest> test_;
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
        for (auto&& test : factory_.create())
            envs.emplace_back(new ThreadEnvironment(std::move(test), sort));

    for (const auto& env : envs)
        threads.emplace_back(std::reference_wrapper<ThreadEnvironment>(*env));

    size_t done;
    while ((done = std::count_if(envs.begin(), envs.end(), isThreadDone)) != envs.size())
    {
        std::cout << "Done: " << done << "/" << envs.size();
        std::cout << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        std::cout << deleteLine;
    }

    for (auto& thread : threads)
        thread.join();
}

}  // namespace test
