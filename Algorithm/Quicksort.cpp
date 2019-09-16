/**
 * Implementation of quicksort algorithm.
 *
 * Quicksort is inplace sorting algorithm which is based on divide-and-conquer approach.
 * Interesting note is that quicksort is used as part of std::sort (which applies 3 sorting algorithms
 * together which are quicksort, heapsort and insertion sort) 's sorting algorithm namely introsort.
 */

#include <iostream>
#include <vector>

using namespace std;

#define PRINTARRAY(v) for(const int& e: v) cout << e << " "; cout << endl;

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
    vector<int> v ({9, 7, 5, 11, 12, 2, 14, 3, 10, 6});
    PRINTARRAY(v)

    Quicksort(v, 0, v.size()-1);
    PRINTARRAY(v)
    
    return 0;
}

