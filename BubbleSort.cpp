/**
 * Implementation of bubble sort.
 */

#include "Util.h"
#include <algorithm>

static void BubbleSort(int v[], int size)
{
    for (int i=size-1; i>=0; --i)
        for (int j=1; j<size; ++j)
            if (v[j] < v[j-1]) std::swap(v[j], v[j-1]);
}

int main()
{
    int v[] = {29, 14, 35, 12, 10, 5, 45, 0};
    const int size = sizeof(v) / sizeof(v[0]);
    PRINTSARRAY(v, size);
    BubbleSort(v, size);
    PRINTSARRAY(v, size);
    return 0;
}
