/**
 * Implementation of simple Priority Queue.
 * This version provides constant time in accessing largest element, and insertion,
 * but logarithmic time in extraction.
 */
#include <iostream>

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
        delete arr;
        arr = nullptr;
    }
    
    // insertion
    void Push(int v)
    {
        arr[n++] = v;
    }

    // extraction
    int Pop()
    {
        int maxi = 0;
        for (int i=1; i<n; ++i)
        {
            if (arr[maxi] < arr[i])
            {
                maxi = i;
            }
        }

        std::swap(arr[maxi], arr[n-1]);
        return arr[--n];
    }

    bool Empty() const
    {
        return n == 0;
    }

private:
    int* arr;
    int n;
};

int main()
{
    PQ pq(12);
    pq.Push('X');
    pq.Push('T');
    pq.Push('O');
    pq.Push('G');
    pq.Push('S');
    pq.Push('M');
    pq.Push('N');
    pq.Push('A');
    pq.Push('E');
    pq.Push('R');
    pq.Push('A');
    pq.Push('I');

    // in turn this while loop will sort the range out
    while (!pq.Empty())
        std::cout << char(pq.Pop()) << " ";
    std::cout << std::endl;
    return 0;
}
