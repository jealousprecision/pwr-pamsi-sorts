#include <cstdlib>
#include <ctime>
#include <cmath>

#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>
#include <numeric>
#include <list>

#include <SortAbstract.hpp>
#include <PrintTools.hpp>
#include <Timer.hpp>
#include <Algo.hpp>

using namespace std;

template<typename Cont>
void fillWithRandom(
    Cont& cont,
    long count = pow(10, 6),
    int max = numeric_limits<int>::max(),
    int offset = 0)
{
    cont.clear();

    algo::generate_n_el(std::back_inserter(cont), count,
        [&]()
        {
            return rand() % max + offset;
        });
}

template<typename Cont>
void fillWithSomewhatSorted(
    Cont& cont,
    long count = pow(10, 6),
    unsigned max = numeric_limits<int>::max(),
    double percentageSorted = 0.0)
{
    if (percentageSorted > 1.0)
        throw std::runtime_error("fillWithSomewhatSorted(): Wrong percentage");

    fillWithRandom(cont, count, max);
    auto end = cont.end() - static_cast<unsigned>(cont.size() * (1 - percentageSorted));
    std::sort(cont.begin(), cont);
}

void test_sorterSorts(SortAbstract::Sorts sortType)
{
    vector<int> vec;
    vector<int> vec_sorted;
    bool passed = true;
    auto logCompletion =
        [&](int percent)
        {
            std::cout << "test_sorterSorts(): sort: [" << SortAbstract::toString(sortType)
                << "]: Completed: " << percent << "\%\n";
        };
    auto resetLine =
        []()
        {
            std::cout << "\033[F";
        };

    logCompletion(0);
    for (int i = 0; i < 100; ++i)
    {
        fillWithRandom(vec, pow(10, 5));

        vec_sorted = vec;
        std::sort(vec_sorted.begin(), vec_sorted.end());

        SortAbstract::sortRange(sortType, vec.begin(), vec.end());

        resetLine();
        logCompletion(i);

        if (!std::equal(vec_sorted.begin(), vec_sorted.end(), vec.begin()))
        {
            passed = false;
            break;
        }
    }
    resetLine();

    std::cout << "test_sorterSorts(): sort: [" << SortAbstract::toString(sortType)
        << "] passed: " << passed << std::string(6, ' ') << std::endl;
}

void test_sorterPerformance(SortAbstract::Sorts sort)
{
    vector<int> vec;
    Timer timer;
    vector<unsigned> durations;

    for (int i = 0; i < pow(10, 2); ++i)
    {
        fillWithRandom(vec, pow(10, 5));

        timer.reset();
        SortAbstract::sortRange(sort, vec.begin(), vec.end());
        durations.push_back(timer.checkNowUs());
    }

    unsigned min = *std::min_element(durations.begin(), durations.end());
    unsigned max = *std::max_element(durations.begin(), durations.end());
    double avg = std::accumulate(durations.begin(), durations.end(), 0.0) / durations.size();

    cout << "test_sorterPerformance() : " << SortAbstract::toString(sort)
        << "\n\tMax: " << max / pow(10, 3)
        << " ms\n\tMin: " << min / pow(10, 3)
        << " ms\n\tAverage: " << avg / pow(10, 3) << " ms" << endl;
}

void test_sorterWorksWithLists(SortAbstract::Sorts sort)
{
    if (sort == SortAbstract::Sorts::heap)
    {
        std::cerr << "test_sorterWorksWithLists(): sort: [HeapSort], skipping" << std::endl;
        return;
    }

    list<int> lst;
    vector<int> vec_sorted;
    size_t size = pow(10, 5);

    fillWithRandom(lst, size);

    vec_sorted.reserve(size);
    std::copy(lst.begin(), lst.end(), std::back_inserter(vec_sorted));
    std::sort(vec_sorted.begin(), vec_sorted.end());

    SortAbstract::sortRange(sort, lst.begin(), lst.end());

    std::cout << "test_sorterWorksWithLists(): sort: [" << SortAbstract::toString(sort) << "], passed: "
        << std::equal(vec_sorted.begin(), vec_sorted.end(), lst.begin()) << std::endl;
}

void test_sorterWorksWithComparators(SortAbstract::Sorts sort)
{
    vector<int> vec;
    fillWithRandom(vec);
    vector<int> vec_sorted(vec);

    auto descending = [](int i, int j) { return i > j; };

    std::sort(vec_sorted.begin(), vec_sorted.end(), descending);
    SortAbstract::sortRange(sort, vec.begin(), vec.end(), descending);

    std::cout << "test_sorterWorksWithComparators(): sort: [" << SortAbstract::toString(sort) << "] passed: "
        << std::equal(vec_sorted.begin(), vec_sorted.end(), vec.begin()) << std::endl;
}

class TestRunner
{
public:
    using test_t = std::function<void(SortAbstract::Sorts)>;

    TestRunner(
        std::vector<test_t> tests,
        std::vector<SortAbstract::Sorts> sorts) :
        tests_(tests), sorts_(sorts)
    {}

    void run()
    {
        for (auto test : tests_)
            for (auto sort : sorts_)
                test(sort);
    }

private:
    std::vector<test_t> tests_;
    std::vector<SortAbstract::Sorts> sorts_;
};

using PrintTools::prettyPrint;

int main()
{
    srand(time(nullptr));

    TestRunner testRunner(
        {
            test_sorterSorts,
            test_sorterPerformance,
            test_sorterWorksWithLists,
            test_sorterWorksWithComparators
        },
        {
            SortAbstract::Sorts::quick,
            SortAbstract::Sorts::merge,
            SortAbstract::Sorts::heap
        });

    testRunner.run();
}
