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
}

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

    pq.Replace('B');
    pq.PrintElements<char>();

    std::cout << "Pop and get: " << pq.Pop<char>() << std::endl;
    pq.PrintElements<char>();

    std::cout << "Top: " << pq.Top<char>() << std::endl;

    return 0;
}
