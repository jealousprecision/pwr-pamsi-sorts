#include <cstdlib>
#include <ctime>

#include <iostream>
#include <vector>

#include <Sorts.hpp>
#include <PrintTools.hpp>


using namespace std;

void fillWithRandom(vector<int>& vec, unsigned count, unsigned max, int offset)
{
    for (int i = 0; i < count; ++i)
        vec.push_back(rand() % (max+1) + offset);
}

int main()
{
    srand(time(nullptr));
    vector<int> vec;
    fillWithRandom(vec, 50, 20, 0);

    merge_sort(vec.begin(), vec.end());

    cout << "vector vec: ";
    PrintTools::printContainer(cout, vec);
    cout << endl;
}