/**
 * Implementation of selection sort.
 *
 * Selection sort works like this
 * it keeps finding the smallest element in the range, then swap with the first element, then finding
 * second smallest element then swap with second element, keep doing like this until entire range is sorted.
 *
 * Compile with
 *  g++ -std=c++11 -I. Algorithm/SelectionSort.cpp
 */

#include "Util.h"
#include <vector>
#include <algorithm>

static void SelectionSort(std::vector<int>& v)
{
    if (v.size() < 1)
        return;

    for (int i=0; i<v.size()-1; ++i)
    {
        int smallest = v[i];
        int mark = -1;
        for (int j=i+1; j<v.size(); ++j)
        {
            if (smallest > v[j])
            {
                smallest = v[j];
                mark = j;
            }
        }
        if (mark != -1)
            std::swap(v[i], v[mark]);
    }
}

int main()
{
    std::vector<int> v {5,9,7,14,2,0,35};
    PRINTARRAY(v)
    SelectionSort(v);
    PRINTARRAY(v)

    return 0;
}
