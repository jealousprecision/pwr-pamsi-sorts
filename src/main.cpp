#include <cstdlib>
#include <ctime>
#include <cmath>

#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

#include <Sorts.hpp>
#include <PrintTools.hpp>
#include <Timer.hpp>

using namespace std;

void fillWithRandom(vector<int>& vec, long count, unsigned max, int offset)
{
    vec.clear();
    vec.resize(count);
    
    for (long i=0; i<count; ++i)
        vec[i] = rand() % max + offset;
}

void fillWithSomewhatSorted(vector<int>& vec, long count, unsigned max, double percentageSorted)
{
    if (percentageSorted > 1.0)
        throw std::runtime_error("fillWithSomewhatSorted(): Wrong percentage");

    fillWithRandom(vec, count, max, 0);

    auto end = vec.end() - (unsigned) (vec.size() * (1 - percentageSorted));

    if (end < vec.begin())
        throw std::runtime_error("");

    std::sort(vec.begin(), end);
}

void test_quick_sort()
{
    vector<int> vec;
    fillWithRandom(vec, pow(10, 6), numeric_limits<int>::max(), 0);

    Timer timer(std::cout, "TimerQuickSort");
    quick_sort(vec.begin(), vec.end());
    timer.printNow();
}

void test_merge_sort()
{
    vector<int> vec;
    fillWithRandom(vec, pow(10, 6), numeric_limits<int>::max(), 0);
    auto vec_test = vec;

    Timer timer(std::cout, "TimerMergeSort");
    merge_sort(vec.begin(), vec.end());
    timer.printNow();

    fillWithSomewhatSorted(vec, pow(10, 6), numeric_limits<int>::max(), 0.997);
    timer.reset();
    quick_sort(vec.begin(), vec.end());
    timer.printNow();

    fillWithSomewhatSorted(vec, pow(10, 6), numeric_limits<int>::max(), 0.997);
    timer.reset();
    merge_sort(vec.begin(), vec.end());
    timer.printNow();
}

int main()
{
    srand(time(nullptr));
    vector<int> vec;

    fillWithRandom(vec, 20, 50, 0);

    test_merge_sort();
    test_quick_sort();
}
