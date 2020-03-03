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
    quick_sort(vec.begin(), vec.end());
    timer.printNow();
}

void test_heap_sort()
{
    vector<int> vec;
    fillWithRandom(vec, pow(10, 4));
    auto vec_test = vec;

    Timer timer(std::cout, "TimerHeapSort");
    heap_sort(vec.begin(), vec.end());
    timer.printNow();

    std::sort(vec_test.begin(), vec_test.end());
    std::cout << "Is good? " << std::equal(vec_test.begin(), vec_test.end(), vec.begin()) << std::endl;
}

void mySwap(int& i, int& j)
{
    int temp = i;
    i = j;
    j = temp;
}

int main()
{
    vector test{5, 10, 8, 7, 42, 90, 56};

    //makeHeapMax(test.begin(), test.end());
    heap_sort(test.begin(), test.end());

    for (auto el : test)
        std::cout << el << ", ";
    
    std::cout << std::endl;

    //test_heap_sort();

    int a = 5;
    int b = 3;
    mySwap(a, b);
    std::cout << a << " : " << b << std::endl;
}
