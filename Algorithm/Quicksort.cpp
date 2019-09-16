/**
 * Implementation of quicksort algorithm.
 *
 * Quicksort is inplace sorting algorithm which is based on divide-and-conquer approach.
 * Interesting note is that quicksort is used as part of std::sort (which applies 3 sorting algorithms
 * together which are quicksort, heapsort and insertion sort) 's sorting algorithm namely introsort.
 *
 * Use testcases input from testcases/Quicksort.txt, or testcases/50Numbers.txt.
 */

#include "Util.h"
#include <vector>

using namespace std;

static int Partition(vector<int>& v, int low, int high)
{
    // select last element as pivot
    int pivot = v[high];
    int i = low;

    for (int j=low; j<high; ++j)
    {
        if (v[j] < pivot)
        {
            swap(v[i], v[j]);
            ++i;
        }
    }
    swap(v[i], v[high]);
    return i;
}

static void Quicksort(vector<int>& v, int l, int r)
{
    if (l < r)
    {
        int q = Partition(v, l, r);
        Quicksort(v, l, q-1);
        Quicksort(v, q+1, r);
    }
}

int main()
{
    PROFILE_DECLR

    vector<int> v;
    int tmpN;
    while (cin >> tmpN)
        v.push_back(tmpN);
    PRINTARRAY(v)

    PROFILE_START
    Quicksort(v, 0, v.size()-1);
    PROFILE_END
    PRINTARRAY(v)
    PROFILE_PRINT
    
    return 0;
}

