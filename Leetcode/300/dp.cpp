/**
 * Problem 300 - https://leetcode.com/problems/longest-increasing-subsequence/
 *
 * Format of testcase.txt is as follows
 *
 * Number of testcases
 * TC#1 Input numbers separated by white space
 * TC#1 Expect number
 * TC#2 ... and so on
 *
 * Time complexity: O(N^2) (exactly compute once for each sub-problem) but would be O(2^N) for memory access to get cached computed result
 * Space complexity: O(N) + 2 auxiliary variables to keep track of taken/notTaken
 *
 */
#include <vector>
#include <cassert>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <cstdio>
#include <limits>
#include <cmath>

class Solution {
public:
    int lengthOfLIS(std::vector<int>& nums) {
        const int size = nums.size();
        if (size == 0)
            return 0;
        if (size == 1)
            return 1;

        std::vector<int> lookup (nums.size()+1);
        lookup[0] = 1;
        
        int maxLIS = 1;
        // -- global solution
        for (int i=1; i<size; ++i)
        {
            // -- local solution
            int maxLocal = 0;
            for (int j=0; j<i; ++j)
            {
                if (nums[i] > nums[j])
                {
                    maxLocal = std::max(maxLocal, lookup[j]);
                }
            }
            lookup[i] = maxLocal + 1;
            maxLIS = std::max(maxLIS, lookup[i]);
        }
        return maxLIS;
    }
};

int main()
{
    std::ifstream infile("testcases.txt");
    std::string line;

    int N;
    infile >> N;    // read number of testcases
    infile.ignore();

    Solution sol;

    for (int i=0; i<N; ++i)
    {
        std::getline(infile, line);
        std::istringstream lineStream(line);
        std::vector<int> inputs;

        // get list of input numbers
        int num;
        while (lineStream >> num)
        {
            inputs.push_back(num);
        }

        int expect;
        infile >> expect;
        infile.ignore();

        // compute
        int out = sol.lengthOfLIS(inputs);
        if (out == expect)
        {
            std::printf("[Success #%d] Output = %d, Expect = %d\n", i, out, expect);
        }
        else
        {
            std::printf("[Failed #%d] Output = %d, Expect = %d\n", i, out, expect);
        }
    }

    infile.close();

    return 0;
}
