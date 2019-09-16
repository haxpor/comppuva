/**
 * Implementation of Quicksort in bottom-up approach via iterative (loop).
 * It's more optimized (as tested not about performance but stack space) version of
 * recursive version of quicksort as can be found at Algorithm/Quicksort.cpp.
 *
 * The implementation involves using std::stack to save the splitted (partitioned) of location-indexes.
 *
 * It still uses the same partition() function as seen in Algorithm/Quicksort.cpp
 *
 * Use testcases input from testcases/Quicksort.txt, or testcases/50Numbers.txt.
 */

#include "Util.h"
#include <stack>
#include <vector>
#include <algorithm>

using namespace std;

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
    PROFILE_DECLR
    vector<int> v; 
    int tmpN;
    while (cin >> tmpN)
        v.push_back(tmpN);

    PRINTARRAY(v)

    PROFILE_START
    QuicksortIterative(v, 0, v.size()-1);
    PROFILE_END
    PRINTARRAY(v)
    PROFILE_PRINT

    return 0;
}
