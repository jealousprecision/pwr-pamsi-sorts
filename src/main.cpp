#include <cstdlib>
#include <ctime>
#include <cmath>

#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

#include <Sorts.hpp>
#include <PrintTools.hpp>


using namespace std;

void fillWithRandom(vector<int>& vec, long count, unsigned max, int offset)
{
    vec.clear();
    vec.reserve(count);
    
    for (long i=0; i<count; ++i)
        vec.push_back(rand() % max);
}

int main()
{
    srand(time(nullptr));
    vector<int> vec;

    fillWithRandom(vec, 20, 50, 0);

    quick_sort(vec.begin(), vec.end());

    cout << "Vec: ";
    PrintTools::printContainer(cout, vec);
    cout << endl;
}