/**
 * Insertion Sort
 * Complextity: O(N ^ 2)
 * Input: A single line of uppercase character separated by a space.
 * Output: A single line of sorted array each as uppercase character separated by a space.
 */

#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>
#include <vector>
#include <pair>

template <typename T>
static void PrintVector(const std::vector<T>& v)
{
    for (int i=0; i<v.size(); ++i)
    {
        if (i != v.size()-1)  std::cout << v[i] << " ";
        else                  std::cout << v[i] << std::endl;
    }
}

/**
 * Print text in color for two locations.
 * 
 * \param colorMark1 std::pair of index, and color integer value for first location
 * \param colorMark2 std::pair of index, and color integer value for second location
 */
template <typename T>
static void PrintVectorColorized(const std::vector<T>& v, const std::pair&& colorMark1, const std::pair&& colorMark2)
{
    for (int i=0; i<v.size(); ++i)
    {
        if (i != v.size()-1)
        {
            if (first == i || second == i)
                std::cout << "\033[1;31m" << v[i] << "\033[0m ";
            else
                std::cout << v[i] << " ";
        }
        else
        {
            if (first == i || second == i)
                std::cout << "\033[1;31m" << v[i] << "\033[0m " << std::endl;
            else
                std::cout << v[i] << std::endl;
        }
    }
}

template <typename T>
static void InsertionSort(std::vector<T>& v)
{
    int i, j;

    for (i=1; i<v.size(); ++i)
    {
        j = i;
        // operate from right to left until all elements to the left are processed
        while ((j > 0) && (v[j] < v[j-1]))
        {
            std::swap(v[j], v[j-1]);
            PrintVectorColorized(v, j, j-1);
            --j;
        }
    }
};

int main()
{
    std::string lineInput;
    std::getline(std::cin, lineInput);   
    std::istringstream ss(lineInput);
    std::vector<char> elems;
    char c;

    // this will implicitly convert into int, there's no explicit support for char type
    // anyway it suits our needs
    while (ss >> c)
    {
        std::cout << c << " ";
        elems.emplace_back(std::move(c));
    }
    std::cout << std::endl;

    InsertionSort(elems);
    return 0;
}
