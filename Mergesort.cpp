/**
 * Implementation of mergesort
 *
 * Mergesort is one of the most efficient sorting algorithm. It uses principle of divide-and-conquer
 * similar to quicksort. It breaks the list into a sublist until each sublist consists only a single
 * element then merge all those sublists together to form a sorted list.
 *
 * Mergesort can be implemented from top-down (recursive) or bottom-up (iterative for loop) depends on
 * requirement or time/space complexity we want to achieve.
 */

#include <iostream>
#include <vector>

using namespace std;

#define PRINTARRAY(v) for (int i=0,size=v.size(); i<size; ++i) { \
                            if (i < size-1) cout << v[i] << " "; else cout << v[i];} cout << endl;

/**
 * Merge two sublists of v together in range of [start, end] separated by mid location.
 * This is in-place operation.
 *
 * \param v Input list to be merged
 * \param start Start index of range to be sorted in v
 * \param mid Mid index of range to be sorted in v
 * \param end End index of range to be sorted in v
 */
template <typename T>
static void merge(vector<T>& v, int start, int mid, int end)
{
    T temp[end - start + 1];

    int i = start, j = mid+1, k=0;

    while (i <= mid && j <= end)
    {
        if (v[i] <= v[j])
            temp[k++] = v[i++];
        else
            temp[k++] = v[j++];
    }

    while (i <= mid)
        temp[k++] = v[i++];

    while (j <= end)
        temp[k++] = v[j++];

    for (int i=start; i<=end; ++i)
        v[i] = temp[i-start];
}

/**
 * Mergesort for input v from start to end index.
 * It's inplace operation.
 *
 * \param v Input list to be sorted
 * \param start Start index for range to sort from input list
 * \param end End index for range to sort from input list
 */
template <typename T>
static void mergesort(vector<T>& v, int start, int end)
{
    if (start < end)
    {
        int mid = (start + end) / 2;
        mergesort(v, start, mid);
        mergesort(v, mid+1, end);
        merge(v, start, mid, end);
    }
}

int main()
{
    vector<char> v ({'A', 'S', 'O', 'R', 'T', 'I', 'N', 'G', 'E', 'X', 'A', 'M', 'P', 'L', 'E'});
    PRINTARRAY(v);

    mergesort(v, 0, v.size()-1);
    PRINTARRAY(v);

    return 0;
}
