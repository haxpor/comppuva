/**
 * Implementation of HeapSort
 *
 * Basically it is built on top of Priority Queue with underlying Heap Data Structure to allow
 * contant time in getting access to the largest element (root node), O(nlogn) time complexity for
 * insertion and extraction.
 *
 * For convenient in implementing Heap Sort algorithm in this source file, we make use of DS/PQ.cpp
 * thus making function calls. For performance-wise, we might consider eliminating function call,
 * and directly incorporate code into as well as allow HearSort() function to directly access to
 * backing store of heap data structure.
 */

#include "Util.h"
#include <cmath>

// -- the following PQ code is copied from DS/PQ.cpp --//
class PQ
{
public:
    PQ(int max): n(0)
    {
        // note: this only allocate new memory space, not yet initialize elements yet
        arr = new int[max];
    }

    ~PQ()
    {
        delete[] arr;
        arr = nullptr;
    }
    
    // insertion
    // v is value to be pushed into
    void Push(int v)
    {
        arr[n++] = v;
        UpHeap(n);
    }

    // extraction
    // if call Pop() when it's empty, then it's undefined behavior.
    // actually it depends whether we want to return the root node in Pop() operation, or just have
    // another Top() to only peek the largest value without doing any pop.
    //
    // Template method added here just for convenient in printing as custom data type i.e. char
    // externally. It doesn't need, or better added template to the whole class to deal with custom
    // underlying data type.
    template <typename T>
    T Pop()
    {
        if (n == 1)
            return arr[--n];

        T ret = arr[0];
        std::swap(arr[0], arr[(n--)-1]);
        DownHeap(0);
        return ret;
    }

    // it will be undefined behavior if calling this function when it's empty.
    template <typename T>
    T Top() const
    {
        return arr[0];
    }

    // v is value to replace at the root of node of the heap
    void Replace(int v)
    {
        arr[0] = v;
        DownHeap(0);
    }

    bool Empty() const
    {
        return n == 0;
    }

    template <typename C>
    void PrintElements() const
    {
        for (int i=0; i<n; ++i)
        {
            std::cout << static_cast<C>(arr[i]) << " ";
        }
        std::cout << std::endl;
    }

private:
    int* arr;
    int n;

    // k is index
    void UpHeap(int k)
    {
        int kk = k - 1;
        if (kk == 0)
            return;

        int comparei = kk;
        int parenti = std::floor((kk+1)/2) - 1;
        while (arr[parenti] < arr[comparei] && parenti >= 0)
        {
            std::swap(arr[parenti], arr[comparei]);
            comparei = parenti;
            parenti = std::floor((comparei+1)/2) - 1;
        }
    }

    // k is index
    void DownHeap(int k)
    {
        if (n == 0)
            return;

        int parenti = k;
        int lefti = 2*k + 1;
        int righti = 2*k + 2;
        while (parenti < n && lefti < n)
        {
            int leftcVal = arr[lefti];
            int rightcVal = arr[righti];
            int parentVal = arr[parenti];

            // left and right
            if (lefti < n && righti < n && (parentVal < leftcVal || parentVal < rightcVal))
            {
                if (leftcVal <= rightcVal)
                {
                    std::swap(arr[parenti], arr[righti]);
                    parenti = righti;
                }
                else
                {
                    std::swap(arr[parenti], arr[lefti]);
                    parenti = lefti;
                }
            }
            // only left
            else if (lefti < n && righti >= n && parentVal < leftcVal)
            {
                std::swap(arr[parenti], arr[lefti]);
                parenti = lefti;
            }
            else
            {
                // equal
                break;
            }

            lefti = 2*parenti + 1;
            righti = 2*parenti + 2;
        }
        PrintElements<int>();
    }
};
// -- end of PQ implementation section -- //

static void HeapSort(int v[], int n)
{
    PQ pq(n);

    for (int i=0; i<n; ++i)
    {
        pq.Push(v[i]);
    }

    pq.PrintElements<int>();

    for (int i=n-1; i>=0; --i)
    {
        v[i] = pq.Pop<int>();
    }
}

int main()
{
    int v[] = {12, 11, 13, 5, 6, 9};
    const int n = sizeof(v) / sizeof(v[0]);    

    HeapSort(v, n);

    for (int i=0; i<n; ++i)
        std::cout << v[i] << " ";
    std::cout << std::endl;

    return 0;
}
