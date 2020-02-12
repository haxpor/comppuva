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
 * Space complexity: O(N^2) + 2 auxiliary variables to keep track of taken/notTaken
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
	    std::vector<std::vector<int>> lookup (nums.size()+1, std::vector<int>(nums.size(), -1));
        return lengthOfLIS(nums, -1, 0, lookup);
    }
private:
    int lengthOfLIS(const std::vector<int>& nums, int prevIdx, int currIdx, std::vector<std::vector<int>>& lookup)
    {
        if (currIdx >= nums.size())
            return 0;

        if (lookup[prevIdx+1][currIdx] != -1)
        {
            return lookup[prevIdx+1][currIdx];
        }

        int taken = 0;
        if (prevIdx == -1 || nums[currIdx] > nums[prevIdx])
        {
            taken = lengthOfLIS(nums, currIdx, currIdx + 1, lookup) + 1;
        }

        int notTaken = lengthOfLIS(nums, prevIdx, currIdx + 1, lookup);
        lookup[prevIdx+1][currIdx] = std::max(taken, notTaken);
        return lookup[prevIdx+1][currIdx];
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
