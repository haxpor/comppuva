/**
 * Insertion Sort with Raw Array
 * Complextity: O(N ^ 2)
 * Input: A single line of uppercase character separated by a space.
 * Output: A single line of sorted array each as uppercase character separated by a space.
 */

#include <iostream>
#include <algorithm>

template <typename T>
static void InsertionSort(T arr[], int n)
{
    int i, j;

    for (i=1; i<n; ++i)
    {
        j = i;
        // operate from right to left until all elements to the left are processed
        while ((j > 0) && (arr[j] < arr[j-1]))
        {
            std::swap(arr[j], arr[j-1]);
            --j;
        }
    }
};

int main()
{
    char input[] = {'A', 'S', 'O', 'R', 'T', 'I', 'N', 'G', 'E', 'X', 'A', 'M', 'P', 'L', 'E'};
    InsertionSort(input, sizeof(input)/sizeof(char));
    for (const char& c : input)
    {
        std::cout << c << " ";
    }

    std::cout << std::endl;
    return 0;
}
