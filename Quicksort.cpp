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
#include <cmath>

using namespace std;

/**
 * This partiion version is not original scheme proposed by Hoare, but it's proposed by Nico Lomuto.
 */
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

/*
 * This partition is based on Hoare's approach.
 * It's more efficient than Lomuto's with reduced 3x number of compare/swap, and different chosen of pivot.
 */
static int PartitionHoare(vector<int>& v, int low, int high)
{
    int pivot = v[std::floor((low + high) / 2)];
    int i = low - 1;
    int j = high + 1;
    while (true)
    {
        do {
            ++i;
        } while (v[i] < pivot);

        do {
            --j;
        } while (v[j] > pivot);

        if (i >= j)
            return j;
        std::swap(v[i], v[j]);
    }
}

static void QuicksortHoare(vector<int>& v, int l, int r)
{
    if (l < r)
    {
        int p = PartitionHoare(v, l, r);
        QuicksortHoare(v, l, p);
        QuicksortHoare(v, p+1, r);
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

    PROFILE_START
    QuicksortHoare(v, 0, v.size()-1);
    PROFILE_END
    PRINTARRAY(v)
    PROFILE_PRINT
    
    return 0;
}

