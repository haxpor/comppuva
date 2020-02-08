/**
 * Problem 33 - https://leetcode.com/problems/search-in-rotated-sorted-array/
 * Format of testcase.txt is as follows
 *
 * Number of testcases
 * Testcase#1 Input numbers separated by white space
 * Testcase#1 Target number
 * Testcase#1 Expect number
 * Testcase#2 ... and so on
 *
 *
 * Note: This one got Runtime Error in Leetcode but with same testcase in question, it passes offline.
 */
#include <vector>
#include <cassert>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <cstdio>
#include <cstdlib>

class Solution {
public:
    int search(std::vector<int>& nums, int target) {
        const int size = nums.size();
        if (size == 0)
            return -1;
        if (size == 1)
            return target == nums.front() ? 0 : -1;

        int left = 0;
        int right = size-1;

        // already sorted case
        // then perform binary search
        if (nums[0] < nums[right])
        {
            while (left <= right)
            {
                int mid = left + (right-left)/2;
                if (nums[mid] > target)
                    right = mid - 1;
                else if (nums[mid] < target)
                    left = mid + 1;
                else
                    // found
                    return mid;
            }
            // not found
            return -1;
        }    
         
        // in sparsed case
        // find pivot-element's index using as halves-separator then perform binary search on both halves
        int pivot;
        while (left <= right)
        {
            int mid = left + (right-left)/2;
            if (nums[mid - 1] > nums[mid])
            {
                pivot = mid;
                break;
            }
            
            if (nums[mid] > nums[mid+1])
            {
                pivot = mid+1;
                break;
            }

            if (nums[mid] > nums[0])
            {
                left = mid + 1;
            }
            else
            {
                right = mid - 1;
            }
        }

        // binary search on left half
        left = 0;
        right = pivot-1;
        while (left <= right)
        {
            int mid = left + (right-left)/2;
            if (nums[mid] > target)
                right = mid - 1;
            else if (nums[mid] < target)
                left = mid + 1;
            else
                return mid;
        }

        // binary search on right half
        left = pivot;
        right = size-1;
        while (left <= right)
        {
            int mid = left + (right-left)/2;
            if (nums[mid] > target)
                right = mid - 1;
            else if (nums[mid] < target)
                left = mid + 1;
            else
                return mid;

        }

        // if cannot find on both halves, then not found
        return -1;
    }
};

int main()
{
    std::ifstream infile("testcase.txt");
    std::string line;

    int N;
    infile >> N;    // read number of testcases

    Solution sol;

    for (int i=0; i<N; ++i)
    {
        std::getline(infile.ignore(), line); // need to ignore left-out byte (newline) from previously extraction operator
                                             // otherwise, we will read newline instead
        std::istringstream lineStream(line);
        std::vector<int> inputs;

        int num;

        // get list of input numbers
        while (lineStream >> num)
        {
            inputs.push_back(num);
        }

        // get target
        infile >> num;

        int expect;
        infile >> expect;

        // compute
        int search = sol.search(inputs, num);
        if (search == expect)
        {
            std::printf("[Success #%d] Output = %d, Expect = %d\n", i, search, expect);
        }
        else
        {
            std::printf("[Failed #%d] Output = %d, Expect = %d\n", i, search, expect);
            std::exit(1);
        }
    }

    infile.close();

    return 0;
}
