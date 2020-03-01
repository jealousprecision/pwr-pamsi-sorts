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

void test_heap_sort()
{
    vector<int> vec;
    fillWithRandom(vec, pow(10, 3));
    auto vec_test = vec;

    Timer timer(std::cout, "TimerHeapSort");
    heap_sort(vec.begin(), vec.end());
    timer.printNow();

    std::sort(vec_test.begin(), vec_test.end());
    std::cout << "Is good? " << std::equal(vec_test.begin(), vec_test.end(), vec.begin()) << std::endl;
}

int main()
{
    vector test{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    for (auto el : test)
    {
        std::cout << "Index value: " << el << " -> " << getRowInHeap(el) << endl;
    }

    for (auto el : test)
    {
        std::cout << "Index value: " << el << " links to children: " << getChildrenIdx(el) << endl;
    }

    vector heapIdxTest{4, 10, 5, 1, 8, 42, 420, 69, 2137, 666, 7};

    for (int i = 0; i < heapIdxTest.size(); ++i)
    {
        std::cout << "Index value, value: (" << i << ", " << heapIdxTest[i] << ") is parent to: " 
            << getChildren(heapIdxTest.begin(), heapIdxTest.end(), i) << std::endl;
    }

    cout << "\n\n\n";

    makeHeapMax(heapIdxTest.begin(), heapIdxTest.end());
    for (int i = 0; i < heapIdxTest.size(); ++i)
    {
        std::cout << "Index value, value: (" << i << ", " << heapIdxTest[i] << ") is parent to: " 
            << getChildren(heapIdxTest.begin(), heapIdxTest.end(), i) << std::endl;
    }

    for (int i=0; i < heapIdxTest.size(); ++i)
    {
        auto children = getChildren(heapIdxTest.begin(), heapIdxTest.end(), i);

        if (children.first)
            std::cout << heapIdxTest[i] << " -> " << children.first.get() << ";" << endl;
        if (children.second)
            std::cout << heapIdxTest[i] << " -> " << children.second.get() << ";" << endl;
    }

    test_heap_sort();
}
