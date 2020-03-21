#include "ThreadedTestRunner.hpp"

#include <cctype>

#include <atomic>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <functional>
#include <list>
#include <thread>
#include <vector>
#include <mutex>
#include <iterator>

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
        setCurrentName(*test_);
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

    std::thread* parent{nullptr};

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

constexpr size_t maxThreads = 10u;

}  // namespace

void ThreadedTestRunner::run()
{
    const auto isThreadDone = [](const std::unique_ptr<ThreadEnvironment>& env) { return env->isDone(); };
    const auto isAttached = [](const std::unique_ptr<ThreadEnvironment>& env) { return env->parent != nullptr; };

    std::vector<std::unique_ptr<ThreadEnvironment>> envs;
    std::list<std::thread> threads;

    for (auto sort : sorts_)
        for (auto&& test : factory_.create())
            envs.emplace_back(new ThreadEnvironment(std::move(test), sort));

    size_t currentEnv = 0;
    for (; currentEnv < maxThreads && currentEnv < envs.size(); ++currentEnv)
    {
        threads.emplace_back(std::reference_wrapper<ThreadEnvironment>(*envs[currentEnv]));
        envs[currentEnv]->parent = &threads.back();
    }

    size_t done;
    while ((done = std::count_if(envs.begin(), envs.end(), isThreadDone)) != envs.size())
    {
        for (const auto& env : envs)
        {
            if (isThreadDone(env) && isAttached(env))
            {
                // remove joinable threads
                env->parent->join();
                threads.remove_if([&](const auto& el) { return &el == env->parent; });
                env->parent = nullptr;

                if (currentEnv < envs.size())
                {
                    // envs (jobs) still available
                    threads.emplace_back(std::reference_wrapper<ThreadEnvironment>(*envs[currentEnv]));
                    envs[currentEnv]->parent = &threads.back();
                    currentEnv++;
                }
            }
        }

        std::cout << "Done: " << std::setw(3) << done << "/" << envs.size() << "\n";

        int i = 1;
        for (const auto& env : envs)
        {
            if (isAttached(env))
            {
                std::cout << "Worker no. " << i++ << ": " << env->getName() << '\n';
            }
        }

        std::cout << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        std::cout << PrintTools::deleteLine;
    }

    for (auto& thread : threads)
        thread.join();
}

}  // namespace test
