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

void fillWithRandom(
    vector<int>& vec,
     long count = pow(10,6),
     unsigned max = numeric_limits<unsigned>::max(),
     int offset = 0)
{
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
    timer.printNow("Random");

    fillWithSomewhatSorted(vec, pow(10, 6), numeric_limits<int>::max(), 0.997);
    timer.reset();
    merge_sort(vec.begin(), vec.end());
    timer.printNow("99.7\% sorted");

    fillWithSomewhatSorted(vec, pow(10, 6), numeric_limits<int>::max(), 0.90);
    timer.reset();
    merge_sort(vec.begin(), vec.end());
    timer.printNow("90\% sorted");

    fillWithSomewhatSorted(vec, pow(10, 6), numeric_limits<int>::max(), 0.50);
    timer.reset();
    merge_sort(vec.begin(), vec.end());
    timer.printNow("50\% sorted");
}

void test_heap_sort()
{
    vector<int> vec;
    fillWithRandom(vec, pow(10, 6), numeric_limits<int>::max(), 0);
    auto vec_test = vec;

    Timer timer(cout, "TimerHeapSort");
    heap_sort(vec.begin(), vec.end());
    timer.printNow("Random");

    std::sort(vec_test.begin(), vec_test.end());
    std::cout << "Is good? " << std::equal(vec_test.begin(), vec_test.end(), vec.begin()) << std::endl;
}

bool isHeapMax(const vector<int>& vec, long idx)
{
    auto children = ChildFactory::makeChildren(vec.begin(), vec.end(), idx);
    bool oneMax = false;
    bool twoMax = false;

    if(children.first)
        oneMax = isHeapMax(vec, children.first.index());
    else
        oneMax = true;
    
    if(children.second)
        twoMax = isHeapMax(vec, children.second.index());
    else
        twoMax = true;

    return oneMax && twoMax;
}


int main()
{
    //test_merge_sort();
    //test_heap_sort();

    vector<int> vec;
    fillWithRandom(vec, pow(10,3));

    makeHeapMax(vec.begin(), vec.size(), 0, std::greater<int>());
    std::cout << "isHeapMax(): " << isHeapMax(vec, 0) << endl;
}
