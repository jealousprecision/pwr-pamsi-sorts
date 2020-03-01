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

void test_quick_sort()
{
    vector<int> vec;
    fillWithRandom(vec, pow(10, 6), numeric_limits<int>::max(), 0);
    auto vec_test = vec;


    Timer timer(std::cout, "TimerQuickSort");
    quick_sort(vec.begin(), vec.end());
    timer.printNow();

    timer.reset();
    std::sort(vec_test.begin(), vec_test.end());
    timer.printNow();
    
    cout << "Is good? " << std::equal(vec_test.begin(), vec_test.end(), vec.begin()) << endl;
}

void test_merge_sort()
{
    vector<int> vec;
    fillWithRandom(vec, pow(10, 6), numeric_limits<int>::max(), 0);
    auto vec_test = vec;

    Timer timer(std::cout, "TimerMergeSort");
    merge_sort(vec.begin(), vec.end());
    timer.printNow();

    timer.reset();
    std::sort(vec_test.begin(), vec_test.end());
    timer.printNow();

    cout << "Is good? " << std::equal(vec_test.begin(), vec_test.end(), vec.begin()) << endl;
}

int main()
{
    srand(time(nullptr));
    vector<int> vec;

    fillWithRandom(vec, 20, 50, 0);

    test_quick_sort();
    test_merge_sort();
}