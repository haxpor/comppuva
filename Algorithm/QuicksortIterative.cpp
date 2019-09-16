/**
 * Implementation of Quicksort in bottom-up approach via iterative (loop).
 * It's more optimized version of recursive version of quicksort as can be found at Algorithm/Quicksort.cpp.
 *
 * The implementation involves using std::stack to save the splitted (partitioned) of location-indexes.
 *
 * It still uses the same partition() function as seen in Algorithm/Quicksort.cpp
 */

#include <iostream>
#include <stack>
#include <vector>
#include <algorithm>

using namespace std;

#define PRINTARRAY(v) for(const int& e: v) cout << e << " "; cout << endl;

static int partition(vector<int>& v, int low, int high)
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

static void QuicksortIterative(vector<int>& v, int l, int r)
{
    int i;
    stack<int> s;

    for (;;)
    {
        while (r > l)
        {
            i = partition(v, l, r);
            if (l-i > r-i)
            {
                s.push(l);
                s.push(i-1);
                l = i+1;
            }
            else
            {
                s.push(i+1);
                s.push(r);
                r = i-1;
            }
        }
        if (s.empty()) break;
        // note: std::stack's pop() function doesn't return value when it pops.
        r = s.top();    s.pop();
        l = s.top();    s.pop();
    }
}

int main()
{
    vector<int> v ({9, 7, 5, 11, 12, 2, 14, 3, 10, 6});
    PRINTARRAY(v)

    QuicksortIterative(v, 0, v.size()-1);
    PRINTARRAY(v)

    return 0;
}
