/**
 * Implementation of Priority Queue.
 *
 * This version provides constant time in extraction (access largest element),
 * but with expense of logaritmic of insertion.
 */
#include <iostream>
#include <cmath>

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
    void Push(int v)
    {
        if (n == 0)
        {
            arr[n++] = v;
        }
        else   
        {
            arr[n] = v;
            int comparei = n;
            int parenti = std::floor((n+1)/2) - 1;
            while (arr[parenti] < arr[comparei])
            {
                std::swap(arr[parenti], arr[comparei]);
                comparei = parenti;
                parenti = std::floor((comparei+1)/2) - 1;
            }
            ++n;
        }
    }

    // extraction
    // if call Pop() when it's empty, then it's undefined behavior.
    int Pop()
    {
        if (n == 1)
            return arr[--n];
        
        std::swap(arr[0], arr[n-1]);
        return arr[--n];
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
            std::cout << C(arr[i]) << " ";
        }
        std::cout << std::endl;
    }

private:
    int* arr;
    int n;
};

int main()
{
    PQ pq(13);
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

    pq.PrintElements<char>();
    
    pq.Push('P');
    pq.PrintElements<char>();

    return 0;
}
