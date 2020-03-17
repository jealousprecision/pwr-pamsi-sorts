#include "Tests.hpp"

#include <cstdlib>
#include <numeric>
#include <iostream>
#include <list>
#include <vector>
#include <Timer.hpp>
#include <PrintTools.hpp>

namespace test
{

namespace
{

template<typename Cont>
void fillWithRandom(
    Cont& cont,
    long count = pow(10, 6),
    int max = std::numeric_limits<int>::max(),
    int offset = 0)
{
    algo::generate_n_el(std::back_inserter(cont), count, [&](){return rand() % max + offset;});
}

template<typename Cont>
void fillWithSomewhatSorted(
    Cont& cont,
    long count = pow(10, 6),
    double percentageSorted = 0.0,
    unsigned max = std::numeric_limits<int>::max())
{
    if (percentageSorted > 1.0)
        throw std::runtime_error("fillWithSomewhatSorted(): Wrong percentage");

    fillWithRandom(cont, count, max);
    auto end = cont.end() - static_cast<unsigned>(cont.size() * (1 - percentageSorted));
    std::sort(cont.begin(), end);
}

void fillSortedOpt(std::vector<int>& vec, double percentageSorted)
{
    if (percentageSorted > 1.0)
        throw std::runtime_error("fillSortedOpt(): wrong percentage");

    for (int i = 0; i < vec.size(); ++i)
        vec[i] = rand();

    auto end = vec.end() - static_cast<unsigned>(vec.size() * (1 - percentageSorted));
    std::sort(vec.begin(), end);
}

}  // namespace

void sorterSorts(SortAbstract::Sorts sortType)
{
    std::vector<int> vec;
    std::vector<int> vec_sorted;
    bool passed = true;

    constexpr size_t TESTLENGTH = 100;
    std::string testAndSortName = std::string("test_sorterSorts(): sort: [") + SortAbstract::toString(sortType) + "]";
    PrintTools::LoadingBar loadingBar(std::cout, testAndSortName + " progress: ", TESTLENGTH);

    loadingBar.start();
    for (int i = 0; i < TESTLENGTH; ++i)
    {
        fillWithRandom(vec, pow(10, 5));

        vec_sorted = vec;
        std::sort(vec_sorted.begin(), vec_sorted.end());

        SortAbstract::sortRange(sortType, vec.begin(), vec.end());

        loadingBar.markProgress(1);

        if (!std::equal(vec_sorted.begin(), vec_sorted.end(), vec.begin()))
        {
            passed = false;
            break;
        }
    }
    loadingBar.end();

    std::cout << testAndSortName << " passed: " << passed << std::string(6, ' ') << std::endl;
}

void sorterPerformance(SortAbstract::Sorts sortType)
{
    std::vector<int> vec;
    Timer timer;
    std::vector<unsigned> durations;

    constexpr size_t TESTLENGTH = 100;
    std::string testAndSortName = std::string("test_sorterSorts(): sort: [") + SortAbstract::toString(sortType) + "]";
    PrintTools::LoadingBar loadingBar(std::cout, testAndSortName + " progress: ", TESTLENGTH);

    loadingBar.start();
    for (int i = 0; i < TESTLENGTH; ++i)
    {
        fillWithRandom(vec, pow(10, 6));

        timer.reset();
        SortAbstract::sortRange(sortType, vec.begin(), vec.end());
        durations.push_back(timer.checkNowUs());
        loadingBar.markProgress(1);
    }
    loadingBar.end();

    unsigned min = *std::min_element(durations.begin(), durations.end());
    unsigned max = *std::max_element(durations.begin(), durations.end());
    double avg = std::accumulate(durations.begin(), durations.end(), 0.0) / durations.size();

    std::cout << testAndSortName << ":"
            << "\n\tMax: " << max / pow(10, 3)
            << " ms\n\tMin: " << min / pow(10, 3)
            << " ms\n\tAverage: " << avg / pow(10, 3) << " ms" << std::endl;
}

void sorterWorksWithLists(SortAbstract::Sorts sort)
{
    if (sort == SortAbstract::Sorts::heap)
    {
        std::cerr << "test_sorterWorksWithLists(): sort: [HeapSort], skipping" << std::endl;
        return;
    }

    std::list<int> lst;
    std::vector<int> vec_sorted;
    size_t size = pow(10, 5);

    fillWithRandom(lst, size);

    vec_sorted.reserve(size);
    std::copy(lst.begin(), lst.end(), std::back_inserter(vec_sorted));
    std::sort(vec_sorted.begin(), vec_sorted.end());

    SortAbstract::sortRange(sort, lst.begin(), lst.end());

    std::cout << "test_sorterWorksWithLists(): sort: [" << SortAbstract::toString(sort) << "], passed: "
        << std::equal(vec_sorted.begin(), vec_sorted.end(), lst.begin()) << std::endl;
}

void sorterWorksWithComparators(SortAbstract::Sorts sort)
{
    std::vector<int> vec;
    fillWithRandom(vec);
    std::vector<int> vec_sorted(vec);

    auto descending = [](int i, int j) { return i > j; };

    std::sort(vec_sorted.begin(), vec_sorted.end(), descending);
    SortAbstract::sortRange(sort, vec.begin(), vec.end(), descending);

    std::cout << "test_sorterWorksWithComparators(): sort: [" << SortAbstract::toString(sort) << "] passed: "
        << std::equal(vec_sorted.begin(), vec_sorted.end(), vec.begin()) << std::endl;
}

void sorterExcercise(SortAbstract::Sorts sort)
{
    size_t testLengths[] = {algo::pow(10, 4), algo::pow(10, 4) * 5, algo::pow(10, 5), algo::pow(10, 5) * 5, algo::pow(10, 6)};
    //size_t testLengths[] = {algo::pow(10, 4)};
    double sortedPercentage[] = {0.0, 0.25, 0.5, 0.75, 0.95, 0.99, 0.997};
    //double sortedPercentage[] = {0.0};
    constexpr size_t NOOFTESTS = 100;
    Timer timer;
    std::string testname = "test_sorterExcercise(): sort: [" + SortAbstract::toString(sort) + "]: ";

    for (auto len : testLengths)
    {
        auto testname_with_len = testname + "Length " + std::to_string(len) + ": ";
        for (auto percentage : sortedPercentage)
        {
            auto testname_with_len_with_perc =
                testname_with_len + "Sorted in " + PrintTools::to_string_with_precision(percentage * 100, 3) + "\%: ";

            std::vector<int> cont;
            cont.resize(len);
            PrintTools::LoadingBar loadingBar(std::cout, testname_with_len_with_perc, NOOFTESTS);
            auto row = PrintTools::getSheetInstance()->newRow();
            row.setName(testname_with_len_with_perc);

            loadingBar.start();
            for (int i = 0; i < NOOFTESTS; ++i)
            {
                fillSortedOpt(cont, percentage);

                timer.reset();
                SortAbstract::sortRange(sort, cont.begin(), cont.end());
                row->push_back(timer.checkNowUs());

                loadingBar.markProgress(1);
            }
            loadingBar.end();

            std::cout << testname_with_len_with_perc
                << "Average " << algo::average(row->begin(), row->end(), 0.0) / 1000 << " ms: " << std::endl;
        }
    }

}

}  // namespace test
